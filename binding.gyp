{
	"targets": [
		{
			"target_name": "nbind",
			'include_dirs': ["<(module_root_dir)/src/includes", "<(module_root_dir)"],
			"includes": [
				"auto.gypi"
			],
			"conditions": [
				["OS=='win'", {
					"sources": [
						'<!@(node list-sources.js)',
					],
					"libraries": [
						"<(module_root_dir)/libui.lib"
					],
					'msvs_settings': {
						'VCCLCompilerTool': {
							'AdditionalOptions': [
								'/MD',
								'/LD'
							]
						}
					},
				}],
				["OS=='linux'", {
					"sources": [
						"<!@(ls -1 src/*.cc)",
						"<!@(ls -1 src/Font/*.cc)",
						"<!@(ls -1 src/UiArea/*.cc)",
						"<!@(ls -1 src/arch/unix/*.cc)"
					],
					"cflags": ["-fvisibility=hidden"],
					'ldflags': [
						"-Wl,-rpath,'$$ORIGIN',-rpath,<(module_root_dir)",
					],
					"libraries": [
						"<(module_root_dir)/libui.so"
					],
					'include_dirs': [
						'<!@(pkg-config gtk+-3.0 --cflags-only-I | sed s/-I//g)'
					]
				}],
				["OS=='mac'", {
					"sources": [
						"<!@(ls -1 src/*.cc)",
						"<!@(ls -1 src/Font/*.cc)",
						"<!@(ls -1 src/UiArea/*.cc)",
						"<!@(ls -1 src/arch/darwin/*.mm)"
					],
					"xcode_settings": {
						"OTHER_LDFLAGS": [
							"-fvisibility=hidden",
							"-L<(module_root_dir)",
							"-lui",
							"-rpath",
							"'@loader_path'",
							"-rpath",
							"<(module_root_dir)"
						]
					}
				}],
			]
		},
		{
			"target_name": "copy_binary",
			"type":"none",
			"dependencies": [ "nbind" ],
			"copies": [
				{
					'destination': '<(module_root_dir)',
					'files': ['<(module_root_dir)/build/Release/nbind.node']
				}
			]
	   }
	],
	"includes": [
		"auto-top.gypi"
	]
}
