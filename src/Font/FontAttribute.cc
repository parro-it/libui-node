#include <vector>
#include "area.h"
#include "ui.h"

// because we're returning the objects in FontAttribute::new...
FontAttribute::FontAttribute(FontAttribute &&other) {
	a = other.a;
	appended = other.appended;
	other.a = nullptr;
}

FontAttribute::FontAttribute(uiAttribute *attr) {
	a = attr;
}

FontAttribute::~FontAttribute() {
	if (a != nullptr) {
		if (!appended) {
			uiFreeAttribute(a);
		}
	}
}

int FontAttribute::getAttributeType() {
	return uiAttributeGetType(a);
}

uiAttribute *FontAttribute::getHandle() {
	return a;
}

void FontAttribute::setAppended() {
	appended = 1;
}

const char *FontAttribute::getFamilyInternal() {
	return uiAttributeFamily(a);
}

double FontAttribute::getSizeInternal() {
	return uiAttributeSize(a);
}

int FontAttribute::getWeightInternal() {
	return uiAttributeWeight(a);
}

int FontAttribute::getItalicInternal() {
	return uiAttributeItalic(a);
}

int FontAttribute::getStretchInternal() {
	return uiAttributeStretch(a);
}

Color FontAttribute::getColorInternal() {
	double r;
	double g;
	double b;
	double alpha;

	uiAttributeColor(a, &r, &g, &b, &alpha);

	return Color(r, g, b, alpha);
}

int FontAttribute::getUnderlineInternal() {
	return uiAttributeUnderline(a);
}

std::vector<Color> FontAttribute::getUnderlineColorInternal() {
	double r;
	double g;
	double b;
	double alpha;

	uiUnderlineColor type;
	uiAttributeUnderlineColor(a, &type, &r, &g, &b, &alpha);

	return std::vector<Color>{Color(r, g, b, alpha), Color(type, 0, 0, 0)};
}

OpenTypeFeatures FontAttribute::getOTFeaturesInternal() {
	return OpenTypeFeatures((uiOpenTypeFeatures *)uiAttributeFeatures(a));
}

FontAttribute FontAttribute::newFamily(const char *family) {
	return FontAttribute(uiNewFamilyAttribute(family));
}

FontAttribute FontAttribute::newSize(double size) {
	return FontAttribute(uiNewSizeAttribute(size));
}

FontAttribute FontAttribute::newWeight(int weightAttribute) {
	return FontAttribute(uiNewWeightAttribute(weightAttribute));
}

FontAttribute FontAttribute::newItalic(int italicAttribute) {
	return FontAttribute(uiNewItalicAttribute(italicAttribute));
}

FontAttribute FontAttribute::newStretch(int stretchAttribute) {
	return FontAttribute(uiNewStretchAttribute(stretchAttribute));
}

FontAttribute FontAttribute::newColor(Color c) {
	return FontAttribute(
		uiNewColorAttribute(c.getR(), c.getG(), c.getB(), c.getA()));
}

FontAttribute FontAttribute::newBackgroundColor(Color c) {
	return FontAttribute(
		uiNewBackgroundAttribute(c.getR(), c.getG(), c.getB(), c.getA()));
}

FontAttribute FontAttribute::newUnderline(int underlineAttr) {
	return FontAttribute(uiNewUnderlineAttribute(underlineAttr));
}

FontAttribute FontAttribute::newUnderlineColor2(int underlineColorAttr,
												Color c) {
	return FontAttribute(uiNewUnderlineColorAttribute(
		underlineColorAttr, c.getR(), c.getG(), c.getB(), c.getA()));
}

FontAttribute FontAttribute::newOTFeatures(OpenTypeFeatures *otf) {
	return FontAttribute(uiNewFeaturesAttribute(otf->getHandle()));
}

NBIND_CLASS(FontAttribute) {
	method(getAttributeType);

	method(getFamilyInternal);
	method(getSizeInternal);
	method(getWeightInternal);
	method(getItalicInternal);
	method(getStretchInternal);
	method(getColorInternal);
	method(getUnderlineInternal);
	method(getUnderlineColorInternal);

	method(newFamily);
	method(newSize);
	method(newWeight);
	method(newItalic);
	method(newStretch);
	method(newColor);
	method(newBackgroundColor);
	method(newUnderline);
	method(newUnderlineColor2);
	method(newOTFeatures);
}
