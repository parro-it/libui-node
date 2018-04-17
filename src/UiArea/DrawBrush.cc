#include <vector>
#include "area.h"
#include "ui.h"

DrawBrush::DrawBrush() {
	b = new uiDrawBrush();
}

DrawBrush::~DrawBrush() {
	if (b->NumStops > 0) {
		delete[] b->Stops;
	}
	delete b;
}

uiDrawBrush *DrawBrush::toStruct() {
	return b;
}

Color DrawBrush::getColor() {
	return Color(b->R, b->G, b->B, b->A);
}

void DrawBrush::setColor(Color value) {
	b->R = value.getR();
	b->G = value.getG();
	b->B = value.getB();
	b->A = value.getA();
}

Point DrawBrush::getStart() {
	return Point(b->X0, b->Y0);
}

void DrawBrush::setStart(Point value) {
	b->X0 = value.getX();
	b->Y0 = value.getY();
}

Point DrawBrush::getEnd() {
	return Point(b->X1, b->Y1);
}

void DrawBrush::setEnd(Point value) {
	b->X1 = value.getX();
	b->Y1 = value.getY();
}

double DrawBrush::getOuterRadius() {
	return b->OuterRadius;
}

void DrawBrush::setOuterRadius(double r) {
	b->OuterRadius = r;
}

int DrawBrush::getType() {
	return b->Type;
}

void DrawBrush::setType(int value) {
	b->Type = value;
}

std::vector<BrushGradientStop> DrawBrush::getStops() {
	std::vector<BrushGradientStop> v;
	v.reserve(b->NumStops);
	for (size_t i = 0; i < b->NumStops; i++) {
		v.insert(v.begin() + i,
				 BrushGradientStop(b->Stops[i].Pos,
								   Color(b->Stops[i].R, b->Stops[i].G,
										 b->Stops[i].B, b->Stops[i].A)));
	}
	return v;
}

void DrawBrush::setStops(std::vector<BrushGradientStop> value) {
	if (b->NumStops > 0) {
		delete[] b->Stops;
	}

	b->NumStops = value.size();
	if (b->NumStops > 0) {
		b->Stops = new uiDrawBrushGradientStop[b->NumStops];

		for (size_t i = 0; i < b->NumStops; i++) {
			Color c = value[i].getColor();
			b->Stops[i] = {value[i].getPos(), c.getR(), c.getG(), c.getB(),
						   c.getA()};
		}
	}
}

NBIND_CLASS(DrawBrush) {
	construct<>();
	method(getStart);
	method(setStart);
	method(getColor);
	method(setColor);
	method(getEnd);
	method(setEnd);
	method(getOuterRadius);
	method(setOuterRadius);
	method(getType);
	method(setType);
	method(setStops);
	method(getStops);

	getset(getColor, setColor);
	getset(getStart, setStart);
	getset(getEnd, setEnd);
	getset(getOuterRadius, setOuterRadius);
	getset(getType, setType);
	getset(getStops, setStops);
}
