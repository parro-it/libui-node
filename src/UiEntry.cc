#include <string>
#include "nbind/api.h"
#include "control.h"
#include "ui.h"

class UiEntryBase : public UiControl {
	DEFINE_EVENT(onChanged)
	const char *n;

  public:
	UiEntryBase(uiControl *, const char *name);
	void setText(std::string text);
	std::string getText();
	void setReadOnly(bool readOnly);
	bool getReadOnly();
	~UiEntryBase();
	void onDestroy(uiControl *control) override;
};

UiEntryBase::~UiEntryBase() {
	//	printf("%s %p destroyed with wrapper %p.\n", n, getHandle(), this);
}

void UiEntryBase::onDestroy(uiControl *control) {
	/*
		freeing event callbacks to allow JS to garbage collect this class
		when there are no references to it left in JS code.
	*/
	DISPOSE_EVENT(onChanged);
}

class UiEntry : public UiEntryBase {
  public:
	UiEntry();
	void onChanged(nbind::cbFunction &cb);
};

class UiPasswordEntry : public UiEntryBase {
  public:
	UiPasswordEntry();
	void onChanged(nbind::cbFunction &cb);
};

class UiSearchEntry : public UiEntryBase {
  public:
	UiSearchEntry();
	void onChanged(nbind::cbFunction &cb);
};

UiEntryBase::UiEntryBase(uiControl *hnd, const char *name) : UiControl(hnd) {
	n = name;
}

void UiEntryBase::setText(std::string text) {
	uiEntrySetText(uiEntry(getHandle()), text.c_str());
	if (onChangedCallback != NULL) {
		(*onChangedCallback)();
	}
}

std::string UiEntryBase::getText() {
	char *char_ptr = uiEntryText(uiEntry(getHandle()));
	std::string s(char_ptr);
	uiFreeText(char_ptr);
	return s;
}

void UiEntryBase::setReadOnly(bool readOnly) {
	uiEntrySetReadOnly(uiEntry(getHandle()), readOnly);
}

bool UiEntryBase::getReadOnly() {
	return uiEntryReadOnly(uiEntry(getHandle()));
}

IMPLEMENT_EVENT(UiEntryBase, uiEntry, onChanged, uiEntryOnChanged)

UiEntry::UiEntry() : UiEntryBase(uiControl(uiNewEntry()), "UiEntry") {}

UiPasswordEntry::UiPasswordEntry()
	: UiEntryBase(uiControl(uiNewPasswordEntry()), "UiPasswordEntry") {}

UiSearchEntry::UiSearchEntry()
	: UiEntryBase(uiControl(uiNewSearchEntry()), "UiSearchEntry") {}

NBIND_CLASS(UiEntryBase) {
	inherit(UiControl);
	getset(getText, setText);
	getset(getReadOnly, setReadOnly);
	method(onChanged);
	method(getText);
	method(setText);
	method(getReadOnly);
	method(setReadOnly);
}

NBIND_CLASS(UiSearchEntry) {
	inherit(UiEntryBase);
	construct<>();
}

NBIND_CLASS(UiPasswordEntry) {
	inherit(UiEntryBase);
	construct<>();
}

NBIND_CLASS(UiEntry) {
	inherit(UiEntryBase);
	construct<>();
}
