#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiColorButton::UiColorButton() : UiControl( (uiControl*) uiNewColorButton() ) {}

INHERITS_CONTROL_METHODS(UiColorButton)


IMPLEMENT_EVENT(UiColorButton, uiColorButton, onChanged, uiColorButtonOnChanged)

void UiColorButton::setColor( double r, double g, double b, double a) {
	uiColorButtonSetColor(
		(uiColorButton *) getHandle(),
		r, g ,b ,a
	);
	if (onChangedCallback != NULL) {
		(*onChangedCallback)();
	}
}

long UiColorButton::getColor() {
	double r = 0.0;
	double g = 0.0;
	double b = 0.0;
	double a = 0.0;

	uiColorButtonColor(
		(uiColorButton *) getHandle(),
		&r, &g ,&b ,&a
	);

	return ((int(r) & 0xff) << 24) +
		((int(g) & 0xff) << 16) +
		((int(b) & 0xff) << 8) +
		(int(a) & 0xff);
}

NBIND_CLASS(UiColorButton) {
	construct<>();
	DECLARE_CONTROL_METHODS()
	method(setColor);
	method(getColor);
	method(onChanged);

/*	getset(getSelected, setSelected);
	method(getSelected);

	 */
}

