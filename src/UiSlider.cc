#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiSlider::UiSlider(int min, int max) :
	UiControl( (uiControl*) uiNewSlider(min, max) ) {}

int UiSlider::getValue() {
	return uiSliderValue((uiSlider*) getHandle());
}

void UiSlider::setValue(int value) {
	uiSliderSetValue((uiSlider*) getHandle(),value);
}


INHERITS_CONTROL_METHODS(UiSlider)

NBIND_CLASS(UiSlider) {
	construct<int, int>();
	DECLARE_CONTROL_METHODS()
	getset(getValue, setValue);
}

