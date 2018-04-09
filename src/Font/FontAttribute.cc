#include "../../ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"

FontAttribute::FontAttribute(uiAttribute *attr){
	a = attr;
}

int FontAttribute::getAttributeType() {
	return uiAttributeGetType(a);
}

uiAttribute *FontAttribute::getHandle() {
	return a;
}

void FontAttribute::free(){
	if(!appended){
		uiFreeAttribute(a);
	}
}

void FontAttribute::setAppended(){
	appended = 1;
}

const char *FontAttribute::getFamily() {
	return uiAttributeFamily(a);
}

double FontAttribute::getSize() {
	return uiAttributeSize(a);
}

int FontAttribute::getWeight() {
	return uiAttributeWeight(a);
}

int FontAttribute::getItalic() {
	return uiAttributeItalic(a);
}

int FontAttribute::getStretch() {
	return uiAttributeStretch(a);
}

Color FontAttribute::getColor() {
	double r;
	double g;
	double b;
	double alpha;

	uiAttributeColor(a, &r, &g, &b, &alpha);

	return Color(r, g, b, alpha);
}

int FontAttribute::getUnderline() {
	return uiAttributeUnderline(a);
}

int FontAttribute::getUnderlineColor(Color *c) {
	double r;
	double g;
	double b;
	double alpha;

	uiUnderlineColor type;
	uiAttributeUnderlineColor(a, &type, &r, &g, &b, &alpha);
	c->setR(r);
	c->setG(g);
	c->setB(b);
	c->setA(alpha);

	return type;
}

OpenTypeFeatures *FontAttribute::getOTFeatures() {
	return new OpenTypeFeatures((uiOpenTypeFeatures*) uiAttributeFeatures(a));
}



FontAttribute *FontAttribute::newFamily(const char *family) {
	return new FontAttribute(uiNewFamilyAttribute(family));
}

FontAttribute *FontAttribute::newSize(double size) {
	return new FontAttribute(uiNewSizeAttribute(size));
}

FontAttribute *FontAttribute::newWeight(int weightAttribute) {
	return new FontAttribute(uiNewWeightAttribute(weightAttribute));
}

FontAttribute *FontAttribute::newItalic(int italicAttribute) {
	return new FontAttribute(uiNewItalicAttribute(italicAttribute));
}

FontAttribute *FontAttribute::newStretch(int stretchAttribute) {
	return new FontAttribute(uiNewStretchAttribute(stretchAttribute));
}

FontAttribute *FontAttribute::newColor(Color c) {
	return new FontAttribute(uiNewColorAttribute(c.getR(), c.getG(), c.getB(), c.getA()));
}

FontAttribute *FontAttribute::newBackground(Color c) {
	return new FontAttribute(uiNewBackgroundAttribute(c.getR(), c.getG(), c.getB(), c.getA()));
}

FontAttribute *FontAttribute::newUnderline(int underlineAttr) {
	return new FontAttribute(uiNewUnderlineAttribute(underlineAttr));
}

FontAttribute *FontAttribute::newUnderlineColor2(int underlineColorAttr, Color c) {
	return new FontAttribute(uiNewUnderlineColorAttribute(underlineColorAttr, c.getR(), c.getG(), c.getB(), c.getA()));
}

FontAttribute *FontAttribute::newOTFeatures(OpenTypeFeatures *otf) {
	return new FontAttribute(uiNewFeaturesAttribute(otf->getHandle()));
}


NBIND_CLASS(FontAttribute) {
	method(free);
	method(getAttributeType);

	method(getFamily);
	method(getSize);
	method(getWeight);
	method(getItalic);
	method(getStretch);
	method(getColor);
	method(getUnderline);
	method(getUnderlineColor);

	method(newFamily);
	method(newSize);
	method(newWeight);
	method(newItalic);
	method(newStretch);
	method(newColor);
	method(newBackground);
	method(newUnderline);
	method(newUnderlineColor2);
	method(newOTFeatures);
}
