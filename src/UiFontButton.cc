#include "../ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"

UiFontButton::UiFontButton() : UiControl((uiControl*)uiNewFontButton()) {}

INHERITS_CONTROL_METHODS(UiFontButton)

IMPLEMENT_EVENT(UiFontButton, uiFontButton, onChanged, uiFontButtonOnChanged)

UiFontDescriptor* UiFontButton::getFont() {
	uiFontDescriptor *desc = new uiFontDescriptor();
	uiFontButtonFont((uiFontButton*)getHandle(), desc);
	return new UiFontDescriptor(desc);
}

NBIND_CLASS(UiFontButton) {
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
	method(getFont);
	method(onChanged);
}
