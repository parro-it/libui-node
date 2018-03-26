#include "../../ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"

UiFontDescriptor::UiFontDescriptor(uiFontDescriptor * desc) {
	d = desc;
	cleanup = 1;
}

UiFontDescriptor::UiFontDescriptor(char *family, double size, int weight, int italic, int stretch) {
    d = new uiFontDescriptor();
    d->Family = family;
    d->Size = size;
    d->Weight = weight;
    d->Italic = italic
    d->Stretch = stretch;
}

UiFontDescriptor::~UiFontDescriptor(){
	if(cleanup){
		uiFreeFontButtonFont(d);
	}
	delete d;
}

char *UiFontDescriptor::getFamily() {
	return m->Family;
}

double UiFontDescriptor::getSize() {
	return m->Size;
}

int UiFontDescriptor::getWeight() {
	return m->Weight;
}

int UiFontDescriptor::getItalic() {
	return m->Italic;
}

int UiFontDescriptor::getStetch() {
	return m->Stretch;
}

uiFontDescriptor *UiFontDescriptor::getHandle(){
	return m;
}


NBIND_CLASS(UiFontDescriptor) {
	method(getFamily);
	method(getSize);
	method(getWeight);
	method(getItalic);
	method(getStetch);
}
