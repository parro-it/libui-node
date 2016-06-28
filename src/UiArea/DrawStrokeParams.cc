#include "../../ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"



DrawStrokeParams::DrawStrokeParams() {
	sp = new uiDrawStrokeParams();
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
	return std::vector<double>(); // std::vector<double>(sp->Dashes);
}

int DrawStrokeParams::getNumDashes() {
	return sp->NumDashes;

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
	// sp->Dashes = value;
}

void DrawStrokeParams::setNumDashes(int value) {
	sp->NumDashes = value;
}

void DrawStrokeParams::setDashPhase(double value) {
	sp->DashPhase = value;
}


uiDrawStrokeParams * DrawStrokeParams::toStruct() {
	return sp;
}



NBIND_CLASS(DrawStrokeParams) {
	construct<>();
	method(getCap);
	method(getJoin);
	method(getThickness);
	method(getMiterLimit);
	method(getDashes);
	method(getNumDashes);
	method(getDashPhase);
	method(setCap);
	method(setJoin);
	method(setThickness);
	method(setMiterLimit);
	method(setDashes);
	method(setNumDashes);
	method(setDashPhase);
	getset(getCap,setCap);
	getset(getJoin,setJoin);
	getset(getThickness,setThickness);
	getset(getMiterLimit,setMiterLimit);
	getset(getDashes,setDashes);
	getset(getNumDashes,setNumDashes);
	getset(getDashPhase,setDashPhase);
}
