#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiRadioButtons::UiRadioButtons() : UiControl( (uiControl*) uiNewRadioButtons() ) {}

INHERITS_CONTROL_METHODS(UiRadioButtons)



void UiRadioButtons::append(const char *text) {
	uiRadioButtonsAppend(
		(uiRadioButtons *) getHandle(),
		text
	);
}


NBIND_CLASS(UiRadioButtons) {
	construct<>();
	DECLARE_CONTROL_METHODS()
	method(append);
}


