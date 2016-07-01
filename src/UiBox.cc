#include "../ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"

UiBox::UiBox(uiControl *control) : UiControl( control ) {}

void UiBox::append(UiControl *control, bool stretchy) {
	uiBoxAppend(
		(uiBox *) getHandle(),
		control->getHandle(),
		stretchy
	);
}

void UiBox::deleteAt(int index) {
	uiBoxDelete(
		(uiBox *) getHandle(),
		index
	);
}

void UiBox::setPadded(bool padded) {
	uiBoxSetPadded((uiBox *) getHandle(), padded);
}

bool UiBox::getPadded() {
	return uiBoxPadded((uiBox *) getHandle());
}


UiVerticalBox::UiVerticalBox() : UiBox( (uiControl*) uiNewVerticalBox() ) {}

INHERITS_CONTROL_METHODS(UiVerticalBox)
INHERITS_BOX_METHODS(UiVerticalBox)


UiHorizontalBox::UiHorizontalBox() : UiBox( (uiControl*) uiNewHorizontalBox() ) {}

INHERITS_CONTROL_METHODS(UiHorizontalBox)
INHERITS_BOX_METHODS(UiHorizontalBox)


NBIND_CLASS(UiVerticalBox) {
	construct<>();
	DECLARE_CONTROL_METHODS()
	DECLARE_BOX_METHODS()
}

NBIND_CLASS(UiHorizontalBox) {
	construct<>();
	DECLARE_CONTROL_METHODS()
	DECLARE_BOX_METHODS()
}





