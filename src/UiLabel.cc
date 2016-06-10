#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiLabel::UiLabel(const char *text) : UiControl( (uiControl*) uiNewLabel(text) ) {}

INHERITS_CONTROL_METHODS(UiLabel)

NBIND_CLASS(UiLabel) {
	construct<const char *>();
	DECLARE_CONTROL_METHODS()
}

