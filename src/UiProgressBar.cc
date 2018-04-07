#include "../ui.h"
#include "nbind/api.h"
#include "includes/control.h"

class UiProgressBar : public UiControl {
  private:
	int value = 0;

  public:
	UiProgressBar();
	DEFINE_CONTROL_METHODS()
	int getValue();
	void setValue(int value);
};

UiProgressBar::UiProgressBar() : UiControl((uiControl *)uiNewProgressBar()) {}

INHERITS_CONTROL_METHODS(UiProgressBar)

void UiProgressBar::setValue(int val) {
	value = val;
	uiProgressBarSetValue((uiProgressBar *)getHandle(), value);
}

int UiProgressBar::getValue() {
	return value;
}

NBIND_CLASS(UiProgressBar) {
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
	getset(getValue, setValue);
	method(getValue);
	method(setValue);
}
