/* Copyright 2021 Hein-Pieter van Braam-Stewart
 *
 * This file is part of ppelib (Portable Portable Executable LIBrary)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PPELIB_CONSTANTS_H
#define PPELIB_CONSTANTS_H

#include <inttypes.h>
#include <stddef.h>

#define PE_SIGNATURE_OFFSET 0x3c
#define PE_SIGNATURE 0x00004550

#define COFF_HEADER_SIZE 20u
#define PE_HEADER_DATA_DIRECTORIES_SIZE 8u

#define PE_SECTION_HEADER_SIZE 40u

#define PE_OPTIONAL_HEADER_STANDARD_ENTRIES 9u
#define PE_OPTIONAL_HEADER_STANDARD_SIZE 28u
#define PEPLUS_OPTIONAL_HEADER_STANDARD_ENTRIES 8u
#define PEPLUS_OPTIONAL_HEADER_STANDARD_SIZE 24u

#define PE_OPTIONAL_HEADER_WINDOWS_ENTRIES 21u
#define PE_OPTIONAL_HEADER_WINDOWS_SIZE 68u
#define PEPLUS_OPTIONAL_HEADER_WINDOWS_ENTRIES 21u
#define PEPLUS_OPTIONAL_HEADER_WINDOWS_SIZE 88u

#define RESOURCE_DIRECTORY_TABLE_SIZE 16u
#define RESOURCE_DIRECTORY_ENTRY_SIZE 8u

#define PE32_MAGIC 0x10b
#define PE32PLUS_MAGIC 0x20b
#define PE32_ROM_MAGIC 0x107

typedef struct ppelib_map_entry {
        const char* string;
        uint32_t value;
} ppelib_map_entry_t;

enum ppelib_machine_type {
	IMAGE_FILE_MACHINE_UNKNOWN = 0x0,
	IMAGE_FILE_MACHINE_AM33 = 0x1d3,
	IMAGE_FILE_MACHINE_AMD64 = 0x8664,
	IMAGE_FILE_MACHINE_ARM = 0x1c0,
	IMAGE_FILE_MACHINE_ARM64 = 0xaa64,
	IMAGE_FILE_MACHINE_ARMNT = 0x1c4,
	IMAGE_FILE_MACHINE_EBC = 0xebc,
	IMAGE_FILE_MACHINE_I386 = 0x14c,
	IMAGE_FILE_MACHINE_IA64 = 0x200,
	IMAGE_FILE_MACHINE_M32R = 0x9041,
	IMAGE_FILE_MACHINE_MIPS16 = 0x266,
	IMAGE_FILE_MACHINE_MIPSFPU = 0x366,
	IMAGE_FILE_MACHINE_MIPSFPU16 = 0x466,
	IMAGE_FILE_MACHINE_POWERPC = 0x1f0,
	IMAGE_FILE_MACHINE_POWERPCFP = 0x1f1,
	IMAGE_FILE_MACHINE_R4000 = 0x166,
	IMAGE_FILE_MACHINE_RISCV32 = 0x5032,
	IMAGE_FILE_MACHINE_RISCV64 = 0x5064,
	IMAGE_FILE_MACHINE_RISCV128 = 0x5128,
	IMAGE_FILE_MACHINE_SH3 = 0x1a2,
	IMAGE_FILE_MACHINE_SH3DSP = 0x1a3,
	IMAGE_FILE_MACHINE_SH4 = 0x1a6,
	IMAGE_FILE_MACHINE_SH5 = 0x1a8,
	IMAGE_FILE_MACHINE_THUMB = 0x1c2,
	IMAGE_FILE_MACHINE_WCEMIPSV2 = 0x169,
};

static const ppelib_map_entry_t ppelib_magic_type_map[] = {
	{"PE32", PE32_MAGIC},
	{"PE32+", PE32PLUS_MAGIC},
	{"PE32 ROM", PE32_ROM_MAGIC},
	{NULL, 0}
};

static const ppelib_map_entry_t ppelib_machine_type_map[] = {
	{"IMAGE_FILE_MACHINE_UNKNOWN", 0x0},
	{"IMAGE_FILE_MACHINE_AM33", 0x1d3},
	{"IMAGE_FILE_MACHINE_AMD64", 0x8664},
	{"IMAGE_FILE_MACHINE_ARM", 0x1c0},
	{"IMAGE_FILE_MACHINE_ARM64", 0xaa64},
	{"IMAGE_FILE_MACHINE_ARMNT", 0x1c4},
	{"IMAGE_FILE_MACHINE_EBC", 0xebc},
	{"IMAGE_FILE_MACHINE_I386", 0x14c},
	{"IMAGE_FILE_MACHINE_IA64", 0x200},
	{"IMAGE_FILE_MACHINE_M32R", 0x9041},
	{"IMAGE_FILE_MACHINE_MIPS16", 0x266},
	{"IMAGE_FILE_MACHINE_MIPSFPU", 0x366},
	{"IMAGE_FILE_MACHINE_MIPSFPU16", 0x466},
	{"IMAGE_FILE_MACHINE_POWERPC", 0x1f0},
	{"IMAGE_FILE_MACHINE_POWERPCFP", 0x1f1},
	{"IMAGE_FILE_MACHINE_R4000", 0x166},
	{"IMAGE_FILE_MACHINE_RISCV32", 0x5032},
	{"IMAGE_FILE_MACHINE_RISCV64", 0x5064},
	{"IMAGE_FILE_MACHINE_RISCV128", 0x5128},
	{"IMAGE_FILE_MACHINE_SH3", 0x1a2},
	{"IMAGE_FILE_MACHINE_SH3DSP", 0x1a3},
	{"IMAGE_FILE_MACHINE_SH4", 0x1a6},
	{"IMAGE_FILE_MACHINE_SH5", 0x1a8},
	{"IMAGE_FILE_MACHINE_THUMB", 0x1c2},
	{"IMAGE_FILE_MACHINE_WCEMIPSV2", 0x169},
	{NULL, 0},
};

enum ppelib_characteristics {
	IMAGE_FILE_RELOCS_STRIPPED = 0x0001,
	IMAGE_FILE_EXECUTABLE_IMAGE = 0x0002,
	IMAGE_FILE_LINE_NUMS_STRIPPED = 0x0004,
	IMAGE_FILE_LOCAL_SYMS_STRIPPED = 0x0008,
	IMAGE_FILE_AGGRESSIVE_WS_TRIM = 0x0010,
	IMAGE_FILE_LARGE_ADDRESS_AWARE = 0x0020,
	IMAGE_FILE_RESERVED = 0x0040,
	IMAGE_FILE_BYTES_REVERSED_LO = 0x0080,
	IMAGE_FILE_32BIT_MACHINE = 0x0100,
	IMAGE_FILE_DEBUG_STRIPPED = 0x0200,
	IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP = 0x0400,
	IMAGE_FILE_NET_RUN_FROM_SWAP = 0x0800,
	IMAGE_FILE_SYSTEM = 0x1000,
	IMAGE_FILE_DLL = 0x2000,
	IMAGE_FILE_UP_SYSTEM_ONLY = 0x4000,
	IMAGE_FILE_BYTES_REVERSED_HI = 0x8000,
};

static const ppelib_map_entry_t ppelib_characteristics_map[] = {
	{"IMAGE_FILE_RELOCS_STRIPPED", 0x0001},
	{"IMAGE_FILE_EXECUTABLE_IMAGE", 0x0002},
	{"IMAGE_FILE_LINE_NUMS_STRIPPED", 0x0004},
	{"IMAGE_FILE_LOCAL_SYMS_STRIPPED", 0x0008},
	{"IMAGE_FILE_AGGRESSIVE_WS_TRIM", 0x0010},
	{"IMAGE_FILE_LARGE_ADDRESS_AWARE", 0x0020},
	{"IMAGE_FILE_RESERVED", 0x0040},
	{"IMAGE_FILE_BYTES_REVERSED_LO", 0x0080},
	{"IMAGE_FILE_32BIT_MACHINE", 0x0100},
	{"IMAGE_FILE_DEBUG_STRIPPED", 0x0200},
	{"IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP", 0x0400},
	{"IMAGE_FILE_NET_RUN_FROM_SWAP", 0x0800},
	{"IMAGE_FILE_SYSTEM", 0x1000},
	{"IMAGE_FILE_DLL", 0x2000},
	{"IMAGE_FILE_UP_SYSTEM_ONLY", 0x4000},
	{"IMAGE_FILE_BYTES_REVERSED_HI", 0x8000},
	{NULL, 0},
};

enum ppelib_windows_subsystem {
	IMAGE_SUBSYSTEM_UNKNOWN = 0,
	IMAGE_SUBSYSTEM_NATIVE = 1,
	IMAGE_SUBSYSTEM_WINDOWS_GUI = 2,
	IMAGE_SUBSYSTEM_WINDOWS_CUI = 3,
	IMAGE_SUBSYSTEM_OS2_CUI = 5,
	IMAGE_SUBSYSTEM_POSIX_CUI = 7,
	IMAGE_SUBSYSTEM_NATIVE_WINDOWS = 8,
	IMAGE_SUBSYSTEM_WINDOWS_CE_GUI = 9,
	IMAGE_SUBSYSTEM_EFI_APPLICATION = 10,
	IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER = 11,
	IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER = 12,
	IMAGE_SUBSYSTEM_EFI_ROM = 13,
	IMAGE_SUBSYSTEM_XBOX = 14,
	IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION = 16,
};

static const ppelib_map_entry_t ppelib_windows_subsystem_map[] = {
	{"IMAGE_SUBSYSTEM_UNKNOWN", 0},
	{"IMAGE_SUBSYSTEM_NATIVE", 1},
	{"IMAGE_SUBSYSTEM_WINDOWS_GUI", 2},
	{"IMAGE_SUBSYSTEM_WINDOWS_CUI", 3},
	{"IMAGE_SUBSYSTEM_OS2_CUI", 5},
	{"IMAGE_SUBSYSTEM_POSIX_CUI", 7},
	{"IMAGE_SUBSYSTEM_NATIVE_WINDOWS", 8},
	{"IMAGE_SUBSYSTEM_WINDOWS_CE_GUI", 9},
	{"IMAGE_SUBSYSTEM_EFI_APPLICATION", 10},
	{"IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER", 11},
	{"IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER", 12},
	{"IMAGE_SUBSYSTEM_EFI_ROM", 13},
	{"IMAGE_SUBSYSTEM_XBOX", 14},
	{"IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION", 16},
	{NULL, 0}
};

enum ppelib_dll_characteristics {
	IMAGE_DLLCHARACTERISTICS_RESERVED1 = 0x0001,
	IMAGE_DLLCHARACTERISTICS_RESERVED2 = 0x0002,
	IMAGE_DLLCHARACTERISTICS_RESERVED3 = 0x0004,
	IMAGE_DLLCHARACTERISTICS_RESERVED4 = 0x0008,
	IMAGE_DLLCHARACTERISTICS_HIGH_ENTROPY_VA = 0x0020,
	IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE = 0x0040,
	IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY = 0x0080,
	IMAGE_DLLCHARACTERISTICS_NX_COMPAT = 0x0100,
	IMAGE_DLLCHARACTERISTICS_NO_ISOLATION = 0x0200,
	IMAGE_DLLCHARACTERISTICS_NO_SEH = 0x0400,
	IMAGE_DLLCHARACTERISTICS_NO_BIND = 0x0800,
	IMAGE_DLLCHARACTERISTICS_APPCONTAINER = 0x1000,
	IMAGE_DLLCHARACTERISTICS_WDM_DRIVER = 0x2000,
	IMAGE_DLLCHARACTERISTICS_GUARD_CF = 0x4000,
	IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE = 0x8000,
};

static const ppelib_map_entry_t ppelib_dll_characteristics_map[] = {
	{"IMAGE_DLLCHARACTERISTICS_RESERVED1", 0x0001},
	{"IMAGE_DLLCHARACTERISTICS_RESERVED2", 0x0002},
	{"IMAGE_DLLCHARACTERISTICS_RESERVED3", 0x0004},
	{"IMAGE_DLLCHARACTERISTICS_RESERVED4", 0x0008},
	{"IMAGE_DLLCHARACTERISTICS_HIGH_ENTROPY_VA", 0x0020},
	{"IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE", 0x0040},
	{"IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY", 0x0080},
	{"IMAGE_DLLCHARACTERISTICS_NX_COMPAT", 0x0100},
	{"IMAGE_DLLCHARACTERISTICS_NO_ISOLATION", 0x0200},
	{"IMAGE_DLLCHARACTERISTICS_NO_SEH", 0x0400},
	{"IMAGE_DLLCHARACTERISTICS_NO_BIND", 0x0800},
	{"IMAGE_DLLCHARACTERISTICS_APPCONTAINER", 0x1000},
	{"IMAGE_DLLCHARACTERISTICS_WDM_DRIVER", 0x2000},
	{"IMAGE_DLLCHARACTERISTICS_GUARD_CF", 0x4000},
	{"IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE", 0x8000},
	{NULL, 0}
};

enum ppelib_data_directories {
	DIR_EXPORT_TABLE = 0,
	DIR_IMPORT_TABLE = 1,
	DIR_RESOURCE_TABLE = 2,
	DIR_EXCEPTION_TABLE = 3,
	DIR_CERTIFICATE_TABLE = 4,
	DIR_BASE_RELOCATION_TABLE = 5,
	DIR_DEBUG = 6,
	DIR_ARCHITECTURE = 7,
	DIR_GLOBAL_PTR = 8,
	DIR_TLSTABLE = 9,
	DIR_LOAD_CONFIG_TABLE = 10,
	DIR_BOUND_IMPORT = 11,
	DIR_IAT = 12,
	DIR_DELAY_IMPORT_DESCRIPTOR = 13,
	DIR_CLRRUNTIME_HEADER = 14,
	DIR_RESERVED = 15,
};

static const ppelib_map_entry_t ppelib_data_directories_map[] = {
	{"DIR_EXPORT_TABLE", 0},
	{"DIR_IMPORT_TABLE", 1},
	{"DIR_RESOURCE_TABLE", 2},
	{"DIR_EXCEPTION_TABLE", 3},
	{"DIR_CERTIFICATE_TABLE", 4},
	{"DIR_BASE_RELOCATION_TABLE", 5},
	{"DIR_DEBUG", 6},
	{"DIR_ARCHITECTURE", 7},
	{"DIR_GLOBAL_PTR", 8},
	{"DIR_TLSTABLE", 9},
	{"DIR_LOAD_CONFIG_TABLE", 10},
	{"DIR_BOUND_IMPORT", 11},
	{"DIR_IAT", 12},
	{"DIR_DELAY_IMPORT_DESCRIPTOR", 13},
	{"DIR_CLRRUNTIME_HEADER", 14},
	{"DIR_RESERVED", 15},
	{NULL, 0}
};

enum ppelib_section_flags {
	IMAGE_SCN_RESERVED1 = 0x00000000,
	IMAGE_SCN_RESERVED2 = 0x00000001,
	IMAGE_SCN_RESERVED3 = 0x00000002,
	IMAGE_SCN_RESERVED4 = 0x00000004,
	IMAGE_SCN_TYPE_NO_PAD = 0x00000008,
	IMAGE_SCN_RESERVED5 = 0x00000010,
	IMAGE_SCN_CNT_CODE = 0x00000020,
	IMAGE_SCN_CNT_INITIALIZED_DATA = 0x00000040,
	IMAGE_SCN_CNT_UNINITIALIZED_DATA = 0x00000080,
	IMAGE_SCN_LNK_OTHER = 0x00000100,
	IMAGE_SCN_LNK_INFO = 0x00000200,
	IMAGE_SCN_RESERVED6 = 0x00000400,
	IMAGE_SCN_LNK_REMOVE = 0x00000800,
	IMAGE_SCN_LNK_COMDAT = 0x00001000,
	IMAGE_SCN_GPREL = 0x00008000,
	IMAGE_SCN_MEM_PURGEABLE = 0x00020000,
	IMAGE_SCN_MEM_16BIT = 0x00020000,
	IMAGE_SCN_MEM_LOCKED = 0x00040000,
	IMAGE_SCN_MEM_PRELOAD = 0x00080000,
	IMAGE_SCN_ALIGN_1BYTES = 0x00100000,
	IMAGE_SCN_ALIGN_2BYTES = 0x00200000,
	IMAGE_SCN_ALIGN_4BYTES = 0x00300000,
	IMAGE_SCN_ALIGN_8BYTES = 0x00400000,
	IMAGE_SCN_ALIGN_16BYTES = 0x00500000,
	IMAGE_SCN_ALIGN_32BYTES = 0x00600000,
	IMAGE_SCN_ALIGN_64BYTES = 0x00700000,
	IMAGE_SCN_ALIGN_128BYTES = 0x00800000,
	IMAGE_SCN_ALIGN_256BYTES = 0x00900000,
	IMAGE_SCN_ALIGN_512BYTES = 0x00A00000,
	IMAGE_SCN_ALIGN_1024BYTES = 0x00B00000,
	IMAGE_SCN_ALIGN_2048BYTES = 0x00C00000,
	IMAGE_SCN_ALIGN_4096BYTES = 0x00D00000,
	IMAGE_SCN_ALIGN_8192BYTES = 0x00E00000,
	IMAGE_SCN_LNK_NRELOC_OVFL = 0x01000000,
	IMAGE_SCN_MEM_DISCARDABLE = 0x02000000,
	IMAGE_SCN_MEM_NOT_CACHED = 0x04000000,
	IMAGE_SCN_MEM_NOT_PAGED = 0x08000000,
	IMAGE_SCN_MEM_SHARED = 0x10000000,
	IMAGE_SCN_MEM_EXECUTE = 0x20000000,
	IMAGE_SCN_MEM_READ = 0x40000000,
	IMAGE_SCN_MEM_WRITE = 0x80000000,
};

static const ppelib_map_entry_t ppelib_section_flags_map[] = {
	{"IMAGE_SCN_RESERVED1", 0x00000000},
	{"IMAGE_SCN_RESERVED2", 0x00000001},
	{"IMAGE_SCN_RESERVED3", 0x00000002},
	{"IMAGE_SCN_RESERVED4", 0x00000004},
	{"IMAGE_SCN_TYPE_NO_PAD", 0x00000008},
	{"IMAGE_SCN_RESERVED5", 0x00000010},
	{"IMAGE_SCN_CNT_CODE", 0x00000020},
	{"IMAGE_SCN_CNT_INITIALIZED_DATA", 0x00000040},
	{"IMAGE_SCN_CNT_UNINITIALIZED_DATA", 0x00000080},
	{"IMAGE_SCN_LNK_OTHER", 0x00000100},
	{"IMAGE_SCN_LNK_INFO", 0x00000200},
	{"IMAGE_SCN_RESERVED6", 0x00000400},
	{"IMAGE_SCN_LNK_REMOVE", 0x00000800},
	{"IMAGE_SCN_LNK_COMDAT", 0x00001000},
	{"IMAGE_SCN_GPREL", 0x00008000},
	{"IMAGE_SCN_MEM_PURGEABLE", 0x00020000},
	{"IMAGE_SCN_MEM_16BIT", 0x00020000},
	{"IMAGE_SCN_MEM_LOCKED", 0x00040000},
	{"IMAGE_SCN_MEM_PRELOAD", 0x00080000},
	{"IMAGE_SCN_ALIGN_1BYTES", 0x00100000},
	{"IMAGE_SCN_ALIGN_2BYTES", 0x00200000},
	{"IMAGE_SCN_ALIGN_4BYTES", 0x00300000},
	{"IMAGE_SCN_ALIGN_8BYTES", 0x00400000},
	{"IMAGE_SCN_ALIGN_16BYTES", 0x00500000},
	{"IMAGE_SCN_ALIGN_32BYTES", 0x00600000},
	{"IMAGE_SCN_ALIGN_64BYTES", 0x00700000},
	{"IMAGE_SCN_ALIGN_128BYTES", 0x00800000},
	{"IMAGE_SCN_ALIGN_256BYTES", 0x00900000},
	{"IMAGE_SCN_ALIGN_512BYTES", 0x00A00000},
	{"IMAGE_SCN_ALIGN_1024BYTES", 0x00B00000},
	{"IMAGE_SCN_ALIGN_2048BYTES", 0x00C00000},
	{"IMAGE_SCN_ALIGN_4096BYTES", 0x00D00000},
	{"IMAGE_SCN_ALIGN_8192BYTES", 0x00E00000},
	{"IMAGE_SCN_LNK_NRELOC_OVFL", 0x01000000},
	{"IMAGE_SCN_MEM_DISCARDABLE", 0x02000000},
	{"IMAGE_SCN_MEM_NOT_CACHED", 0x04000000},
	{"IMAGE_SCN_MEM_NOT_PAGED", 0x08000000},
	{"IMAGE_SCN_MEM_SHARED", 0x10000000},
	{"IMAGE_SCN_MEM_EXECUTE", 0x20000000},
	{"IMAGE_SCN_MEM_READ", 0x40000000},
	{"IMAGE_SCN_MEM_WRITE", 0x80000000},
	{NULL, 0}
};

enum ppelib_resource_types {
	RT_CURSOR = 1,
	RT_BITMAP = 2,
	RT_ICON = 3,
	RT_MENU = 4,
	RT_DIALOG = 5,
	RT_STRING = 6,
	RT_FONTDIR = 7,
	RT_FONT = 8,
	RT_ACCELERATOR = 9,
	RT_RCDATA = 10,
	RT_MESSAGETABLE = 11,
	RT_GROUP_CURSOR = 12,
	RT_GROUP_ICON = 14,
	RT_VERSION = 16,
	RT_DLGINCLUDE = 17,
	RT_PLUGPLAY = 19,
	RT_VXD = 20,
	RT_ANICURSOR = 21,
	RT_ANIICON = 22,
	RT_HTML = 23,
	RT_MANIFEST = 24,
};

static const ppelib_map_entry_t ppelib_resource_types_map[] = {
	{"RT_CURSOR", 1},
	{"RT_BITMAP", 2},
	{"RT_ICON", 3},
	{"RT_MENU", 4},
	{"RT_DIALOG", 5},
	{"RT_STRING", 6},
	{"RT_FONTDIR", 7},
	{"RT_FONT", 8},
	{"RT_ACCELERATOR", 9},
	{"RT_RCDATA", 10},
	{"RT_MESSAGETABLE", 11},
	{"RT_GROUP_CURSOR", 12},
	{"RT_GROUP_ICON", 14},
	{"RT_VERSION", 16},
	{"RT_DLGINCLUDE", 17},
	{"RT_PLUGPLAY", 19},
	{"RT_VXD", 20},
	{"RT_ANICURSOR", 21},
	{"RT_ANIICON", 22},
	{"RT_HTML", 23},
	{"RT_MANIFEST", 24},
	{NULL, 0}
};

enum ppelib_charset_types {
	ASCII = 0x0,
	Japan = 0x3a4,
	Korea = 0x3b5,
	Taiwan = 0x3b6,
	Unicode = 0x4b0,
	Latin2 = 0x4e2,
	Cyrillic = 0x4e3,
	Multilingual = 0x4e4,
	Greek = 0x4e5,
	Turkish = 0x4e6,
	Hebrew = 0x4e7,
	Arabic = 0x4e8,
};

static const ppelib_map_entry_t ppelib_charsets_types_map[] = {
	{"ASCII", 0x0},
	{"Japan", 0x3a4},
	{"Korea", 0x3b5},
	{"Taiwan", 0x3b6},
	{"Unicode", 0x4b0},
	{"Latin2", 0x4e2},
	{"Cyrillic", 0x4e3},
	{"Multilingual", 0x4e4},
	{"Greek", 0x4e5},
	{"Turkish", 0x4e6},
	{"Hebrew", 0x4e7},
	{"Arabic", 0x4e8},
	{NULL, 0}
};

enum ppelib_certificate_revision {
	WIN_CERT_REVISION_1_0 = 0x0100,
	WIN_CERT_REVISION_2_0 = 0x0200,
};

static const ppelib_map_entry_t ppelib_certificate_revision_map[] = {
	{"WIN_CERT_REVISION_1_0", 0x0100},
	{"WIN_CERT_REVISION_2_0", 0x0200},
	{NULL, 0}
};

enum ppelib_certificate_type {
	WIN_CERT_TYPE_X509 = 1,
	WIN_CERT_TYPE_PKCS_SIGNED_DATA = 2,
	WIN_CERT_TYPE_RESERVED_1 = 3,
	WIN_CERT_TYPE_TS_STACK_SIGNED = 4,
};

static const ppelib_map_entry_t ppelib_certificate_type_map[] = {
	{"WIN_CERT_TYPE_X509", 1},
	{"WIN_CERT_TYPE_PKCS_SIGNED_DATA", 2},
	{"WIN_CERT_TYPE_RESERVED_1", 3},
	{"WIN_CERT_TYPE_TS_STACK_SIGNED", 4},
	{NULL, 0}
};
#endif
