subdir('generated')

if cc.get_id() != 'msvc'
	if cc.get_argument_syntax() == 'gcc'
		extra_args = ['-fvisibility=hidden']
	else
		if cc.has_argument('-fvisibility=hidden')
			extra_args = ['-fvisibility=hidden']
		endif
	endif
else
	extra_args = []
endif

ppelib_sources = [
	'dos_header/dos_header.c',
	'dos_header/rich_table.c',
	'dos_header/vlv_signature.c',
	'header/data_directory.c',
	'header/header.c',
	'header/import_table.c',
	'main.c',
	'ppe_error.c',
	'section.c',
	'string_table.c',
	'utils.c',
#	'ppelib-certificates.c',
#	'ppelib-handles.c',
#	'ppelib-headers.c',
#	'ppelib-resource-table.c',
	gen_src,
	gen_h
]

ppelib = shared_library(
	'ppelib',
	ppelib_sources,
	c_args: extra_args,
	include_directories: inc,
	install: true,
	version: meson.project_version(),
	soversion: 0
)
