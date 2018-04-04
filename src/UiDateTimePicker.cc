#include "../ui.h"
#include "ui-node.h"
#include "nbind/api.h"

UiDateTimePicker::UiDateTimePicker()
	: UiControl((uiControl *)uiNewDateTimePicker()) {}

INHERITS_CONTROL_METHODS(UiDateTimePicker)

NBIND_CLASS(UiDateTimePicker) {
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
}

UiTimePicker::UiTimePicker() : UiControl((uiControl *)uiNewTimePicker()) {}

INHERITS_CONTROL_METHODS(UiTimePicker)

NBIND_CLASS(UiTimePicker) {
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
}

UiDatePicker::UiDatePicker() : UiControl((uiControl *)uiNewDatePicker()) {}

INHERITS_CONTROL_METHODS(UiDatePicker)

NBIND_CLASS(UiDatePicker) {
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
}
