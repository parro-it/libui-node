#include "nbind/api.h"
#include "control.h"
#include "ui.h"

class UiProgressBar : public UiControl {
  private:
	int value = 0;

  public:
	UiProgressBar();
	int getValue();
	void setValue(int value);
};

UiProgressBar::UiProgressBar() : UiControl((uiControl *)uiNewProgressBar()) {}

void UiProgressBar::setValue(int val) {
	value = val;
	uiProgressBarSetValue((uiProgressBar *)getHandle(), value);
}

int UiProgressBar::getValue() {
	return value;
}

NBIND_CLASS(UiProgressBar) {
	inherit(UiControl);
	construct<>();
	getset(getValue, setValue);
	method(getValue);
	method(setValue);
}
