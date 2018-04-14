#include "nbind/api.h"
#include "control.h"
#include "ui.h"

class UiHorizontalSeparator : public UiControl {
  public:
	UiHorizontalSeparator();
};

class UiVerticalSeparator : public UiControl {
  public:
	UiVerticalSeparator();
};
UiHorizontalSeparator::UiHorizontalSeparator()
	: UiControl((uiControl *)uiNewHorizontalSeparator()) {}

NBIND_CLASS(UiHorizontalSeparator) {
	inherit(UiControl);
	construct<>();
}

UiVerticalSeparator::UiVerticalSeparator()
	: UiControl((uiControl *)uiNewVerticalSeparator()) {}

NBIND_CLASS(UiVerticalSeparator) {
	inherit(UiControl);
	construct<>();
}
