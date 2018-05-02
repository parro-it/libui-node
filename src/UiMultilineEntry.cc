#include <string>
#include "nbind/api.h"
#include "control.h"
#include "ui.h"

class UiMultilineEntry : public UiControl {
	DEFINE_EVENT(onChanged)

  public:
	UiMultilineEntry();
	void setText(std::string text);
	std::string getText();
	void setReadOnly(bool readOnly);
	bool getReadOnly();
	void append(std::string text);
	~UiMultilineEntry();
	void onDestroy(uiControl *control) override;
};

UiMultilineEntry::~UiMultilineEntry() {
	// printf("UiMultilineEntry %p destroyed with wrapper %p.\n", getHandle(),
	// 	   this);
}

void UiMultilineEntry::onDestroy(uiControl *control) {
	/*
		freeing event callbacks to allow JS to garbage collect this class
		when there are no references to it left in JS code.
	*/
	DISPOSE_EVENT(onChanged);
}
UiMultilineEntry::UiMultilineEntry()
	: UiControl(uiControl(uiNewNonWrappingMultilineEntry())) {}

IMPLEMENT_EVENT(UiMultilineEntry, uiMultilineEntry, onChanged,
				uiMultilineEntryOnChanged)

void UiMultilineEntry::setText(std::string text) {
	uiMultilineEntrySetText(uiMultilineEntry(getHandle()), text.c_str());
	if (onChangedCallback != NULL) {
		(*onChangedCallback)();
	}
}

std::string UiMultilineEntry::getText() {
	char *char_ptr = uiMultilineEntryText(uiMultilineEntry(getHandle()));
	std::string s(char_ptr);
	uiFreeText(char_ptr);
	return s;
}

void UiMultilineEntry::setReadOnly(bool readOnly) {
	uiMultilineEntrySetReadOnly(uiMultilineEntry(getHandle()), readOnly);
}

bool UiMultilineEntry::getReadOnly() {
	return uiMultilineEntryReadOnly(uiMultilineEntry(getHandle()));
}

void UiMultilineEntry::append(std::string text) {
	uiMultilineEntryAppend(uiMultilineEntry(getHandle()), text.c_str());
}

NBIND_CLASS(UiMultilineEntry) {
	inherit(UiControl);
	construct<>();
	getset(getText, setText);
	getset(getReadOnly, setReadOnly);
	method(getText);
	method(setText);
	method(getReadOnly);
	method(setReadOnly);
	method(append);
	method(onChanged);
}
