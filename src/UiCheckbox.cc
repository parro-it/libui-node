#include "../ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"

IMPLEMENT_EVENT(UiCheckbox, uiCheckbox, onToggled, uiCheckboxOnToggled)


UiCheckbox::UiCheckbox(const char *text) : UiControl( (uiControl*) uiNewCheckbox(text) ) {}
UiCheckbox::UiCheckbox() : UiControl( (uiControl*) uiNewCheckbox("") ) {}

INHERITS_CONTROL_METHODS(UiCheckbox)

void UiCheckbox::setText(const char * text) {
	uiCheckboxSetText((uiCheckbox *) getHandle(), text);
}

const char * UiCheckbox::getText() {
	return uiCheckboxText((uiCheckbox *) getHandle());
}

void UiCheckbox::setChecked(bool checked) {
	uiCheckboxSetChecked((uiCheckbox *) getHandle(), checked);
	if (onToggledCallback != NULL) {
		(*onToggledCallback)();
	}
}

bool UiCheckbox::getChecked() {
	return uiCheckboxChecked((uiCheckbox *) getHandle());
}


NBIND_CLASS(UiCheckbox) {
	construct<const char *>();
	construct<>();
	DECLARE_CONTROL_METHODS()
	getset(getChecked, setChecked);
	getset(getText, setText);
	method(getChecked);
	method(setChecked);
	method(getText);
	method(setText);
	method(onToggled);
}

