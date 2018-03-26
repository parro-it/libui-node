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

void UiOpenTypeFeatures::add(const char *c, uint32_t value) {
	uiOpenTypeFeaturesAdd(f, c[0], c[1], c[2], c[3], value);
}

void UiOpenTypeFeatures::remove(const char *c) {
	uiOpenTypeFeaturesRemove(f, c[0], c[1], c[2], c[3]);
}

// uiOpenTypeFeaturesGet() determines whether the given feature
// tag is present in otf. If it is, *value is set to the tag's value and
// nonzero is returned. Otherwise, zero is returned.
//
// Note that if uiOpenTypeFeaturesGet() returns zero, value isn't
// changed. This is important: if a feature is not present in a
// uiOpenTypeFeatures, the feature is NOT treated as if its
// value was zero anyway. Script-specific font shaping rules and
// font-specific feature settings may use a different default value
// for a feature. You should likewise not treat a missing feature as
// having a value of zero either. Instead, a missing feature should
// be treated as having some unspecified default value.
int UiOpenTypeFeatures::get(const char *c, uint32_t *value) {
	return uiOpenTypeFeaturesGet(f, c[0], c[1], c[2], c[3], value);
}

static unsigned int UiOpenTypeFeatures__forEach(const uiOpenTypeFeatures *otf, char a, char b, char c, char d, uint32_t value, void *data) {
	const char str[5] = {a, b, c, d, '\0'};
	nbind::cbFunction *cb = (nbind::cbFunction *) data;
	return cb->call<unsigned int>(
		UiOpenTypeFeatures((uiOpenTypeFeatures*)otf),
		str, value, NULL);
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
