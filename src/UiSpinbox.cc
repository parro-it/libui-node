#include <memory>
#include "nbind/api.h"
#include "control.h"
#include "ui.h"

class UiSpinbox : public UiControl {
  public:
	DEFINE_EVENT(onChanged)

	UiSpinbox(int min, int max);
	UiSpinbox();
	int getValue();
	void setValue(int value);
	~UiSpinbox();
	void onDestroy(uiControl *control) override;
};

UiSpinbox::~UiSpinbox() {
	// printf("UiSpinbox %p destroyed with wrapper %p.\n", getHandle(), this);
}

void UiSpinbox::onDestroy(uiControl *control) {
	/*
		freeing event callbacks to allow JS to garbage collect this class
		when there are no references to it left in JS code.
	*/
	DISPOSE_EVENT(onChanged);
}

UiSpinbox::UiSpinbox(int min, int max)
	: UiControl((uiControl *)uiNewSpinbox(min, max)) {}

UiSpinbox::UiSpinbox() : UiControl((uiControl *)uiNewSpinbox(0, 100)) {}

int UiSpinbox::getValue() {
	return uiSpinboxValue((uiSpinbox *)getHandle());
}

void UiSpinbox::setValue(int value) {
	uiSpinboxSetValue((uiSpinbox *)getHandle(), value);
	if (onChangedCallback != nullptr) {
		(*onChangedCallback)();
	}
}

IMPLEMENT_EVENT(UiSpinbox, uiSpinbox, onChanged, uiSpinboxOnChanged)

NBIND_CLASS(UiSpinbox) {
	inherit(UiControl);
	construct<int, int>();
	construct<>();
	getset(getValue, setValue);
	method(getValue);
	method(setValue);
	method(onChanged);
}
