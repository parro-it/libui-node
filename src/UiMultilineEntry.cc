#include "../ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiMultilineEntry::UiMultilineEntry() : UiControl( (uiControl*) uiNewNonWrappingMultilineEntry() ) {}

INHERITS_CONTROL_METHODS(UiMultilineEntry)

IMPLEMENT_EVENT(UiMultilineEntry, uiMultilineEntry, onChanged, uiMultilineEntryOnChanged)


void UiMultilineEntry::setText(const char * text) {
	uiMultilineEntrySetText((uiMultilineEntry *) getHandle(), text);
	if (onChangedCallback != NULL) {
		(*onChangedCallback)();
	}
}

const char * UiMultilineEntry::getText() {
	return uiMultilineEntryText((uiMultilineEntry *) getHandle());
}

void UiMultilineEntry::setReadOnly(bool readOnly) {
	uiMultilineEntrySetReadOnly((uiMultilineEntry *) getHandle(), readOnly);
}

bool UiMultilineEntry::getReadOnly() {
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
	method(getText);
	method(setText);
	method(getReadOnly);
	method(setReadOnly);
	method(append);
	method(onChanged);

}

