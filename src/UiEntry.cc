#include <string>
#include "../ui.h"
#include "ui-node.h"
#include "nbind/api.h"
#include "includes/entry.h"

class UiEntryBase : public UiControl {
	DEFINE_EVENT(onChanged)

  public:
	UiEntryBase(uiControl *);
	DEFINE_CONTROL_METHODS()
	DEFINE_ENTRY_METHODS()
};

class UiEntry : public UiEntryBase {
  public:
	UiEntry();
	DEFINE_CONTROL_METHODS()
	DEFINE_ENTRY_METHODS()
	void onChanged(nbind::cbFunction &cb);
};

class UiPasswordEntry : public UiEntryBase {
  public:
	UiPasswordEntry();
	DEFINE_CONTROL_METHODS()
	DEFINE_ENTRY_METHODS()
	void onChanged(nbind::cbFunction &cb);
};

class UiSearchEntry : public UiEntryBase {
  public:
	UiSearchEntry();
	DEFINE_CONTROL_METHODS()
	DEFINE_ENTRY_METHODS()
	void onChanged(nbind::cbFunction &cb);
};

UiEntryBase::UiEntryBase(uiControl *hnd) : UiControl(hnd) {}

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

UiEntry::UiEntry() : UiEntryBase(uiControl(uiNewEntry())) {}

INHERITS_CONTROL_METHODS(UiEntry)
INHERITS_ENTRY_METHODS(UiEntry)

UiPasswordEntry::UiPasswordEntry()
	: UiEntryBase(uiControl(uiNewPasswordEntry())) {}

INHERITS_CONTROL_METHODS(UiPasswordEntry)
INHERITS_ENTRY_METHODS(UiPasswordEntry)

UiSearchEntry::UiSearchEntry() : UiEntryBase(uiControl(uiNewSearchEntry())) {}

INHERITS_CONTROL_METHODS(UiSearchEntry)
INHERITS_ENTRY_METHODS(UiSearchEntry)

NBIND_CLASS(UiSearchEntry) {
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
	DECLARE_ENTRY_METHODS()
}

NBIND_CLASS(UiPasswordEntry) {
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
	DECLARE_ENTRY_METHODS()
}

NBIND_CLASS(UiEntry) {
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
	DECLARE_ENTRY_METHODS()
}
