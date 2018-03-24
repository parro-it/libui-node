{
	"targets": [
		{
			"target_name": "nbind",
			"includes": [
				"auto.gypi"
			],
			"sources": [
				"src/EventLoop.cc",
				"src/UiFontButton.cc",
				"src/UiArea/DrawTextFont.cc",
				"src/UiArea/DrawTextFontDescriptor.cc",
				"src/UiArea/DrawTextFontMetrics.cc",
				"src/UiArea/DrawTextLayout.cc",
				"src/UiArea/UiArea.cc",
				"src/UiArea/DrawStrokeParams.cc",
				"src/UiArea/UiDrawContext.cc",
				"src/UiArea/UiDrawPath.cc",
				"src/UiArea/DrawBrush.cc",
				"src/SizeDouble.cc",
				"src/PointDouble.cc",
				"src/UiArea/DrawMatrix.cc",
				"src/UiArea/BrushGradientStop.cc",
				"src/UiArea/UiAreaDrawParams.cc",
				"src/UiArea/UiAreaKeyEvent.cc",
				"src/UiArea/UiAreaMouseEvent.cc",
				"src/UiArea/UiAreaHandler.cc",
				"src/UiGrid.cc",
				"src/UiForm.cc",
				"src/Size.cc",
				"src/Point.cc",
				"src/Color.cc",
				"src/UiColorButton.cc",
				"src/UiDialogs.cc",
				"src/UiMenu.cc",
				"src/UiCombobox.cc",
				"src/UiSlider.cc",
				"src/UiSpinbox.cc",
				"src/UiCheckbox.cc",
				"src/UiWindow.cc",
				"src/UiEntry.cc",
				"src/UiMultilineEntry.cc",
				"src/UiRadioButtons.cc",
				"src/UiEditableCombobox.cc",
				"src/UiGroup.cc",
				"src/UiTab.cc",
				"src/UiBox.cc",
				"src/UiDateTimePicker.cc",
				"src/UiSeparator.cc",
				"src/UiProgressBar.cc",
				"src/Ui.cc",
				"src/UiControl.cc",
				"src/UiLabel.cc",
				"src/UiButton.cc",
			],
			"conditions": [
				["OS=='win'", {
					"sources": [
						"src/arch/win32/libui_loop.cc",
						"src/arch/win32/usleep.cc"
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
						"src/arch/unix/libui_loop.cc"
					],
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
						"src/arch/darwin/libui_loop.mm"
					],
					"xcode_settings": {
						"OTHER_LDFLAGS": [
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
