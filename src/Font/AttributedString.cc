#include "../../ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"

AttributedString::AttributedString(uiAttributedString *str) {
	s = str;
}

AttributedString::AttributedString(const char *str) {
	s = uiNewAttributedString(str);
}

void AttributedString::free() {
	uiFreeAttributedString(s);
}

uiAttributedString *AttributedString::getHandle() {
	return s;
}

const char * AttributedString::toString() {
	return uiAttributedStringString(s);
}

size_t AttributedString::toStringLen() {
	return uiAttributedStringLen(s);
}

void AttributedString::appendUnattributed(const char *str) {
	uiAttributedStringAppendUnattributed(s, str);
}

void AttributedString::insertUnattributed(const char *str, size_t at) {
	uiAttributedStringInsertAtUnattributed(s, str, at);
}

void AttributedString::deleteString(size_t start, size_t end) {
	uiAttributedStringDelete(s, start, end);
}

void AttributedString::setAttribute(FontAttribute *attr, size_t start, size_t end) {
	uiAttributedStringSetAttribute(s, attr->getHandle(), start, end);
	attr->setAppended();
}

static unsigned int AttributedString__forEach(const uiAttributedString *s, const uiAttribute *a, size_t start, size_t end, void *data) {
	nbind::cbFunction *cb = (nbind::cbFunction *) data;

	return cb->call<unsigned int>(
		AttributedString((uiAttributedString*)s),
		FontAttribute((uiAttribute*)a),
		start, end);
}

void AttributedString::forEach(nbind::cbFunction& cb) {
	uiAttributedStringForEachAttribute(s, AttributedString__forEach, &cb);
}



void AttributedString::appendAttributed(const char *str, FontAttribute *attr) {
	this->appendAttributed(str, attr, nullptr);
}


void AttributedString::appendAttributed(const char *str, FontAttribute *attr, FontAttribute *attr2) {
	size_t start = this->toStringLen();
	// TODO how this (and strlen) work with unicode?
	size_t end = start + strlen(str);

	this->appendUnattributed(str);
	this->setAttribute(attr, start, end);
	if(attr2 != nullptr){
		this->setAttribute(attr2, start, end);
	}
}


size_t AttributedString::numGraphemes() {
	return uiAttributedStringNumGraphemes(s);
}

size_t AttributedString::byteIndexToGrapheme(size_t pos) {
	return uiAttributedStringByteIndexToGrapheme(s, pos);
}

size_t AttributedString::graphemeToByteIndex(size_t pos) {
	return uiAttributedStringGraphemeToByteIndex(s, pos);
}

NBIND_CLASS(AttributedString) {
	construct<const char *>();
	method(free);
	method(toString);
	method(toStringLen);
	method(appendUnattributed);
	method(insertUnattributed);
	method(forEach);
	multimethod(appendAttributed, args(const char *, FontAttribute *), "appendAttributed1");
	multimethod(appendAttributed, args(const char *, FontAttribute *, FontAttribute *), "appendAttributed2");
	method(deleteString);
	method(setAttribute);

	method(numGraphemes);
	method(byteIndexToGrapheme);
	method(graphemeToByteIndex);
}
