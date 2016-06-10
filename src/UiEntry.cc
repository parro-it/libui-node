#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"

UiEntryBase::UiEntryBase(uiControl* hnd) : UiControl( hnd ) {}

void UiEntryBase::setText(const char * text) {
	uiEntrySetText((uiEntry *) getHandle(), text);
}

const char * UiEntryBase::getText() {
	return uiEntryText((uiEntry *) getHandle());
}

void UiEntryBase::setReadOnly(int readOnly) {
	uiEntrySetReadOnly((uiEntry *) getHandle(), readOnly);
}

int UiEntryBase::getReadOnly() {
	return uiEntryReadOnly((uiEntry *) getHandle());
}



UiEntry::UiEntry() : UiEntryBase( (uiControl*) uiNewEntry() ) {}

INHERITS_CONTROL_METHODS(UiEntry)
INHERITS_ENTRY_METHODS(UiEntry)

void UiEntry::onChange(nbind::cbFunction & cb) {
	uiEntryOnChanged(
		(uiEntry *) getHandle(),
		UiEntry_onChange,
		&cb
	);
}

NBIND_CLASS(UiEntry) {
	construct<>();
	DECLARE_CONTROL_METHODS()
	DECLARE_ENTRY_METHODS()
}


UiPasswordEntry::UiPasswordEntry() : UiEntryBase( (uiControl*) uiNewPasswordEntry() ) {}

INHERITS_CONTROL_METHODS(UiPasswordEntry)
INHERITS_ENTRY_METHODS(UiPasswordEntry)

NBIND_CLASS(UiPasswordEntry) {
	construct<>();
	DECLARE_CONTROL_METHODS()
	DECLARE_ENTRY_METHODS()
}


UiSearchEntry::UiSearchEntry() : UiEntryBase( (uiControl*) uiNewSearchEntry() ) {}

INHERITS_CONTROL_METHODS(UiSearchEntry)
INHERITS_ENTRY_METHODS(UiSearchEntry)

NBIND_CLASS(UiSearchEntry) {
	construct<>();
	DECLARE_CONTROL_METHODS()
	DECLARE_ENTRY_METHODS()
}
