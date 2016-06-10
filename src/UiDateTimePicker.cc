#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiDateTimePicker::UiDateTimePicker() : UiControl( (uiControl*) uiNewDateTimePicker() ) {}

INHERITS_CONTROL_METHODS(UiDateTimePicker)

NBIND_CLASS(UiDateTimePicker) {
	construct<>();
	DECLARE_CONTROL_METHODS()
}

