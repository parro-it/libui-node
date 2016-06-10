#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiEditableCombobox::UiEditableCombobox() : UiControl( (uiControl*) uiNewEditableCombobox() ) {}

INHERITS_CONTROL_METHODS(UiEditableCombobox)

NBIND_CLASS(UiEditableCombobox) {
	construct<>();
	DECLARE_CONTROL_METHODS()
}

