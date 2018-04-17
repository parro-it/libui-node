#include <cstring>
#include "area.h"
#include "ui.h"

// needed because of UiFontButton::getFont
FontDescriptor::FontDescriptor(FontDescriptor &&other) {
	d = other.d;
	buttonCleanup = other.buttonCleanup;
	other.d = nullptr;
}

FontDescriptor::FontDescriptor(uiFontDescriptor *desc) {
	d = desc;
	buttonCleanup = 1;
}

FontDescriptor::FontDescriptor(const char *family, double size, int weight,
							   int italic, int stretch) {
	d = new uiFontDescriptor();

	d->Family = new char[std::strlen(family) + 1];
	std::strcpy(d->Family, family);
	d->Size = size;
	d->Weight = weight;
	d->Italic = italic;
	d->Stretch = stretch;
}

FontDescriptor::~FontDescriptor() {
	if (d != nullptr) {
		if (buttonCleanup) {
			uiFreeFontButtonFont(d);
		} else {
			delete[] d->Family;
		}
		delete d;
	}
}

char *FontDescriptor::getFamily() {
	return d->Family;
}

double FontDescriptor::getSize() {
	return d->Size;
}

int FontDescriptor::getWeight() {
	return d->Weight;
}

int FontDescriptor::getItalic() {
	return d->Italic;
}

int FontDescriptor::getStretch() {
	return d->Stretch;
}

uiFontDescriptor *FontDescriptor::getHandle() {
	return d;
}

NBIND_CLASS(FontDescriptor) {
	construct<const char *, double, int, int, int>();
	method(getFamily);
	method(getSize);
	method(getWeight);
	method(getItalic);
	method(getStretch);
}
