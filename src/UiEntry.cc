#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiEntry::UiEntry() : UiControl( (uiControl*) uiNewEntry() ) {}

void UiEntry::destroy() { UiControl::destroy(); }
void UiEntry::setParent(UiControl *parent) { UiControl::setParent(parent); }
int UiEntry::toplevel() { return UiControl::toplevel(); }
int UiEntry::getVisible() { return UiControl::getVisible(); }
void UiEntry::setVisible(int visible) { UiControl::setVisible(visible); }
int UiEntry::getEnabled() { return UiControl::getEnabled(); }
void UiEntry::setEnabled(int enabled) { UiControl::setEnabled(enabled); }

NBIND_CLASS(UiEntry) {
	construct<>();
	method(destroy);
	method(setParent);
	method(toplevel);
	getset(getVisible, setVisible);
	getset(getEnabled, setEnabled);
}

