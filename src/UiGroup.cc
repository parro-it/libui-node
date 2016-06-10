#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiGroup::UiGroup(const char *text) : UiControl( (uiControl*) uiNewGroup(text) ) {}


void UiGroup::setChild(UiControl *control) {
	uiGroupSetChild((uiGroup *) getHandle(), control->getHandle());
}

INHERITS_CONTROL_METHODS(UiGroup)

NBIND_CLASS(UiGroup) {
	construct<const char *>();
	method(setChild);
	DECLARE_CONTROL_METHODS()
}

