#include "../../libui/ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"



DrawStrokeParams::DrawStrokeParams(int cap, int join, double thickness, double miterLimit,std::vector<double> dashes,int numDashes,double DashPhase) {

}

int DrawStrokeParams::getCap() {
	return Cap;
}

int DrawStrokeParams::getJoin() {
	return Join;
}

double DrawStrokeParams::getThickness() {
	return Thickness;
}

double DrawStrokeParams::getMiterLimit() {
	return MiterLimit;

}

std::vector<double> DrawStrokeParams::getDashes() {
	return Dashes;
}

int DrawStrokeParams::getNumDashes() {
	return NumDashes;

}

double DrawStrokeParams::getDashPhase() {
	return DashPhase;

}

void DrawStrokeParams::setCap(int value) {

}

void DrawStrokeParams::setJoin(int value) {

}

void DrawStrokeParams::setThickness(double value) {

}

void DrawStrokeParams::setMiterLimit(double value) {

}

void DrawStrokeParams::setDashes(std::vector<double> value) {

}

void DrawStrokeParams::setNumDashes(int value) {

}

void DrawStrokeParams::setDashPhase(double value) {

}


uiDrawStrokeParams * DrawStrokeParams::toStruct() {
	return NULL;
}


void DrawStrokeParams::toJS(nbind::cbOutput output) {

}


NBIND_CLASS(DrawStrokeParams) {
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
	method(toStruct);
	method(toJS);
}
