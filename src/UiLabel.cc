#include <string>
#include "nbind/api.h"
#include "control.h"
#include "ui.h"

class UiLabel : public UiControl {
  public:
	UiLabel();
	UiLabel(std::string text);
	DEFINE_CONTROL_METHODS()
	void setText(std::string text);
	std::string getText();
};

UiLabel::UiLabel(std::string text)
	: UiControl(uiControl(uiNewLabel(text.c_str()))) {}
UiLabel::UiLabel() : UiControl(uiControl(uiNewLabel(""))) {}

INHERITS_CONTROL_METHODS(UiLabel)

void UiLabel::setText(std::string text) {
	uiLabelSetText(uiLabel(getHandle()), text.c_str());
}

std::string UiLabel::getText() {
	char *char_ptr = uiLabelText(uiLabel(getHandle()));
	std::string s(char_ptr);
	uiFreeText(char_ptr);
	return s;
}

NBIND_CLASS(UiLabel) {
	construct<std::string>();
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
	getset(getText, setText);
	method(getText);
	method(setText);
}
