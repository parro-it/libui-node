#include <string>
#include "nbind/api.h"
#include "control.h"
#include "ui.h"

class UiButton : public UiControl {
	DEFINE_EVENT(onClicked)

  public:
	UiButton(std::string text);
	UiButton();
	void setText(std::string text);
	std::string getText();
	~UiButton();
	void onDestroy(uiControl *control) override;
};

void UiButton::onDestroy(uiControl *control) {
	/*
		freeing event callbacks to allow JS to garbage collect this class
		when there are no references to it left in JS code.
	*/
	DISPOSE_EVENT(onClicked);
}

UiButton::~UiButton() {
	// printf("UiButton %p destroyed with wrapper %p.\n", getHandle(), this);
}

UiButton::UiButton(std::string text)
	: UiControl(uiControl(uiNewButton(text.c_str()))) {}

UiButton::UiButton() : UiControl(uiControl(uiNewButton(""))) {}

void UiButton::setText(std::string text) {
	uiButtonSetText(uiButton(getHandle()), text.c_str());
}

std::string UiButton::getText() {
	char *char_ptr = uiButtonText(uiButton(getHandle()));
	std::string s(char_ptr);
	uiFreeText(char_ptr);
	return s;
}

IMPLEMENT_EVENT(UiButton, uiButton, onClicked, uiButtonOnClicked)

NBIND_CLASS(UiButton) {
	inherit(UiControl);
	construct<std::string>();
	construct<>();
	getset(getText, setText);
	method(getText);
	method(setText);
	method(onClicked);
}
