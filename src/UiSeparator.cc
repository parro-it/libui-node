#include "../ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiSeparator::UiSeparator() : UiControl( (uiControl*) uiNewHorizontalSeparator() ) {}

INHERITS_CONTROL_METHODS(UiSeparator)

NBIND_CLASS(UiSeparator) {
	construct<>();
	DECLARE_CONTROL_METHODS()
}

