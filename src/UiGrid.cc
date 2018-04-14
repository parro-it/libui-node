#include "nbind/api.h"
#include "control.h"
#include "ui.h"

// TODO - document
class UiGrid : public UiControl {
  public:
	UiGrid();
	bool getPadded();
	void setPadded(bool value);
	void append(std::shared_ptr<UiControl> c, int left, int top, int xspan,
				int yspan, int hexpand, int halign, int vexpand, int valign);
	void insertAt(std::shared_ptr<UiControl> c, UiControl *existing, int at,
				  int xspan, int yspan, int hexpand, int halign, int vexpand,
				  int valign);

	~UiGrid();
	void onDestroy(uiControl *control) override;

  private:
	// this hold references to children controls
	// to avoid them being garbage collected
	// until not destroyed.
	std::vector<std::shared_ptr<UiControl>> children;
};

UiGrid::~UiGrid() {
	//	printf("UiGrid %p destroyed with wrapper %p.\n", getHandle(), this);
}

void UiGrid::onDestroy(uiControl *control) {
	/*
		freeing children to allow JS to garbage collect their wrapper classes
		when there are no references to them left in JS code.
	*/
	children.clear();
}
UiGrid::UiGrid() : UiControl((uiControl *)uiNewGrid()) {}

bool UiGrid::getPadded() {
	return uiGridPadded((uiGrid *)getHandle());
}

void UiGrid::setPadded(bool value) {
	uiGridSetPadded((uiGrid *)getHandle(), value);
}

void UiGrid::append(std::shared_ptr<UiControl> c, int left, int top, int xspan,
					int yspan, int hexpand, int halign, int vexpand,
					int valign) {
	children.push_back(c);
	uiGridAppend((uiGrid *)getHandle(), c.get()->getHandle(), left, top, xspan,
				 yspan, hexpand, halign, vexpand, valign);
}

void UiGrid::insertAt(std::shared_ptr<UiControl> c, UiControl *existing, int at,
					  int xspan, int yspan, int hexpand, int halign,
					  int vexpand, int valign) {
	children.push_back(c);
	uiGridInsertAt((uiGrid *)getHandle(), c.get()->getHandle(),
				   existing->getHandle(), at, xspan, yspan, hexpand, halign,
				   vexpand, valign);
}

NBIND_CLASS(UiGrid) {
	inherit(UiControl);
	construct<>();
	method(append);
	method(insertAt);
	method(getPadded);
	method(setPadded);
	getset(getPadded, setPadded);
}
