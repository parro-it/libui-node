#include "../ui.h"
#include "nbind/api.h"
#include "includes/area.h"
#include "includes/control.h"
#include "includes/values.h"

class UiFontButton : public UiControl {
	DEFINE_EVENT(onChanged)

  public:
	UiFontButton();
	DrawTextFont *getFont();
	DEFINE_CONTROL_METHODS()
};

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
