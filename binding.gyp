{
	"targets": [
		{
			"includes": [
				"auto.gypi"
			],
			"sources": [
				"src/UiGroup.cc",
				"src/UiTab.cc",
				"src/UiCheckbox.cc",
				"src/UiBox.cc",
				"src/UiEntry.cc",
				"src/UiMultilineEntry.cc",
				"src/UiDateTimePicker.cc",
				"src/UiRadioButtons.cc",
				"src/UiCombobox.cc",
				"src/UiEditableCombobox.cc",
				"src/UiSeparator.cc",
				"src/UiProgressBar.cc",
				"src/UiSlider.cc",
				"src/UiSpinbox.cc",
				"src/Ui.cc",
				"src/UiWindow.cc",
				"src/UiControl.cc",
				"src/UiLabel.cc",
				"src/UiButton.cc",
			],
			"libraries": [
				"../libui/build/out/libui.so"

			]
		}
	],
	"includes": [
		"auto-top.gypi"
	]
}
