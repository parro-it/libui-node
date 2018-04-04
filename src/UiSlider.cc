#include "../ui.h"
#include "ui-node.h"
#include "nbind/api.h"

class UiSlider : public UiControl {
	DEFINE_EVENT(onChanged)

  public:
	UiSlider(int min, int max);
	UiSlider();
	DEFINE_CONTROL_METHODS()

	int getValue();
	void setValue(int value);
};

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

INHERITS_CONTROL_METHODS(UiSlider)

NBIND_CLASS(UiSlider) {
	construct<int, int>();
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
	getset(getValue, setValue);
	method(getValue);
	method(setValue);
	method(onChanged);
}
