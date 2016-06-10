#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiCheckbox::UiCheckbox(const char *text) : UiControl( (uiControl*) uiNewCheckbox(text) ) {}

INHERITS_CONTROL_METHODS(UiCheckbox)

NBIND_CLASS(UiCheckbox) {
	construct<const char *>();
	DECLARE_CONTROL_METHODS()
}

