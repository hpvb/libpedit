#!/usr/bin/env python3

# Copyright 2021 Hein-Pieter van Braam-Stewart
#
# This file is part of ppelib (Portable Portable Executable LIBrary)
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import os
import sys
from generator import generate

outdir = sys.argv[1]
mydir = os.path.dirname(os.path.abspath(__file__))

header = [
    ["getset_structure.c", "header_getset.c" ],
    ["header_deserialize.c", "header_deserialize.c"],
    ["header_serialize.c", "header_serialize.c"],
    ["print_structure.c", "header_print.c"],
    ["private_header.h", "header_private.h"]
]

standard_structures = [
    "coff_symbol",
    "dos_header",
    "export_directory_table",
    "import_directory_table",
    "section",
    "vlv_signature",
]

standard_files = [
    ["getset_structure.c", "_getset.c"],
    ["print_structure.c", "_print.c"],
    ["private_header.h", "_private.h"],
    ["structure_deserialize.c", "_deserialize.c"],
    ["structure_serialize.c", "_serialize.c"],
]

for file in header:
    generate(f"{mydir}/structures/header.yaml", f"{mydir}/templates/{file[0]}", f"{outdir}/{file[1]}")

for structure in standard_structures:
    for file in standard_files:
        generate(f"{mydir}/structures/{structure}.yaml", f"{mydir}/templates/{file[0]}", f"{outdir}/{structure}{file[1]}")
