#include "../ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiSlider::UiSlider(int min, int max) :
	UiControl( (uiControl*) uiNewSlider(min, max) ) {}

UiSlider::UiSlider() : UiControl( (uiControl*) uiNewSlider(0, 100) ) {}

int UiSlider::getValue() {
	return uiSliderValue((uiSlider*) getHandle());
}

void UiSlider::setValue(int value) {
	uiSliderSetValue((uiSlider*) getHandle(),value);
	if (onChangedCallback != NULL) {
		(*onChangedCallback)();
	}
}

IMPLEMENT_EVENT(UiSlider, uiSlider, onChanged, uiSliderOnChanged)


INHERITS_CONTROL_METHODS(UiSlider)

NBIND_CLASS(UiSlider) {
	construct<int, int>();
	construct<>();
	DECLARE_CONTROL_METHODS()
	getset(getValue, setValue);
	method(getValue);
	method(setValue);
	method(onChanged);
}

