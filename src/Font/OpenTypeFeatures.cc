#include "../../ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"

OpenTypeFeatures::OpenTypeFeatures(uiOpenTypeFeatures *feat) {
	f = feat;
}

OpenTypeFeatures::OpenTypeFeatures() {
	f = uiNewOpenTypeFeatures();
}

void OpenTypeFeatures::free() {
	uiFreeOpenTypeFeatures(f);
}

uiOpenTypeFeatures *OpenTypeFeatures::getHandle() {
	return f;
}

OpenTypeFeatures *OpenTypeFeatures::clone(OpenTypeFeatures *f2) {
	return new OpenTypeFeatures(uiOpenTypeFeaturesClone(f2->f));
}

void OpenTypeFeatures::add(const char *tag, uint32_t value) {
	uiOpenTypeFeaturesAdd(f, tag[0], tag[1], tag[2], tag[3], value);
}

void OpenTypeFeatures::remove(const char *tag) {
	uiOpenTypeFeaturesRemove(f, tag[0], tag[1], tag[2], tag[3]);
}

int OpenTypeFeatures::get(const char *tag, uint32_t *value) {
	return uiOpenTypeFeaturesGet(f, tag[0], tag[1], tag[2], tag[3], value);
}

static unsigned int OpenTypeFeatures__forEach(const uiOpenTypeFeatures *otf, char a, char b, char c, char d, uint32_t value, void *data) {
	const char tag[5] = {a, b, c, d, '\0'};
	nbind::cbFunction *cb = (nbind::cbFunction *) data;
	return cb->call<unsigned int>(
		OpenTypeFeatures((uiOpenTypeFeatures*)otf),
		&tag[0], value);
}

void OpenTypeFeatures::forEach(nbind::cbFunction& cb) {
	uiOpenTypeFeaturesForEach(f, OpenTypeFeatures__forEach, &cb);
}

NBIND_CLASS(OpenTypeFeatures) {
	construct<>();
	method(free);
	method(clone);
	method(add);
	method(remove);
	method(get);
	method(forEach);
}
