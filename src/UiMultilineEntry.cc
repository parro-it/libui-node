#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiMultilineEntry::UiMultilineEntry() : UiControl( (uiControl*) uiNewMultilineEntry() ) {}

INHERITS_CONTROL_METHODS(UiMultilineEntry)

NBIND_CLASS(UiMultilineEntry) {
	construct<>();
	DECLARE_CONTROL_METHODS()
}

