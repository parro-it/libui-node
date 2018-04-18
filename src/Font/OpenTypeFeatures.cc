#include <array>
#include "area.h"
#include "ui.h"

OpenTypeFeatures::OpenTypeFeatures(OpenTypeFeatures &&other) {
	f = other.f;
	other.f = nullptr;
}

OpenTypeFeatures::OpenTypeFeatures(uiOpenTypeFeatures *feat) {
	f = feat;
}

OpenTypeFeatures::OpenTypeFeatures() {
	f = uiNewOpenTypeFeatures();
}

OpenTypeFeatures::~OpenTypeFeatures() {
	if (f != nullptr) {
		uiFreeOpenTypeFeatures(f);
	}
}

uiOpenTypeFeatures *OpenTypeFeatures::getHandle() {
	return f;
}

OpenTypeFeatures OpenTypeFeatures::clone(OpenTypeFeatures *f2) {
	return OpenTypeFeatures(uiOpenTypeFeaturesClone(f2->f));
}

void OpenTypeFeatures::add(const char *tag, uint32_t value) {
	uiOpenTypeFeaturesAdd(f, tag[0], tag[1], tag[2], tag[3], value);
}

void OpenTypeFeatures::remove(const char *tag) {
	uiOpenTypeFeaturesRemove(f, tag[0], tag[1], tag[2], tag[3]);
}

std::array<unsigned int, 2> OpenTypeFeatures::getInternal(const char *tag) {
	unsigned int value = 0;
	unsigned int exists =
		uiOpenTypeFeaturesGet(f, tag[0], tag[1], tag[2], tag[3], &value);
	return std::array<unsigned int, 2>{{value, exists}};
}

typedef struct {
	OpenTypeFeatures *otf;
	nbind::cbFunction *cb;
} ForEachData;

static uiForEach OpenTypeFeatures__forEach(const uiOpenTypeFeatures *otf,
										   char a, char b, char c, char d,
										   uint32_t value, void *dat) {
	ForEachData *data = (ForEachData *)dat;
	const char tag[5] = {a, b, c, d, '\0'};

	unsigned int v = data->cb->call<unsigned int>(data->otf, &tag[0], value);

	return v ? uiForEachStop : uiForEachContinue;
}

void OpenTypeFeatures::forEach(nbind::cbFunction &cb) {
	ForEachData d = {this, &cb};
	uiOpenTypeFeaturesForEach(f, OpenTypeFeatures__forEach, &d);
}

NBIND_CLASS(OpenTypeFeatures) {
	construct<>();
	method(clone);
	method(add);
	method(remove);
	method(getInternal);
	method(forEach);
}
