#include <memory>
#include "nbind/api.h"
#include "control.h"
#include "ui.h"

class UiSpinbox : public UiControl {

  public:
	std::unique_ptr<nbind::cbFunction> onChangedCallback;
	void onChanged(nbind::cbFunction cb);
	UiSpinbox(int min, int max);
	UiSpinbox();
	~UiSpinbox();
	DEFINE_CONTROL_METHODS()

	int getValue();
	void setValue(int value);
	void onDestroy(uiControl *control) override;
};

UiSpinbox::~UiSpinbox() {
	printf("UiSpinbox %p destroyed with wrapper %p.\n", getHandle(), this);
}

void UiSpinbox::onDestroy(uiControl *control) {
	/*
		freeing event callbacks to allow JS to garbage collect this class
		when there are no references to it left in JS code.
	*/

	printf("onDestroy called\n");
	nbind::cbFunction *cb = onChangedCallback.release();
	delete cb;
}

UiSpinbox::UiSpinbox(int min, int max)
	: UiControl((uiControl *)uiNewSpinbox(min, max)) {}

UiSpinbox::UiSpinbox() : UiControl((uiControl *)uiNewSpinbox(0, 100)) {}

int UiSpinbox::getValue() {
	return uiSpinboxValue((uiSpinbox *)getHandle());
}

void UiSpinbox::setValue(int value) {
	uiSpinboxSetValue((uiSpinbox *)getHandle(), value);
	if (onChangedCallback != nullptr) {
		(*onChangedCallback)();
	}
}

namespace std {
template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args &&... args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
} // namespace std

static void UiSpinbox_onChanged(uiSpinbox *w, void *data) {
	UiSpinbox *ctrl = (UiSpinbox *)data;
	nbind::cbFunction cb = *(ctrl->onChangedCallback);
	cb();
}

void UiSpinbox::onChanged(nbind::cbFunction cb) {
	// nbind::cbFunction *cba = new nbind::cbFunction(cb);
	onChangedCallback = std::make_unique<nbind::cbFunction>(cb);
	uiSpinboxOnChanged((uiSpinbox *)getHandle(), UiSpinbox_onChanged, this);
}

INHERITS_CONTROL_METHODS(UiSpinbox)

NBIND_CLASS(UiSpinbox) {
	construct<int, int>();
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
	getset(getValue, setValue);
	method(getValue);
	method(setValue);
	method(onChanged);
}
