#!/usr/bin/env python3

from jinja2 import Template, Environment, FileSystemLoader
from itertools import tee
import sys
import os

import pprint
pp = pprint.PrettyPrinter(indent=4)

def snake_case(string):
    prev_upper = False
    at_start = True
    retval = ""

    for char in string:
        if char.isupper():
            if not prev_upper and not at_start:
                retval += "_"
            prev_upper = True

        else:
            prev_upper = False

        retval += char.lower()
        at_start = False

    return retval

mydir = os.path.dirname(os.path.abspath(__file__))
outdir = sys.argv[1]
generate = sys.argv[2]

type_map = {
    -1 : "uint8_t*",
    1  : "uint8_t",
    2  : "uint16_t",
    4  : "uint32_t",
    8  : "uint64_t",
    's': "uint8_t[9]",
}

pe_header = [
    { "name": "Machine", "pe_size": 2, "format": {"enum": "ppelib_machine_type_map"}},
    { "name": "NumberOfSections", "pe_size": 2},
    { "name": "TimeDateStamp", "pe_size": 4},
    { "name": "PointerToSymbolTable", "pe_size": 4, "format": {"hex": True}},
    { "name": "NumberOfSymbols", "pe_size": 4},
    { "name": "SizeOfOptionalHeader", "pe_size": 2},
    { "name": "Characteristics", "pe_size": 2, "format": {"bitfield": "ppelib_characteristics_map"}},
    { "name": "Magic", "pe_size": 2, "format": {"enum": "ppelib_magic_type_map"}},
    { "name": "MajorLinkerVersion", "pe_size": 1},
    { "name": "MinorLinkerVersion", "pe_size": 1},
    { "name": "SizeOfCode", "pe_size": 4},
    { "name": "SizeOfInitializedData", "pe_size": 4},
    { "name": "SizeOfUninitializedData", "pe_size": 4},
    { "name": "AddressOfEntryPoint", "pe_size": 4, "format": {"hex": True}},
    { "name": "BaseOfCode", "pe_size": 4, "format": {"hex": True}},
    { "name": "BaseOfData", "pe_size": 4, "peplus_size": 0, "format": {"hex": True}},
    { "name": "ImageBase", "pe_size": 4, "peplus_size": 8, "format": {"hex": True}},
    { "name": "SectionAlignment", "pe_size": 4},
    { "name": "FileAlignment", "pe_size": 4},
    { "name": "MajorOperatingSystemVersion", "pe_size": 2},
    { "name": "MinorOperatingSystemVersion", "pe_size": 2},
    { "name": "MajorImageVersion", "pe_size": 2},
    { "name": "MinorImageVersion", "pe_size": 2},
    { "name": "MajorSubsystemVersion", "pe_size": 2},
    { "name": "MinorSubsystemVersion", "pe_size": 2},
    { "name": "Win32VersionValue", "pe_size": 4},
    { "name": "SizeOfImage", "pe_size": 4},
    { "name": "SizeOfHeaders", "pe_size": 4},
    { "name": "Checksum", "pe_size": 4, "format": {"hex": True}},
    { "name": "Subsystem", "pe_size": 2, "format": {"enum": "ppelib_windows_subsystem_map"}},
    { "name": "DllCharacteristics", "pe_size": 2, "format": {"bitfield": "ppelib_dll_characteristics_map"}},
    { "name": "SizeOfStackReserve", "pe_size": 4, "peplus_size": 8},
    { "name": "SizeOfStackCommit", "pe_size": 4, "peplus_size": 8},
    { "name": "SizeOfHeapReserve", "pe_size": 4, "peplus_size": 8},
    { "name": "SizeOfHeapCommit", "pe_size": 4, "peplus_size": 8},
    { "name": "LoaderFlags", "pe_size": 4},
    { "name": "NumberOfRvaAndSizes", "pe_size": 4},
]

pe_header_directories = [
    "ExportTable",
    "ImportTable",
    "ResourceTable",
    "ExceptionTable",
    "CertificateTable",
    "BaseRelocationTable",
    "Debug",
    "Architecture",
    "GlobalPtr" ,
    "TLSTable",
    "LoadConfigTable",
    "BoundImport",
    "IAT",
    "DelayImportDescriptor",
    "CLRRuntimeHeader",
    "Reserved",
]

section_header = [
    { "name": "Name", "pe_size": 8, "format": {"string": True}},
    { "name": "VirtualSize", "pe_size": 4},
    { "name": "VirtualAddress", "pe_size": 4, "format": {"hex": True}},
    { "name": "SizeOfRawData", "pe_size": 4},
    { "name": "PointerToRawData", "pe_size": 4, "format": {"hex": True}},
    { "name": "PointerToRelocations", "pe_size": 4, "format": {"hex": True}},
    { "name": "PointerToLinenumbers", "pe_size": 4, "format": {"hex": True}},
    { "name": "NumberOfRelocations", "pe_size": 2},
    { "name": "NumberOfLinenumbers", "pe_size": 2},
    { "name": "Characteristics", "pe_size": 4, "format": {"bitfield": "ppelib_section_flags_map"}},
]

certificate_table = [
    { "name": "Length", "pe_size": 4 },
    { "name": "Revision", "pe_size": 2, "format": {"enum": "ppelib_certificate_revision_map"}},
    { "name": "CertificateType", "pe_size": 2, "format": {"enum": "ppelib_certificate_type_map"}},
    { "name": "Certificate", "pe_size": -1, "format": {"variable_size": True}},
]

fields = []
pe_offset = 0
peplus_offset = 0
for field in pe_header:
    pe_size = 0
    peplus_size = 0
    pe_t = ""
    peplus_t = ""

    field_name = snake_case(field["name"])
    retval = { "name": field_name }
    retval["human_name"] = field["name"]

    pe_t = type_map[field["pe_size"]]
    pe_size = field["pe_size"]

    if "peplus_size" in field:
        if field["peplus_size"]:
            peplus_t = type_map[field["peplus_size"]]
            peplus_size = field["peplus_size"]
    else:
        peplus_t = pe_t
        peplus_size = pe_size

    if "format" in field:
        retval["format"] = field["format"]

    if pe_size:
        retval["pe_type"] = pe_t
        retval["pe_offset"] = pe_offset
        retval["pe_size"] = pe_size
        pe_offset = pe_offset + pe_size

    if peplus_size:
        retval["peplus_type"] = peplus_t
        retval["peplus_offset"] = peplus_offset
        retval["peplus_size"] = peplus_size
        peplus_offset = peplus_offset + peplus_size

    fields.append(retval)

common_fields = []
pe_fields = []
peplus_fields = []

sizes = {
    "total_pe": 0,
    "total_peplus": 0,
    "common": 0,
    "pe": 0,
    "peplus": 0,
}

in_common = True
for field in fields:
    if "pe_type" in field and "peplus_type" in field:
        if field["pe_type"] != field["peplus_type"]:
            in_common = False
    else:
        in_common = False

    if in_common:
        f = {
            "name": field["name"],
            "human_name": field["human_name"],
            "type": field["pe_type"],
            "offset": field["pe_offset"],
            "size": field["pe_size"],
        }

        if "format" in field:
            f["format"] = field["format"]
        common_fields.append(f)

        sizes["common"] = sizes["common"] + field["pe_size"]
        sizes["total_pe"] = sizes["common"]
        sizes["total_peplus"] = sizes["common"]

    else:
        f = {
            "name": field["name"],
            "human_name": field["human_name"],
            "type": field["pe_type"],
            "offset": field["pe_offset"],
            "pe_size": field["pe_size"],
        }

        if "peplus_size" in field:
            f["size"] = field["peplus_size"]
        else:
            f["size"] = field["pe_size"]

        if "format" in field:
            f["format"] = field["format"]
        pe_fields.append(f)
        sizes["total_pe"] = sizes["total_pe"] + field["pe_size"]

        if not "peplus_type" in field:
            continue

        f = {
            "name": field["name"],
            "human_name": field["human_name"],
            "type": field["peplus_type"],
            "offset": field["peplus_offset"],
            "pe_size": field["peplus_size"],
        }
        if "format" in field:
            f["format"] = field["format"]

        if "peplus_size" in field:
            f["size"] = field["peplus_size"]
        else:
            f["size"] = field["pe_size"]

        peplus_fields.append(f)

        sizes["total_peplus"] = sizes["total_peplus"] + field["peplus_size"]

directories = []
for directory in pe_header_directories:
    directories.append({
        "name": f"dir_{snake_case(directory)}".upper(),
        "human_name": directory
    })

if generate == "header":
    with open(f'{mydir}/templates/ppelib-header.h') as file_:
        template = Environment(loader=FileSystemLoader(f"{mydir}/templates/")).from_string(file_.read())
        with open(f'{outdir}/ppelib-header.h', 'w') as outfile:
            outfile.write(template.render(fields=fields, directories=directories))

if generate == "c":
    with open(f'{mydir}/templates/ppelib-header.c') as file_:
        template = Environment(loader=FileSystemLoader(f"{mydir}/templates/")).from_string(file_.read())
        with open(f'{outdir}/ppelib-header.c', 'w') as outfile:
            outfile.write(template.render(
                pe_magic_field=snake_case('Magic'),
                pe_rvas_field=snake_case('NumberOfRvaAndSizes'),
                sizes=sizes,
                common_fields=common_fields,
                pe_fields=pe_fields,
                peplus_fields=peplus_fields,
                directories=directories
            ))

fields = []
offset = 0
length = 0
for field in section_header:
    t = type_map[field["pe_size"]]
    field_name = snake_case(field["name"])
    f = {
        "name": field_name,
        "human_name": field["name"],
        "pe_size": field["pe_size"],
        "pe_type": t,
        "offset" : offset,
    }
    if "format" in field:
        f["format"] = field["format"]
    fields.append(f)
    offset = offset + field["pe_size"]
    if f["pe_size"] > 0:
        length = length + f['pe_size']

pointer_field = snake_case("PointerToRawData")
virtualsize_field = snake_case("VirtualSize")
rawsize_field = snake_case("SizeOfRawData")

if generate == "header":
    with open(f'{mydir}/templates/ppelib-section.h') as file_:
        template = Environment(loader=FileSystemLoader(f"{mydir}/templates/")).from_string(file_.read())
        with open(f'{outdir}/ppelib-section.h', 'w') as outfile:
            outfile.write(template.render(
                fields=fields,
                length=length,
                pointer_field=pointer_field,
                virtualsize_field=virtualsize_field,
                rawsize_field=rawsize_field,
            ))

if generate == "c":
    with open(f'{mydir}/templates/ppelib-section.c') as file_:
        template = Environment(loader=FileSystemLoader(f"{mydir}/templates/")).from_string(file_.read())
        with open(f'{outdir}/ppelib-section.c', 'w') as outfile:
            outfile.write(template.render(
                fields=fields,
                length=length,
                pointer_field=pointer_field,
                virtualsize_field=virtualsize_field,
                rawsize_field=rawsize_field,
            ))

fields = []
offset = 0
length = 0
for field in certificate_table:
    t = type_map[field["pe_size"]]
    field_name = snake_case(field["name"])
    f = {
        "name": field_name,
        "human_name": field["name"],
        "pe_size": field["pe_size"],
        "pe_type": t,
        "offset" : offset,
    }
    if "format" in field:
        f["format"] = field["format"]
    fields.append(f)
    offset = offset + field["pe_size"]
    if f["pe_size"] > 0:
        length = length + f['pe_size']

length_field = snake_case("Length")

if generate == "header":
    with open(f'{mydir}/templates/ppelib-certificate_table.h') as file_:
        template = Environment(loader=FileSystemLoader(f"{mydir}/templates/")).from_string(file_.read())
        with open(f'{outdir}/ppelib-certificate_table.h', 'w') as outfile:
            outfile.write(template.render(
                fields=fields,
                length=length,
                length_field=length_field
            ))

if generate == "c":
    with open(f'{mydir}/templates/ppelib-certificate_table.c') as file_:
        template = Environment(loader=FileSystemLoader(f"{mydir}/templates/")).from_string(file_.read())
        with open(f'{outdir}/ppelib-certificate_table.c', 'w') as outfile:
            outfile.write(template.render(
                fields=fields,
                length=length,
                length_field=length_field
            ))
