#include "../ui.h"
#include "ui-node.h"
#include "nbind/api.h"

UiEditableCombobox::UiEditableCombobox()
	: UiControl((uiControl *)uiNewEditableCombobox()) {}

INHERITS_CONTROL_METHODS(UiEditableCombobox)

IMPLEMENT_EVENT(UiEditableCombobox, uiEditableCombobox, onChanged,
				uiEditableComboboxOnChanged)

void UiEditableCombobox::append(const char *text) {
	uiEditableComboboxAppend((uiEditableCombobox *)getHandle(), text);
}

void UiEditableCombobox::setText(const char *text) {
	uiEditableComboboxSetText((uiEditableCombobox *)getHandle(), text);
	if (onChangedCallback != NULL) {
		(*onChangedCallback)();
	}
}

const char *UiEditableCombobox::getText() {
	return uiEditableComboboxText((uiEditableCombobox *)getHandle());
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
