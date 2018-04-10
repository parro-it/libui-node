#include "../ui.h"
#include "ui-node.h"
#include "nbind/api.h"
#include "nbind/nbind.h"

UiFontButton::UiFontButton() : UiControl((uiControl *)uiNewFontButton()) {}

INHERITS_CONTROL_METHODS(UiFontButton)

IMPLEMENT_EVENT(UiFontButton, uiFontButton, onChanged, uiFontButtonOnChanged)

DrawTextFont *UiFontButton::getFont() {
	return new DrawTextFont(uiFontButtonFont((uiFontButton *)getHandle()));
}

NBIND_CLASS(UiFontButton) {
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
	method(getFont);
	method(onChanged);
}
