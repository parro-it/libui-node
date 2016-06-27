#include "../ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiRadioButtons::UiRadioButtons() : UiControl( (uiControl*) uiNewRadioButtons() ) {}

INHERITS_CONTROL_METHODS(UiRadioButtons)

IMPLEMENT_EVENT(UiRadioButtons, uiRadioButtons, onSelected, uiRadioButtonsOnSelected)


int UiRadioButtons::getSelected() {
	return uiRadioButtonsSelected( (uiRadioButtons *) getHandle() );
}

void UiRadioButtons::setSelected(int n) {
	uiRadioButtonsSetSelected(
		(uiRadioButtons *) getHandle(),
		n
	);
	if (onSelectedCallback != NULL) {
		(*onSelectedCallback)();
	}
}

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
	getset(getSelected, setSelected);
	method(getSelected);
	method(setSelected);
	method(onSelected);
}


