{
	"targets": [
		{
			"includes": [
				"auto.gypi"
			],
			"sources": [
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
				["OS!='mac'", {
					'ldflags': [
            					'-Wl,-rpath,<(module_root_dir)',
          				],
					"libraries": [
						".."
					]
				}]
			],
			"xcode_settings": {
				"OTHER_LDFLAGS": [
					"-L.",
					"-lui",
					"-rpath",
					"."
				]
			}
		}
	],
	"includes": [
		"auto-top.gypi"
	]
}
