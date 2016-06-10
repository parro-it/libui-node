#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"

UiBox::UiBox() : UiControl( (uiControl*) uiNewVerticalBox() ) {}

void UiBox::append(UiControl *control, int stretchy) {
	uiBoxAppend(
		(uiBox *) getHandle(),
		control->getHandle(),
		stretchy
	);
}


void UiBox::destroy() { UiControl::destroy(); }
void UiBox::setParent(UiControl *parent) { UiControl::setParent(parent); }
int UiBox::toplevel() { return UiControl::toplevel(); }
int UiBox::getVisible() { return UiControl::getVisible(); }
void UiBox::setVisible(int visible) { UiControl::setVisible(visible); }
int UiBox::getEnabled() { return UiControl::getEnabled(); }
void UiBox::setEnabled(int enabled) { UiControl::setEnabled(enabled); }


NBIND_CLASS(UiBox) {
	construct<>();
	method(append);
	method(destroy);
	method(setParent);
	method(toplevel);
	getset(getVisible, setVisible);
	getset(getEnabled, setEnabled);
}





