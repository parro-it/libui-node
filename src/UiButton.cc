#include "../ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiButton::UiButton(const char *text) : UiControl( (uiControl*) uiNewButton(text) ) {}
UiButton::UiButton() : UiControl( (uiControl*) uiNewButton("") ) {}

INHERITS_CONTROL_METHODS(UiButton)



void UiButton::setText(const char * text) {
	uiButtonSetText((uiButton *) getHandle(), text);
}

const char * UiButton::getText() {
	return uiButtonText((uiButton *) getHandle());
}


IMPLEMENT_EVENT(UiButton, uiButton, onClicked, uiButtonOnClicked)


NBIND_CLASS(UiButton) {
	construct<const char *>();
	construct<>();
	DECLARE_CONTROL_METHODS()
	getset(getText, setText);
	method(getText);
	method(setText);
	method(onClicked);
}

