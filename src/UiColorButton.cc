#include "../ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiColorButton::UiColorButton() : UiControl( (uiControl*) uiNewColorButton() ) {}

INHERITS_CONTROL_METHODS(UiColorButton)


IMPLEMENT_EVENT(UiColorButton, uiColorButton, onChanged, uiColorButtonOnChanged)

void UiColorButton::setColor(Color color) {
	uiColorButtonSetColor(
		(uiColorButton *) getHandle(),
		color.getR(), color.getG(), color.getB() ,color.getA()
	);
	if (onChangedCallback != NULL) {
		(*onChangedCallback)();
	}
}

Color UiColorButton::getColor() {
	double r = 0.0;
	double g = 0.0;
	double b = 0.0;
	double a = 0.0;

	uiColorButtonColor(
		(uiColorButton *) getHandle(),
		&r, &g ,&b ,&a
	);

	return Color(r, g, b, a);
}

NBIND_CLASS(UiColorButton) {
	construct<>();
	DECLARE_CONTROL_METHODS()
	method(setColor);
	method(getColor);
	method(onChanged);
	getset(getColor, setColor);

}

