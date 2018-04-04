#include "../ui.h"
#include "ui-node.h"
#include "nbind/api.h"

class UiMultilineEntry : public UiControl {
	DEFINE_EVENT(onChanged)

  public:
	UiMultilineEntry();
	DEFINE_CONTROL_METHODS()
	void setText(const char *text);
	const char *getText();
	void setReadOnly(bool readOnly);
	bool getReadOnly();
	void append(const char *text);
};

UiMultilineEntry::UiMultilineEntry()
	: UiControl((uiControl *)uiNewNonWrappingMultilineEntry()) {}

INHERITS_CONTROL_METHODS(UiMultilineEntry)

IMPLEMENT_EVENT(UiMultilineEntry, uiMultilineEntry, onChanged,
				uiMultilineEntryOnChanged)

void UiMultilineEntry::setText(const char *text) {
	uiMultilineEntrySetText((uiMultilineEntry *)getHandle(), text);
	if (onChangedCallback != NULL) {
		(*onChangedCallback)();
	}
}

const char *UiMultilineEntry::getText() {
	return uiMultilineEntryText((uiMultilineEntry *)getHandle());
}

void UiMultilineEntry::setReadOnly(bool readOnly) {
	uiMultilineEntrySetReadOnly((uiMultilineEntry *)getHandle(), readOnly);
}

bool UiMultilineEntry::getReadOnly() {
	return uiMultilineEntryReadOnly((uiMultilineEntry *)getHandle());
}

void UiMultilineEntry::append(const char *text) {
	uiMultilineEntryAppend((uiMultilineEntry *)getHandle(), text);
}

NBIND_CLASS(UiMultilineEntry) {
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
	getset(getText, setText);
	getset(getReadOnly, setReadOnly);
	method(getText);
	method(setText);
	method(getReadOnly);
	method(setReadOnly);
	method(append);
	method(onChanged);
}
