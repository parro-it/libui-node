#include "nbind/api.h"
#include "control.h"
#include "ui.h"

class UiSlider : public UiControl {
	DEFINE_EVENT(onChanged)

  public:
	UiSlider(int min, int max);
	UiSlider();
	int getValue();
	void setValue(int value);
	~UiSlider();
	void onDestroy(uiControl *control) override;
};

UiSlider::~UiSlider() {
	// printf("UiSlider %p destroyed with wrapper %p.\n", getHandle(),
	// 	   this);
}

void UiSlider::onDestroy(uiControl *control) {
	/*
		freeing event callbacks to allow JS to garbage collect this class
		when there are no references to it left in JS code.
	*/
	DISPOSE_EVENT(onChanged);
}

UiSlider::UiSlider(int min, int max)
	: UiControl((uiControl *)uiNewSlider(min, max)) {}

UiSlider::UiSlider() : UiControl((uiControl *)uiNewSlider(0, 100)) {}

int UiSlider::getValue() {
	return uiSliderValue((uiSlider *)getHandle());
}

void UiSlider::setValue(int value) {
	uiSliderSetValue((uiSlider *)getHandle(), value);
	if (onChangedCallback != NULL) {
		(*onChangedCallback)();
	}
}

IMPLEMENT_EVENT(UiSlider, uiSlider, onChanged, uiSliderOnChanged)

NBIND_CLASS(UiSlider) {
	inherit(UiControl);
	construct<int, int>();
	construct<>();
	getset(getValue, setValue);
	method(getValue);
	method(setValue);
	method(onChanged);
}
