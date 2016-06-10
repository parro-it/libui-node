#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiButton::UiButton(const char *text) : UiControl( (uiControl*) uiNewButton(text) ) {}

INHERITS_CONTROL_METHODS(UiButton)

NBIND_CLASS(UiButton) {
	construct<const char *>();
	DECLARE_CONTROL_METHODS()
}

