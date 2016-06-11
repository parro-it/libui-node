#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiSpinbox::UiSpinbox(int min, int max) :
	UiControl( (uiControl*) uiNewSpinbox(min, max) ) {}

int UiSpinbox::getValue() {
	return uiSpinboxValue((uiSpinbox*) getHandle());
}

void UiSpinbox::setValue(int value) {
	uiSpinboxSetValue((uiSpinbox*) getHandle(),value);
}

IMPLEMENT_EVENT(UiSpinbox, uiSpinbox, onChanged, uiSpinboxOnChanged)

INHERITS_CONTROL_METHODS(UiSpinbox)

NBIND_CLASS(UiSpinbox) {
	construct<int, int>();
	DECLARE_CONTROL_METHODS()
	getset(getValue, setValue);
	method(onChanged);
}

