#include "../ui.h"
#include "nbind/api.h"
#include "includes/control.h"

class UiHorizontalSeparator : public UiControl {
  public:
	UiHorizontalSeparator();
	DEFINE_CONTROL_METHODS()
};

class UiVerticalSeparator : public UiControl {
  public:
	UiVerticalSeparator();
	DEFINE_CONTROL_METHODS()
};
UiHorizontalSeparator::UiHorizontalSeparator()
	: UiControl((uiControl *)uiNewHorizontalSeparator()) {}

INHERITS_CONTROL_METHODS(UiHorizontalSeparator)

NBIND_CLASS(UiHorizontalSeparator) {
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
}

UiVerticalSeparator::UiVerticalSeparator()
	: UiControl((uiControl *)uiNewVerticalSeparator()) {}

INHERITS_CONTROL_METHODS(UiVerticalSeparator)

NBIND_CLASS(UiVerticalSeparator) {
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
}
