{
	"targets": [
		{
			"includes": [
				"auto.gypi"

			],
			"sources": [
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
				["OS=='linux'", {
					"sources": [
						"src/arch/unix/EventLoop.cc",
						"src/arch/unix/uiConnectionNumber.cc"
					],
					'ldflags': [
						'-Wl,-rpath,<(module_root_dir)',
					],
					"libraries": [
						"<(module_root_dir)/libui.so"
					],
					'include_dirs': [
						'/usr/include/gtk-3.0',
						'/usr/include/glib-2.0',
						'/usr/lib/x86_64-linux-gnu/glib-2.0/include',
						'/usr/include/at-spi2-atk/2.0 ',
						'/usr/include/at-spi-2.0 ',
						'/usr/include/dbus-1.0 ',
						'/usr/lib/x86_64-linux-gnu/dbus-1.0/include ',
						'/usr/include/gtk-3.0 ',
						'/usr/include/gio-unix-2.0/ ',
						'/usr/include/mirclient ',
						'/usr/include/mircommon ',
						'/usr/include/mircookie ',
						'/usr/include/cairo ',
						'/usr/include/pango-1.0 ',
						'/usr/include/harfbuzz ',
						'/usr/include/pango-1.0 ',
						'/usr/include/atk-1.0 ',
						'/usr/include/cairo ',
						'/usr/include/pixman-1 ',
						'/usr/include/freetype2 ',
						'/usr/include/libpng12 ',
						'/usr/include/gdk-pixbuf-2.0 ',
						'/usr/include/libpng12 ',
						'/usr/include/glib-2.0 '
					]
				}],
				["OS=='mac'", {
					"sources": [
						"src/arch/darwin/EventLoop.mm"
					],
					"xcode_settings": {
						"OTHER_LDFLAGS": [
							"-L<(module_root_dir)",
							"-lui",
							"-rpath",
							"<(module_root_dir)"
						]
					}
				}],
			]
		}
	],
	"includes": [
		"auto-top.gypi"
	]
}
