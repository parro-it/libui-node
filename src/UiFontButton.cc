#include "nbind/api.h"
#include "area.h"
#include "control.h"
#include "ui.h"
#include "values.h"

class UiFontButton : public UiControl {
	DEFINE_EVENT(onChanged)

  public:
	UiFontButton();
	~UiFontButton();
	FontDescriptor getFont();
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

FontDescriptor UiFontButton::getFont() {
	uiFontDescriptor *desc = new uiFontDescriptor();
	uiFontButtonFont((uiFontButton *)getHandle(), desc);
	return FontDescriptor(desc);
}

NBIND_CLASS(UiFontButton) {
	inherit(UiControl);
	construct<>();
	getter(getFont);
	method(getFont);
	method(onChanged);
}
