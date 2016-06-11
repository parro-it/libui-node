#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiButton::UiButton(const char *text) : UiControl( (uiControl*) uiNewButton(text) ) {}

INHERITS_CONTROL_METHODS(UiButton)



void UiButton::setText(const char * text) {
	uiButtonSetText((uiButton *) getHandle(), text);
}

const char * UiButton::getText() {
	return uiButtonText((uiButton *) getHandle());
}


static void UiButton_onClicked(uiButton *w, void *data)
{
	nbind::cbFunction *cb = (nbind::cbFunction *) data;
	(*cb)();
}


void UiButton::onClicked(nbind::cbFunction & cb) {
	onClickedCallback = new nbind::cbFunction(cb);
	uiButtonOnClicked(
		(uiButton *) getHandle(),
		UiButton_onClicked,
		onClickedCallback
	);
}



NBIND_CLASS(UiButton) {
	construct<const char *>();
	DECLARE_CONTROL_METHODS()
	getset(getText, setText);
	method(onClicked);
}

