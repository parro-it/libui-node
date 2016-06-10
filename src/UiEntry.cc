#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiEntry::UiEntry() : UiControl( (uiControl*) uiNewEntry() ) {}

INHERITS_CONTROL_METHODS(UiEntry)

NBIND_CLASS(UiEntry) {
	construct<>();
	DECLARE_CONTROL_METHODS()
}

