#include "../../ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"


const char * DrawTextFontDescriptor::getFamily() {
	return d->Family;
}

double DrawTextFontDescriptor::getSize() {
	return d->Size;
}

int DrawTextFontDescriptor::getWeight() {
	return d->Weight;
}

int DrawTextFontDescriptor::getItalic() {
	return d->Italic;
}

int DrawTextFontDescriptor::getStretch() {
	return d->Stretch;
}

DrawTextFontDescriptor::DrawTextFontDescriptor(uiDrawTextFontDescriptor * descr) {
	d = descr;
}

NBIND_CLASS(DrawTextFontDescriptor) {
	method(getFamily);
	method(getSize);
	method(getWeight);
	method(getItalic);
	method(getStretch);
}
