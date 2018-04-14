#include "nbind/api.h"
#include "area.h"
#include "control.h"
#include "ui.h"
#include "values.h"

class UiFontButton : public UiControl {
	DEFINE_EVENT(onChanged)

  public:
	UiFontButton();
	DrawTextFont *getFont();
	~UiFontButton();
	void onDestroy(uiControl *control) override;
};

UiFontButton::~UiFontButton() {
	// printf("UiFontButton %p destroyed with wrapper %p.\n", getHandle(),
	// this);
}

void UiFontButton::onDestroy(uiControl *control) {
	/*
		freeing event callbacks to allow JS to garbage collect this class
		when there are no references to it left in JS code.
	*/
	DISPOSE_EVENT(onChanged);
}

UiFontButton::UiFontButton() : UiControl((uiControl *)uiNewFontButton()) {}

IMPLEMENT_EVENT(UiFontButton, uiFontButton, onChanged, uiFontButtonOnChanged)

DrawTextFont *UiFontButton::getFont() {
	return new DrawTextFont(uiFontButtonFont((uiFontButton *)getHandle()));
}

NBIND_CLASS(UiFontButton) {
	inherit(UiControl);
	construct<>();
	method(getFont);
	method(onChanged);
}
