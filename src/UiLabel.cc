#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiLabel::UiLabel(const char *text) : UiControl( (uiControl*) uiNewLabel(text) ) {}

INHERITS_CONTROL_METHODS(UiLabel)


void UiLabel::setText(const char * text) {
	uiLabelSetText((uiLabel *) getHandle(), text);
}

const char * UiLabel::getText() {
	return uiLabelText((uiLabel *) getHandle());
}


NBIND_CLASS(UiLabel) {
	construct<const char *>();
	DECLARE_CONTROL_METHODS()
	getset(getText, setText);
}

