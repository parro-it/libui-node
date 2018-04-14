#include <memory>
#include <vector>
#include "nbind/api.h"
#include "box.h"
#include "control.h"
#include "ui.h"

class UiBox : public UiControl {
  public:
	UiBox(uiControl *hnd);
	~UiBox();
	void onDestroy(uiControl *control) override;

	// this hold references to children controls
	// to avoid them being garbage collected
	// until not destroyed.
	std::vector<std::shared_ptr<UiControl>> children;

	DEFINE_BOX_METHODS()
};

class UiVerticalBox : public UiBox {
  public:
	UiVerticalBox();
	DEFINE_BOX_METHODS()
};

class UiHorizontalBox : public UiBox {
  public:
	UiHorizontalBox();
	DEFINE_BOX_METHODS()
};

UiBox::~UiBox() {
	// printf("UiBox %p destroyed with wrapper %p.\n", getHandle(), this);
}

void UiBox::onDestroy(uiControl *control) {
	/*
		freeing children to allow JS to garbage collect their wrapper classes
		when there are no references to them left in JS code.
	*/
	children.clear();
}
UiBox::UiBox(uiControl *control) : UiControl(control) {}

void UiBox::append(std::shared_ptr<UiControl> control, bool stretchy) {
	children.push_back(control);
	uiBoxAppend((uiBox *)getHandle(), control->getHandle(), stretchy);
}

void UiBox::deleteAt(int index) {
	children.erase(children.begin() + index);
	uiBoxDelete((uiBox *)getHandle(), index);
}

void UiBox::setPadded(bool padded) {
	uiBoxSetPadded((uiBox *)getHandle(), padded);
}

bool UiBox::getPadded() {
	return uiBoxPadded((uiBox *)getHandle());
}

UiVerticalBox::UiVerticalBox() : UiBox((uiControl *)uiNewVerticalBox()) {}

INHERITS_BOX_METHODS(UiVerticalBox)

UiHorizontalBox::UiHorizontalBox() : UiBox((uiControl *)uiNewHorizontalBox()) {}

INHERITS_BOX_METHODS(UiHorizontalBox)

NBIND_CLASS(UiVerticalBox) {
	inherit(UiControl);
	construct<>();
	DECLARE_BOX_METHODS()
}

NBIND_CLASS(UiHorizontalBox) {
	inherit(UiControl);
	construct<>();
	DECLARE_BOX_METHODS()
}
