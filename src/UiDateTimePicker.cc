#include "../ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiDateTimePicker::UiDateTimePicker() : UiControl( (uiControl*) uiNewDateTimePicker() ) {}

INHERITS_CONTROL_METHODS(UiDateTimePicker)

NBIND_CLASS(UiDateTimePicker) {
	construct<>();
	DECLARE_CONTROL_METHODS()
}



UiTimePicker::UiTimePicker() : UiControl( (uiControl*) uiNewTimePicker() ) {}

INHERITS_CONTROL_METHODS(UiTimePicker)

NBIND_CLASS(UiTimePicker) {
	construct<>();
	DECLARE_CONTROL_METHODS()
}


UiDatePicker::UiDatePicker() : UiControl( (uiControl*) uiNewDatePicker() ) {}

INHERITS_CONTROL_METHODS(UiDatePicker)

NBIND_CLASS(UiDatePicker) {
	construct<>();
	DECLARE_CONTROL_METHODS()
}


