#include <string>
#include "../ui.h"
#include "nbind/api.h"
#include "includes/control.h"

class UiButton : public UiControl {
	DEFINE_EVENT(onClicked)

  public:
	UiButton(std::string text);
	UiButton();
	DEFINE_CONTROL_METHODS()
	void setText(std::string text);
	std::string getText();
};

UiButton::UiButton(std::string text)
	: UiControl(uiControl(uiNewButton(text.c_str()))) {}
UiButton::UiButton() : UiControl(uiControl(uiNewButton(""))) {}

INHERITS_CONTROL_METHODS(UiButton)

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
	construct<std::string>();
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
	getset(getText, setText);
	method(getText);
	method(setText);
	method(onClicked);
}
