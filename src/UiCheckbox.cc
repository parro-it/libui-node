#include <string>
#include "nbind/api.h"
#include "control.h"
#include "ui.h"

class UiCheckbox : public UiControl {
	DEFINE_EVENT(onToggled)

  public:
	UiCheckbox(std::string text);
	UiCheckbox();
	void setText(std::string text);
	std::string getText();
	void setChecked(bool checked);
	bool getChecked();
	~UiCheckbox();
	void onDestroy(uiControl *control) override;
};

void UiCheckbox::onDestroy(uiControl *control) {
	/*
		freeing event callbacks to allow JS to garbage collect this class
		when there are no references to it left in JS code.
	*/
	DISPOSE_EVENT(onToggled);
}

UiCheckbox::~UiCheckbox() {
	// printf("UiCheckbox %p destroyed with wrapper %p.\n", getHandle(), this);
}

IMPLEMENT_EVENT(UiCheckbox, uiCheckbox, onToggled, uiCheckboxOnToggled)

UiCheckbox::UiCheckbox(std::string text)
	: UiControl(uiControl(uiNewCheckbox(text.c_str()))) {}
UiCheckbox::UiCheckbox() : UiControl(uiControl(uiNewCheckbox(""))) {}

void UiCheckbox::setText(std::string text) {
	uiCheckboxSetText(uiCheckbox(getHandle()), text.c_str());
}

std::string UiCheckbox::getText() {
	char *char_ptr = uiCheckboxText(uiCheckbox(getHandle()));
	std::string s(char_ptr);
	uiFreeText(char_ptr);
	return s;
}

void UiCheckbox::setChecked(bool checked) {
	uiCheckboxSetChecked(uiCheckbox(getHandle()), checked);
	if (onToggledCallback != NULL) {
		(*onToggledCallback)();
	}
}

bool UiCheckbox::getChecked() {
	return uiCheckboxChecked(uiCheckbox(getHandle()));
}

NBIND_CLASS(UiCheckbox) {
	inherit(UiControl);
	construct<std::string>();
	construct<>();
	getset(getChecked, setChecked);
	getset(getText, setText);
	method(getChecked);
	method(setChecked);
	method(getText);
	method(setText);
	method(onToggled);
}
