#include "../ui.h"
#include "ui-node.h"
#include "nbind/api.h"

UiButton::UiButton(const char *text)
	: UiControl((uiControl *)uiNewButton(text)) {}
UiButton::UiButton() : UiControl((uiControl *)uiNewButton("")) {}

INHERITS_CONTROL_METHODS(UiButton)

void UiButton::setText(const char *text) {
	uiButtonSetText((uiButton *)getHandle(), text);
}

const char *UiButton::getText() {
	return uiButtonText((uiButton *)getHandle());
}

IMPLEMENT_EVENT(UiButton, uiButton, onClicked, uiButtonOnClicked)

NBIND_CLASS(UiButton) {
	construct<const char *>();
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
	getset(getText, setText);
	method(getText);
	method(setText);
	method(onClicked);
}
