#include "../../ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"

UiFontAttribute::UiFontAttribute(uiAttribute *attr){
	a = attr;
}

int UiFontAttribute::getAttributeType() {
	return uiAttributeGetType(a);
}

uiAttribute *UiFontAttribute::getHandle(){
	return a;
}

void UiFontAttribute::free(){
	uiFreeAttribute(a);
}

// TODO needs to actually be of that type
// It is an error to call this on a uiAttribute that does not hold a ...
const char *UiFontAttribute::getFamily(){
	return uiAttributeFamily(a);
}

double UiFontAttribute::getSize() {
	return uiAttributeSize(a);
}

int UiFontAttribute::getWeight(){
	return uiAttributeWeight(a);
}

int UiFontAttribute::getItalic(){
	return uiAttributeItalic(a);
}

int UiFontAttribute::getStretch(){
	return uiAttributeStretch(a);
}

Color UiFontAttribute::getColor(){
	double r;
	double g;
	double b;
	double alpha;

	uiAttributeColor(a, &r, &g, &b, &alpha);

	return Color(r, g, b, alpha);
}

int UiFontAttribute::getUnderline(){
	return uiAttributeUnderline(a);
}

int UiFontAttribute::getUnderlineColor(Color *c){
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

UiFontAttribute *UiFontAttribute::newFamily(const char *family) {
	return new UiFontAttribute(uiNewFamilyAttribute(family));
}

UiFontAttribute *UiFontAttribute::newSize(double size) {
	return new UiFontAttribute(uiNewSizeAttribute(size));
}

UiFontAttribute *UiFontAttribute::newWeight(int weightAttribute) {
	return new UiFontAttribute(uiNewWeightAttribute(weightAttribute));
}

UiFontAttribute *UiFontAttribute::newItalic(int italicAttribute) {
	return new UiFontAttribute(uiNewItalicAttribute(italicAttribute));
}

UiFontAttribute *UiFontAttribute::newStretch(int stretchAttribute) {
	return new UiFontAttribute(uiNewStretchAttribute(stretchAttribute));
}

UiFontAttribute *UiFontAttribute::newColor(Color *c) {
	return new UiFontAttribute(uiNewColorAttribute(c->getR(), c->getG(), c->getB(), c->getA()));
}

UiFontAttribute *UiFontAttribute::newBackground(Color *c) {
	return new UiFontAttribute(uiNewBackgroundAttribute(c->getR(), c->getG(), c->getB(), c->getA()));
}

UiFontAttribute *UiFontAttribute::newUnderline(int underlineAttr) {
	return new UiFontAttribute(uiNewUnderlineAttribute(underlineAttr));
}

UiFontAttribute *UiFontAttribute::newUnderlineColor(int underlineColorAttr, Color *c) {
	return new UiFontAttribute(uiNewUnderlineColorAttribute(underlineColorAttr, c->getR(), c->getG(), c->getB(), c->getA()));
}



NBIND_CLASS(UiFontAttribute) {
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
	method(newUnderlineColor);
}
