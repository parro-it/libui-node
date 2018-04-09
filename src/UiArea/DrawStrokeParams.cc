#include <algorithm>
#include <vector>
#include "area.h"
#include "ui.h"

DrawStrokeParams::DrawStrokeParams() {
	sp = new uiDrawStrokeParams();
}

DrawStrokeParams::~DrawStrokeParams() {
	if (sp->NumDashes > 0) {
		delete[] sp->Dashes;
	}
	delete sp;
}

int DrawStrokeParams::getCap() {
	return sp->Cap;
}

int DrawStrokeParams::getJoin() {
	return sp->Join;
}

double DrawStrokeParams::getThickness() {
	return sp->Thickness;
}

double DrawStrokeParams::getMiterLimit() {
	return sp->MiterLimit;
}

std::vector<double> DrawStrokeParams::getDashes() {
	return std::vector<double>(sp->Dashes, sp->Dashes + sp->NumDashes);
}

double DrawStrokeParams::getDashPhase() {
	return sp->DashPhase;
}

void DrawStrokeParams::setCap(int value) {
	sp->Cap = value;
}

void DrawStrokeParams::setJoin(int value) {
	sp->Join = value;
}

void DrawStrokeParams::setThickness(double value) {
	sp->Thickness = value;
}

void DrawStrokeParams::setMiterLimit(double value) {
	sp->MiterLimit = value;
}

void DrawStrokeParams::setDashes(std::vector<double> value) {
	if (sp->NumDashes > 0) {
		delete[] sp->Dashes;
	}

	sp->NumDashes = value.size();
	if (sp->NumDashes > 0) {
		sp->Dashes = new double[sp->NumDashes];

		std::copy(value.begin(), value.end(), sp->Dashes);
	}
}

void DrawStrokeParams::setDashPhase(double value) {
	sp->DashPhase = value;
}

uiDrawStrokeParams *DrawStrokeParams::toStruct() {
	return sp;
}

NBIND_CLASS(DrawStrokeParams) {
	construct<>();

	method(getCap);
	method(getJoin);
	method(getThickness);
	method(getMiterLimit);
	method(getDashes);
	method(getDashPhase);
	method(setCap);
	method(setJoin);
	method(setThickness);
	method(setMiterLimit);
	method(setDashes);
	method(setDashPhase);
	getset(getCap, setCap);
	getset(getJoin, setJoin);
	getset(getThickness, setThickness);
	getset(getMiterLimit, setMiterLimit);
	getset(getDashes, setDashes);
	getset(getDashPhase, setDashPhase);
}
