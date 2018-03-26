#include "../../ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"

UiFontDescriptor::UiFontDescriptor(uiFontDescriptor * desc) {
	d = desc;
	buttonCleanup = 1;
}

UiFontDescriptor::UiFontDescriptor(char *family, double size, int weight, int italic, int stretch) {
    d = new uiFontDescriptor();
    d->Family = family;
    d->Size = size;
    d->Weight = weight;
    d->Italic = italic;
    d->Stretch = stretch;
}

void UiFontDescriptor::free() {
	if(buttonCleanup){
		uiFreeFontButtonFont(d);
	}
	delete d;
}

char *UiFontDescriptor::getFamily() {
	return d->Family;
}

double UiFontDescriptor::getSize() {
	return d->Size;
}

int UiFontDescriptor::getWeight() {
	return d->Weight;
}

int UiFontDescriptor::getItalic() {
	return d->Italic;
}

int UiFontDescriptor::getStretch() {
	return d->Stretch;
}

uiFontDescriptor *UiFontDescriptor::getHandle(){
	return d;
}


NBIND_CLASS(UiFontDescriptor) {
	// construct<char *, double, int, int, int>();
	method(getFamily);
	method(getSize);
	method(getWeight);
	method(getItalic);
	method(getStretch);
}
