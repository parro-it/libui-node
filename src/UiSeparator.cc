#include "../ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiHorizontalSeparator::UiHorizontalSeparator() : UiControl( (uiControl*) uiNewHorizontalSeparator() ) {}

INHERITS_CONTROL_METHODS(UiHorizontalSeparator)

NBIND_CLASS(UiHorizontalSeparator) {
	construct<>();
	DECLARE_CONTROL_METHODS()
}


UiVerticalSeparator::UiVerticalSeparator() : UiControl( (uiControl*) uiNewVerticalSeparator() ) {}

INHERITS_CONTROL_METHODS(UiVerticalSeparator)

NBIND_CLASS(UiVerticalSeparator) {
	construct<>();
	DECLARE_CONTROL_METHODS()
}
