#include "../ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"

UiGrid::UiGrid() : UiControl( (uiControl*) uiNewGrid() ) {}

bool UiGrid::getPadded() {
	return uiGridPadded((uiGrid *) getHandle());
}

void UiGrid::setPadded(bool value) {
	uiGridSetPadded((uiGrid *) getHandle(), value);
}

void UiGrid::append(UiControl *c, int left, int top, int xspan, int yspan, int hexpand, int halign, int vexpand, int valign) {
	uiGridAppend(
		(uiGrid *) getHandle(),
		c->getHandle(),
		left,
		top,
		xspan,
		yspan,
		hexpand,
		halign,
		vexpand,
		valign
	);
}

void UiGrid::insertAt(UiControl *c, UiControl *existing, int at, int xspan, int yspan, int hexpand, int halign, int vexpand, int valign) {
	uiGridInsertAt(
		(uiGrid *) getHandle(),
		c->getHandle(),
		existing->getHandle(),
		at,
		xspan,
		yspan,
		hexpand,
		halign,
		vexpand,
		valign
	);
}




INHERITS_CONTROL_METHODS(UiGrid)

NBIND_CLASS(UiGrid) {
	construct<>();
	method(append);
	method(insertAt);
	method(getPadded);
	method(setPadded);
	getset(getPadded, setPadded);
	DECLARE_CONTROL_METHODS()
}
