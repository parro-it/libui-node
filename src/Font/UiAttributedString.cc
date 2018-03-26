#include "../../ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"

UiAttributedString::UiAttributedString(uiAttributedString *str) {
	s = str;
}

UiAttributedString::UiAttributedString(const char *str) {
	s = uiNewAttributedString(str);
}

void UiAttributedString::free() {
	uiFreeAttributedString(s);
}

uiAttributedString *UiAttributedString::getHandle() {
	return s;
}

const char * UiAttributedString::toString() {
	return uiAttributedStringString(s);
}

size_t UiAttributedString::toStringLen() {
	return uiAttributedStringLen(s);
}

void UiAttributedString::appendUnattributed(const char *str) {
	uiAttributedStringAppendUnattributed(s, str);
}

void UiAttributedString::insertUnattributed(const char *str, size_t at) {
	uiAttributedStringInsertAtUnattributed(s, str, at);
}

void UiAttributedString::deleteString(size_t start, size_t end) {
	uiAttributedStringDelete(s, start, end);
}

void UiAttributedString::setAttribute(UiFontAttribute *attr, size_t start, size_t end) {
	uiAttributedStringSetAttribute(s, attr->getHandle(), start, end);
}

static unsigned int UiAttributedString__forEach(const uiAttributedString *s, const uiAttribute *a, size_t start, size_t end, void *d) {
	return ((cb_data*)d)->cb.call<unsigned int>(
		UiAttributedString((uiAttributedString*)s),
		UiFontAttribute((uiAttribute*)a),
		start, end, ((cb_data*)d)->data);
}

void UiAttributedString::forEach(nbind::cbFunction& cb, void *data) {
	cb_data d = {cb, data};
	uiAttributedStringForEachAttribute(s, UiAttributedString__forEach, &d);
}



void UiAttributedString::appendAttributed(const char *str, UiFontAttribute *attr) {
	this->appendAttributed2(str, attr, nullptr);
}


void UiAttributedString::appendAttributed2(const char *str, UiFontAttribute *attr, UiFontAttribute *attr2) {
	size_t start = this->toStringLen();
	// TODO how this (and strlen) work with unicode?
	size_t end = start + strlen(str);

	this->appendUnattributed(str);
	this->setAttribute(attr, start, end);
	if(attr2 != nullptr){
		this->setAttribute(attr2, start, end);	
	}
}


size_t UiAttributedString::numGraphemes() {
	return uiAttributedStringNumGraphemes(s);
}

size_t UiAttributedString::byteIndexToGrapheme(size_t pos) {
	return uiAttributedStringByteIndexToGrapheme(s, pos);
}

size_t UiAttributedString::graphemeToByteIndex(size_t pos) {
	return uiAttributedStringGraphemeToByteIndex(s, pos);
}

NBIND_CLASS(UiAttributedString) {
	construct<const char *>();
	method(free);
	method(toString);
	method(toStringLen);
	method(appendUnattributed);
	method(insertUnattributed);
	method(forEach);
	method(appendAttributed);
	method(appendAttributed2);
	// multimethod(appendAttributed, args(const char *, UiFontAttribute *));
	// multimethod(appendAttributed, args(const char *, UiFontAttribute *, UiFontAttribute *), "appendAttributed2");
	method(deleteString);
	method(setAttribute);
	// method(forEachAttribute);
	method(numGraphemes);
	method(byteIndexToGrapheme);
	method(graphemeToByteIndex);
}
