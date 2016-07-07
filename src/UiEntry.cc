#include "../ui.h"
#include "nbind/api.h"
#include "ui-node.h"

UiEntryBase::UiEntryBase(uiControl* hnd) : UiControl( hnd ) {}

void UiEntryBase::setText(const char * text) {
	uiEntrySetText((uiEntry *) getHandle(), text);
	if (onChangedCallback != NULL) {
		(*onChangedCallback)();
	}
}

const char * UiEntryBase::getText() {
	return uiEntryText((uiEntry *) getHandle());
}

void UiEntryBase::setReadOnly(bool readOnly) {
	uiEntrySetReadOnly((uiEntry *) getHandle(), readOnly);
}

bool UiEntryBase::getReadOnly() {
	return uiEntryReadOnly((uiEntry *) getHandle());
}

IMPLEMENT_EVENT(UiEntryBase, uiEntry, onChanged, uiEntryOnChanged)


UiEntry::UiEntry() : UiEntryBase( (uiControl*) uiNewEntry() ) {}

INHERITS_CONTROL_METHODS(UiEntry)
INHERITS_ENTRY_METHODS(UiEntry)

UiPasswordEntry::UiPasswordEntry() : UiEntryBase( (uiControl*) uiNewPasswordEntry() ) {}

INHERITS_CONTROL_METHODS(UiPasswordEntry)
INHERITS_ENTRY_METHODS(UiPasswordEntry)



UiSearchEntry::UiSearchEntry() : UiEntryBase( (uiControl*) uiNewSearchEntry() ) {}

INHERITS_CONTROL_METHODS(UiSearchEntry)
INHERITS_ENTRY_METHODS(UiSearchEntry)

#include "nbind/nbind.h"


NBIND_CLASS(UiSearchEntry) {
	construct<>();
	DECLARE_CONTROL_METHODS()
	DECLARE_ENTRY_METHODS()
}

NBIND_CLASS(UiPasswordEntry) {
	construct<>();
	DECLARE_CONTROL_METHODS()
	DECLARE_ENTRY_METHODS()
}

NBIND_CLASS(UiEntry) {
	construct<>();
	DECLARE_CONTROL_METHODS()
	DECLARE_ENTRY_METHODS()
}
