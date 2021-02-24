#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "pelib-header.h"
#include "pelib-section.h"
#include "constants.h"

#define CHECK_BIT(var,val) ((var) & (val))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

typedef struct pefile {
        size_t pe_header_offset;
        size_t coff_header_offset;
	size_t section_offset;
        size_t end_of_sections;

       	pelib_header_t header;
	pelib_section_t* sections;

        uint8_t* stub;
	size_t trailing_data_size;
	uint8_t* trailing_data;
} pefile_t;


int read_pe_file(const char* filename, uint8_t** file, size_t* size, uint32_t* pe_header_offset) {
	FILE *f = fopen(filename, "r");

	if (fseek(f, PE_SIGNATURE, SEEK_SET) == -1) {
		perror("Seeking to PE header offset");
		return 1;
	}

	size_t retsize;

	retsize = fread(pe_header_offset, 1, 4, f);
	if (retsize != 4) {
		fprintf(stderr, "Couldn't read PE header offset. Got %li bytes, expected 4\n", retsize);
		return 1;
	}

	if (fseek(f, *pe_header_offset, SEEK_SET) == -1) {
		perror("Seeking to PE header");
		return 1;
	}

	uint8_t signature[4];
	retsize = fread(&signature, 1, 4, f);
	if (retsize != 4) {
		fprintf(stderr, "Couldn't read PE signature. Got %li bytes, expected 4\n", retsize);
		return 1;
	}

	if (memcmp(signature, "PE\0", 4) != 0) {
		fprintf(stderr, "Not a PE file. Got 0x%X 0x%X 0x%X 0x%X, expected 0x%X 0x%X 0x%X 0x%X\n", signature[0], signature[1], signature[2], signature[3], 'P', 'E', 0, 0);
	}

	fseek(f, 0, SEEK_END);
	*size = ftell(f);
	rewind(f);
	
	*file = malloc(*size);
	if (! *file) {
		fprintf(stderr, "Unable to allocate memory\n");
		return 1;
	}

	retsize = fread(*file, 1, *size, f);
	if (retsize != *size) {
		fprintf(stderr, "Couldn't file. Got %li bytes, expected 4\n", retsize);
		return 1;
	}
	fclose(f);

	return 0;
}

int write_pe_file(const char* filename, const pefile_t* pe) {
	uint8_t* buffer = NULL;
	size_t size = 0;
	size_t write = 0;

	// Write stub
	size += pe->pe_header_offset;
	size += 4;
	size_t coff_header_size = serialize_pe_header(&pe->header, NULL, pe->pe_header_offset);
	size += coff_header_size;
	size_t end_of_sections = 0;

	size_t section_offset = pe->pe_header_offset + coff_header_size;
	for (uint32_t i = 0; i < pe->header.number_of_sections; ++i) {
		size_t section_size = serialize_section(&pe->sections[i], NULL, section_offset + (i * PE_SECTION_HEADER_SIZE));
		if (section_size > end_of_sections) {
			end_of_sections = section_size;
		}
	}

	// Theoretically all the sections could be before the header
	if (end_of_sections > size) {
		size = end_of_sections;
	}

	size += pe->trailing_data_size;

	printf("Size of coff_header        : %li\n", coff_header_size);
	printf("Size of sections           : %li\n", end_of_sections);
	printf("Size of trailing data      : %li\n", pe->trailing_data_size);
	printf("Total size                 : %li\n", size);

	buffer = realloc(buffer, size);
	if (! buffer) {
		fprintf(stderr, "Failed to allocate\n");
		return 1;
	}
	memset(buffer, 0, size);
	//memset(buffer, 0xFF, size);

	memcpy(buffer, pe->stub, pe->pe_header_offset);
	write += pe->pe_header_offset;

	// Write PE header
	memcpy(buffer + write, "PE\0", 4);
	write += 4;

	// Write COFF header
	serialize_pe_header(&pe->header, buffer, pe->pe_header_offset + 4);

	// Write sections
	for (uint32_t i = 0; i < pe->header.number_of_sections; ++i) {
		serialize_section(&pe->sections[i], buffer, section_offset + 4 + (i * PE_SECTION_HEADER_SIZE));
	}

	// Write trailing data
	memcpy(buffer + end_of_sections, pe->trailing_data, pe->trailing_data_size);
	
	FILE *f = fopen(filename, "w+");
	fwrite(buffer, 1, size, f);

	fclose(f);
	free(buffer);

	return size;
}

int main(int argc, char* argv[]) {
	if (! argc) return 1;

	pefile_t pe = {0};
	uint8_t* file;
	size_t size;
	uint32_t pe_header_offset;

	if (read_pe_file(argv[1], &file, &size, &pe_header_offset)) {
		return 1;
	}

	pe.pe_header_offset = pe_header_offset;
	pe.coff_header_offset = pe_header_offset + 4;

	if (size < pe.coff_header_offset + COFF_HEADER_SIZE) {
		fprintf(stderr, "File size too small\n");
		return 1;
	}

	size_t header_size = deserialize_pe_header(file, pe.coff_header_offset, size, &pe.header);
	pe.section_offset = header_size + pe.coff_header_offset;

	print_pe_header(&pe.header);
	printf("\n");

	pe.sections = malloc(sizeof(pelib_section_t) * pe.header.number_of_sections);
	pe.end_of_sections = 0;

	for (uint32_t i = 0; i < pe.header.number_of_sections; ++i) {
		size_t section_size = deserialize_section(file, pe.section_offset + (i * PE_SECTION_HEADER_SIZE), size, &pe.sections[i]);
		if (section_size > pe.end_of_sections) {
			pe.end_of_sections = section_size;
		}

		print_section(&pe.sections[i]);
		printf("\n");
	}

        pe.stub = malloc(pe.pe_header_offset);
        if (! pe.stub) {
                fprintf(stderr, "Failed to allocate memory\n");
                return 1;
        }
        memcpy(pe.stub, file, pe.pe_header_offset);

        if (size > pe.end_of_sections) {
                pe.trailing_data_size = size - pe.end_of_sections;
                pe.trailing_data = malloc(pe.trailing_data_size);

                memcpy(pe.trailing_data, file + pe.end_of_sections, pe.trailing_data_size);
        }

	write_pe_file("out.exe", &pe);

	free(file);
	free(pe.stub);
	for (uint32_t i = 0; i < pe.header.number_of_sections; ++i) {
		free(pe.sections[i].contents);
	}
	free(pe.sections);
	free(pe.trailing_data);
}