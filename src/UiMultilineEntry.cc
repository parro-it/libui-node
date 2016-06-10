#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiMultilineEntry::UiMultilineEntry() : UiControl( (uiControl*) uiNewMultilineEntry() ) {}

INHERITS_CONTROL_METHODS(UiMultilineEntry)

void UiMultilineEntry::setText(const char * text) {
	uiMultilineEntrySetText((uiMultilineEntry *) getHandle(), text);
}

const char * UiMultilineEntry::getText() {
	return uiMultilineEntryText((uiMultilineEntry *) getHandle());
}

void UiMultilineEntry::setReadOnly(int readOnly) {
	uiMultilineEntrySetReadOnly((uiMultilineEntry *) getHandle(), readOnly);
}

int UiMultilineEntry::getReadOnly() {
	return uiMultilineEntryReadOnly((uiMultilineEntry *) getHandle());
}


void UiMultilineEntry::append(const char *text) {
	uiMultilineEntryAppend(
		(uiMultilineEntry *) getHandle(),
		text
	);
}

NBIND_CLASS(UiMultilineEntry) {
	construct<>();
	DECLARE_CONTROL_METHODS()
	getset(getText, setText);
	getset(getReadOnly, setReadOnly);
	method(append);

}

