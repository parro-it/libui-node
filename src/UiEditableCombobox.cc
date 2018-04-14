#include <string>
#include "nbind/api.h"
#include "control.h"
#include "ui.h"

class UiEditableCombobox : public UiControl {
	DEFINE_EVENT(onChanged)

  public:
	UiEditableCombobox();
	void append(std::string text);
	std::string getText();
	void setText(std::string text);
	~UiEditableCombobox();
	void onDestroy(uiControl *control) override;
};

UiEditableCombobox::~UiEditableCombobox() {
	// printf("UiEditableCombobox %p destroyed with wrapper %p.\n", getHandle(),
	//	   this);
}

void UiEditableCombobox::onDestroy(uiControl *control) {
	/*
		freeing event callbacks to allow JS to garbage collect this class
		when there are no references to it left in JS code.
	*/
	DISPOSE_EVENT(onChanged);
}

UiEditableCombobox::UiEditableCombobox()
	: UiControl(uiControl(uiNewEditableCombobox())) {}

IMPLEMENT_EVENT(UiEditableCombobox, uiEditableCombobox, onChanged,
				uiEditableComboboxOnChanged)

void UiEditableCombobox::append(std::string text) {
	uiEditableComboboxAppend(uiEditableCombobox(getHandle()), text.c_str());
}

void UiEditableCombobox::setText(std::string text) {
	uiEditableComboboxSetText(uiEditableCombobox(getHandle()), text.c_str());
	if (onChangedCallback != NULL) {
		(*onChangedCallback)();
	}
}

std::string UiEditableCombobox::getText() {
	char *char_ptr = uiEditableComboboxText(uiEditableCombobox(getHandle()));
	std::string s(char_ptr);
	uiFreeText(char_ptr);
	return s;
}

NBIND_CLASS(UiEditableCombobox) {
	inherit(UiControl);
	method(append);
	construct<>();
	getset(getText, setText);
	method(getText);
	method(setText);
	method(onChanged);
}
