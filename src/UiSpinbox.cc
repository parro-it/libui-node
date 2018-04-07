#include "../ui.h"
#include "nbind/api.h"
#include "includes/control.h"

class UiSpinbox : public UiControl {
	DEFINE_EVENT(onChanged)

  public:
	UiSpinbox(int min, int max);
	UiSpinbox();
	DEFINE_CONTROL_METHODS()

	int getValue();
	void setValue(int value);
};
UiSpinbox::UiSpinbox(int min, int max)
	: UiControl((uiControl *)uiNewSpinbox(min, max)) {}

UiSpinbox::UiSpinbox() : UiControl((uiControl *)uiNewSpinbox(0, 100)) {}

int UiSpinbox::getValue() {
	return uiSpinboxValue((uiSpinbox *)getHandle());
}

void UiSpinbox::setValue(int value) {
	uiSpinboxSetValue((uiSpinbox *)getHandle(), value);
	if (onChangedCallback != NULL) {
		(*onChangedCallback)();
	}
}

IMPLEMENT_EVENT(UiSpinbox, uiSpinbox, onChanged, uiSpinboxOnChanged)

INHERITS_CONTROL_METHODS(UiSpinbox)

NBIND_CLASS(UiSpinbox) {
	construct<int, int>();
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
	getset(getValue, setValue);
	method(getValue);
	method(setValue);
	method(onChanged);
}
