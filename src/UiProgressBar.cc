#include "../ui.h"
#include "ui-node.h"
#include "nbind/api.h"
#include "nbind/nbind.h"

UiProgressBar::UiProgressBar() : UiControl((uiControl *)uiNewProgressBar()) {}

INHERITS_CONTROL_METHODS(UiProgressBar)

void UiProgressBar::setValue(int val) {
	value = val;
	uiProgressBarSetValue((uiProgressBar *)getHandle(), value);
}

int UiProgressBar::getValue() {
	return value;
}

NBIND_CLASS(UiProgressBar) {
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
	getset(getValue, setValue);
	method(getValue);
	method(setValue);
}
