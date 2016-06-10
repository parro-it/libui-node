#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiProgressBar::UiProgressBar() : UiControl( (uiControl*) uiNewProgressBar() ) {}

INHERITS_CONTROL_METHODS(UiProgressBar)

NBIND_CLASS(UiProgressBar) {
	construct<>();
	DECLARE_CONTROL_METHODS()
}

