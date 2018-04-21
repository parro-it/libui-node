#include <vector>
#include "area.h"
#include "ui.h"

AttributedString::AttributedString(uiAttributedString *str) {
	s = str;
}

AttributedString::AttributedString(const char *str) {
	s = uiNewAttributedString(str);
}

AttributedString::~AttributedString() {
	uiFreeAttributedString(s);
}

uiAttributedString *AttributedString::getHandle() {
	return s;
}

const char *AttributedString::toString() {
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

void AttributedString::setAttribute(FontAttribute *attr, size_t start,
									size_t end) {
	uiAttributedStringSetAttribute(s, attr->getHandle(), start, end);
	attr->setAppended();
}

typedef struct {
	AttributedString *str;
	nbind::cbFunction *cb;
} ForEachData;

static uiForEach AttributedString__forEach(const uiAttributedString *s,
										   const uiAttribute *a, size_t start,
										   size_t end, void *d) {
	ForEachData *data = (ForEachData *)d;

	FontAttribute f = FontAttribute((uiAttribute *)a);
	f.setAppended();

	unsigned int v = data->cb->call<unsigned int>(data->str, f, start, end);

	return v ? uiForEachStop : uiForEachContinue;
}

void AttributedString::forEach(nbind::cbFunction &cb) {
	ForEachData d = {this, &cb};
	uiAttributedStringForEachAttribute(s, AttributedString__forEach, &d);
}

void AttributedString::appendAttributedInternal(
	const char *str, std::vector<FontAttribute *> attrs) {
	size_t start = this->toStringLen();
	size_t end = start + strlen(str);

	this->appendUnattributed(str);
	for (std::vector<FontAttribute *>::size_type i = 0; i < attrs.size(); i++) {
		this->setAttribute(attrs[i], start, end);
	}
}

void AttributedString::insertAttributedInternal(
	const char *str, size_t start, std::vector<FontAttribute *> attrs) {
	size_t end = start + strlen(str);

	this->insertUnattributed(str, start);
	for (std::vector<FontAttribute *>::size_type i = 0; i < attrs.size(); i++) {
		this->setAttribute(attrs[i], start, end);
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
	method(toString);
	method(toStringLen);
	method(appendUnattributed);
	method(insertUnattributed);
	method(forEach);
	method(appendAttributedInternal);
	method(insertAttributedInternal);
	method(deleteString);
	method(setAttribute);

	method(numGraphemes);
	method(byteIndexToGrapheme);
	method(graphemeToByteIndex);
}
