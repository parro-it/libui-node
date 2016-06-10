#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"

UiBox::UiBox(uiControl *control) : UiControl( control ) {}

void UiBox::append(UiControl *control, int stretchy) {
	uiBoxAppend(
		(uiBox *) getHandle(),
		control->getHandle(),
		stretchy
	);
}

UiVerticalBox::UiVerticalBox() : UiBox( (uiControl*) uiNewVerticalBox() ) {}

void UiVerticalBox::append(UiControl *control, int stretchy) {
	UiBox::append(control, stretchy);
}

INHERITS_CONTROL_METHODS(UiVerticalBox)


UiHorizontalBox::UiHorizontalBox() : UiBox( (uiControl*) uiNewHorizontalBox() ) {}

void UiHorizontalBox::append(UiControl *control, int stretchy) {
	UiBox::append(control, stretchy);
}

INHERITS_CONTROL_METHODS(UiHorizontalBox)


NBIND_CLASS(UiVerticalBox) {
	construct<>();
	DECLARE_CONTROL_METHODS()
	method(append);
}


NBIND_CLASS(UiHorizontalBox) {
	construct<>();
	DECLARE_CONTROL_METHODS()
	method(append);
}





