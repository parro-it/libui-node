#include "nbind/api.h"
#include "control.h"
#include "ui.h"
#include "values.h"

class UiColorButton : public UiControl {
	DEFINE_EVENT(onChanged)

  public:
	UiColorButton();
	Color getColor();
	void setColor(Color value);
	~UiColorButton();
	void onDestroy(uiControl *control) override;
};

void UiColorButton::onDestroy(uiControl *control) {
	/*
		freeing event callbacks to allow JS to garbage collect this class
		when there are no references to it left in JS code.
	*/
	DISPOSE_EVENT(onChanged);
}

UiColorButton::~UiColorButton() {
	// printf("UiColorButton %p destroyed with wrapper %p.\n", getHandle(),
	// this);
}

UiColorButton::UiColorButton() : UiControl((uiControl *)uiNewColorButton()) {}

IMPLEMENT_EVENT(UiColorButton, uiColorButton, onChanged, uiColorButtonOnChanged)

void UiColorButton::setColor(Color color) {
	uiColorButtonSetColor((uiColorButton *)getHandle(), color.getR(),
						  color.getG(), color.getB(), color.getA());
	if (onChangedCallback != NULL) {
		(*onChangedCallback)();
	}
}

Color UiColorButton::getColor() {
	double r = 0.0;
	double g = 0.0;
	double b = 0.0;
	double a = 0.0;

	uiColorButtonColor((uiColorButton *)getHandle(), &r, &g, &b, &a);

	return Color(r, g, b, a);
}

NBIND_CLASS(UiColorButton) {
	inherit(UiControl);
	construct<>();
	method(setColor);
	method(getColor);
	method(onChanged);
	getset(getColor, setColor);
}
