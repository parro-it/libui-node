#include "nbind/api.h"
#include "control.h"
#include "ui.h"

class UiDateTimePicker : public UiControl {
  public:
	UiDateTimePicker();
};

UiDateTimePicker::UiDateTimePicker()
	: UiControl((uiControl *)uiNewDateTimePicker()) {}

NBIND_CLASS(UiDateTimePicker) {
	inherit(UiControl);
	construct<>();
}

class UiTimePicker : public UiControl {
  public:
	UiTimePicker();
};

UiTimePicker::UiTimePicker() : UiControl((uiControl *)uiNewTimePicker()) {}

NBIND_CLASS(UiTimePicker) {
	inherit(UiControl);
	construct<>();
}

class UiDatePicker : public UiControl {
  public:
	UiDatePicker();
};

UiDatePicker::UiDatePicker() : UiControl((uiControl *)uiNewDatePicker()) {}

NBIND_CLASS(UiDatePicker) {
	inherit(UiControl);
	construct<>();
}
