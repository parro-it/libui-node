#include "../ui.h"
#include "ui-node.h"
#include "nbind/api.h"

// TODO - document
class UiGrid : public UiControl {
  public:
	UiGrid();
	bool getPadded();
	void setPadded(bool value);
	void append(UiControl *c, int left, int top, int xspan, int yspan,
				int hexpand, int halign, int vexpand, int valign);
	void insertAt(UiControl *c, UiControl *existing, int at, int xspan,
				  int yspan, int hexpand, int halign, int vexpand, int valign);

	DEFINE_CONTROL_METHODS()
};

UiGrid::UiGrid() : UiControl((uiControl *)uiNewGrid()) {}

bool UiGrid::getPadded() {
	return uiGridPadded((uiGrid *)getHandle());
}

void UiGrid::setPadded(bool value) {
	uiGridSetPadded((uiGrid *)getHandle(), value);
}

void UiGrid::append(UiControl *c, int left, int top, int xspan, int yspan,
					int hexpand, int halign, int vexpand, int valign) {
	uiGridAppend((uiGrid *)getHandle(), c->getHandle(), left, top, xspan, yspan,
				 hexpand, halign, vexpand, valign);
}

void UiGrid::insertAt(UiControl *c, UiControl *existing, int at, int xspan,
					  int yspan, int hexpand, int halign, int vexpand,
					  int valign) {
	uiGridInsertAt((uiGrid *)getHandle(), c->getHandle(), existing->getHandle(),
				   at, xspan, yspan, hexpand, halign, vexpand, valign);
}

INHERITS_CONTROL_METHODS(UiGrid)

NBIND_CLASS(UiGrid) {
	construct<>();
	method(append);
	method(insertAt);
	method(getPadded);
	method(setPadded);
	getset(getPadded, setPadded);
	DECLARE_CHILD_CONTROL_METHODS()
}
