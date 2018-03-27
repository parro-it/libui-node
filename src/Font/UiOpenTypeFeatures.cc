#include "../../ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"

UiOpenTypeFeatures::UiOpenTypeFeatures(uiOpenTypeFeatures *feat) {
	f = feat;
}

UiOpenTypeFeatures::UiOpenTypeFeatures() {
	f = uiNewOpenTypeFeatures();
}

void UiOpenTypeFeatures::free() {
	uiFreeOpenTypeFeatures(f);
}

uiOpenTypeFeatures *UiOpenTypeFeatures::getHandle() {
	return f;
}

UiOpenTypeFeatures *UiOpenTypeFeatures::clone(UiOpenTypeFeatures *f2) {
	return new UiOpenTypeFeatures(uiOpenTypeFeaturesClone(f2->f));
}

void UiOpenTypeFeatures::add(const char *tag, uint32_t value) {
	uiOpenTypeFeaturesAdd(f, tag[0], tag[1], tag[2], tag[3], value);
}

void UiOpenTypeFeatures::remove(const char *tag) {
	uiOpenTypeFeaturesRemove(f, tag[0], tag[1], tag[2], tag[3]);
}

int UiOpenTypeFeatures::get(const char *tag, uint32_t *value) {
	return uiOpenTypeFeaturesGet(f, tag[0], tag[1], tag[2], tag[3], value);
}

static unsigned int UiOpenTypeFeatures__forEach(const uiOpenTypeFeatures *otf, char a, char b, char c, char d, uint32_t value, void *data) {
	const char tag[5] = {a, b, c, d, '\0'};
	nbind::cbFunction *cb = (nbind::cbFunction *) data;
	return cb->call<unsigned int>(
		UiOpenTypeFeatures((uiOpenTypeFeatures*)otf),
		&tag[0], value);
}

void UiOpenTypeFeatures::forEach(nbind::cbFunction& cb) {
	uiOpenTypeFeaturesForEach(f, UiOpenTypeFeatures__forEach, &cb);
}

NBIND_CLASS(UiOpenTypeFeatures) {
	construct<>();
	method(free);
	method(clone);
	method(add);
	method(remove);
	method(get);
	method(forEach);
}
