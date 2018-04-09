#include "../ui.h"
#include "ui-node.h"
#include "nbind/api.h"
#include "nbind/nbind.h"

UiLabel::UiLabel(const char *text) : UiControl((uiControl *)uiNewLabel(text)) {}
UiLabel::UiLabel() : UiControl((uiControl *)uiNewLabel("")) {}

INHERITS_CONTROL_METHODS(UiLabel)

void UiLabel::setText(const char *text) {
	uiLabelSetText((uiLabel *)getHandle(), text);
}

const char *UiLabel::getText() {
	return uiLabelText((uiLabel *)getHandle());
}

NBIND_CLASS(UiLabel) {
	construct<const char *>();
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
	getset(getText, setText);
	method(getText);
	method(setText);
}
