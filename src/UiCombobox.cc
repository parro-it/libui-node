#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiCombobox::UiCombobox() : UiControl( (uiControl*) uiNewCombobox() ) {}

INHERITS_CONTROL_METHODS(UiCombobox)

NBIND_CLASS(UiCombobox) {
	construct<>();
	DECLARE_CONTROL_METHODS()
}

