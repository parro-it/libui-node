#include <string>
#include "nbind/api.h"
#include "control.h"
#include "ui.h"

class UiEditableCombobox : public UiControl {
	DEFINE_EVENT(onChanged)

  public:
	UiEditableCombobox();
	DEFINE_CONTROL_METHODS()
	void append(std::string text);
	std::string getText();
	void setText(std::string text);
};

UiEditableCombobox::UiEditableCombobox()
	: UiControl(uiControl(uiNewEditableCombobox())) {}

INHERITS_CONTROL_METHODS(UiEditableCombobox)

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
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
	method(append);
	getset(getText, setText);
	method(getText);
	method(setText);
	method(onChanged);
}
