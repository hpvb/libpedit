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

#ifndef PPELIB_{{s.structure|upper}}_PRIVATE_H_
#define PPELIB_{{s.structure|upper}}_PRIVATE_H_

#include <inttypes.h>
#include <stdio.h>
#include <stddef.h>

#include <ppelib/ppelib-constants.h>

typedef struct ppelib_file ppelib_file_t;

#define {{s.structure|upper}}_SIZE {{s.common_size}}

{% for extra_definition in s.extra_definitions -%}
#define {{extra_definition.name|upper}} {{extra_definition.value}}
{% endfor -%}

{% for include in s.extra_includes %}
#include "{{include}}"
{% endfor %}

#include "platform.h"
#include "utils.h"

typedef struct {{s.structure}} {
	{% for field in s.fields -%}
	{% if field.getset_type == "string_name" -%}
	char {{field.struct_name}}[9];
	{% else -%}
	{{field.getset_type}} {{field.struct_name}};
	{% endif -%}
	{% endfor %}

	{% for field in s.extra_fields %}
	{{field.type}} {{field.name}};
	{% endfor %}

	ppelib_file_t *pe;
	char modified;
} {{s.structure}}_t;

{% for field in s.fields %}
{% if field.getset_type == "string_name" -%}
EXPORT_SYM const char* ppelib_{{s.structure}}_get_{{field.struct_name}}(const {{s.structure}}_t* {{s.structure}});
EXPORT_SYM void ppelib_{{s.structure}}_set_{{field.struct_name}}({{s.structure}}_t* {{s.structure}}, const char value[9]);
{% else -%}
EXPORT_SYM {{field.getset_type}} ppelib_{{s.structure}}_get_{{field.struct_name}}(const {{s.structure}}_t* {{s.structure}});
{% if field.set -%}
EXPORT_SYM void ppelib_{{s.structure}}_set_{{field.struct_name}}({{s.structure}}_t* {{s.structure}}, {{field.getset_type}} value);
{% endif -%}
{% if field.format and field.format.enum -%}
EXPORT_SYM const char* ppelib_{{s.structure}}_get_{{field.struct_name}}_string(const {{s.structure}}_t* {{s.structure}});
{% endif -%}
{% endif -%}
{% endfor %}

EXPORT_SYM size_t ppelib_{{s.structure}}_serialize(const {{s.structure}}_t* {{s.structure}}, uint8_t* buffer, const size_t offset);
EXPORT_SYM size_t ppelib_{{s.structure}}_deserialize(const uint8_t* buffer, const size_t size, const size_t offset, {{s.structure}}_t* {{s.structure}});
EXPORT_SYM void ppelib_{{s.structure}}_fprint(FILE* stream, const {{s.structure}}_t* {{s.structure}});
EXPORT_SYM void ppelib_{{s.structure}}_print(const {{s.structure}}_t* {{s.structure}});
EXPORT_SYM uint8_t ppelib_{{s.structure}}_is_null(const {{s.structure}}_t* {{s.structure}});

#endif /* PPELIB_{{s.structure|upper}}_PRIVATE_H_  */
