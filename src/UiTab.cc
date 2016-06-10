#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiTab::UiTab() : UiControl( (uiControl*) uiNewTab() ) {}

INHERITS_CONTROL_METHODS(UiTab)

void UiTab::append(const char *text, UiControl *child) {
	uiTabAppend(
		(uiTab *) getHandle(),
		text,
		child->getHandle()
	);
}


NBIND_CLASS(UiTab) {
	construct<>();
	DECLARE_CONTROL_METHODS()
	method(append);
}


