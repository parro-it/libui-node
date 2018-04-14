#include "../ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"

UiFontButton::UiFontButton() : UiControl((uiControl*)uiNewFontButton()) {}

INHERITS_CONTROL_METHODS(UiFontButton)

IMPLEMENT_EVENT(UiFontButton, uiFontButton, onChanged, uiFontButtonOnChanged)

FontDescriptor UiFontButton::getFont() {
	uiFontDescriptor *desc = new uiFontDescriptor();
	uiFontButtonFont((uiFontButton*)getHandle(), desc);
	return FontDescriptor(desc);
}

NBIND_CLASS(UiFontButton) {
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
	getter(getFont);
	method(getFont);
	method(onChanged);
}
