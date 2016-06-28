#include "../../ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"

DrawBrush::DrawBrush()
 {
	b = new uiDrawBrush();
}

uiDrawBrush * DrawBrush::toStruct() {
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

int DrawBrush::getType() {
	return b->Type;
}

void DrawBrush::setType(int value) {
	b->Type = value;
}


std::vector<BrushGradientStop> DrawBrush::getStops() {
	return std::vector<BrushGradientStop>();
}

void DrawBrush::setStops(std::vector<BrushGradientStop> value) {
	// st = value;
}


NBIND_CLASS(DrawBrush) {
  construct<>();
  method(getStart);
  method(setStart);
  method(getColor);
  method(setColor);
  method(getEnd);
  method(setEnd);
  method(getType);
  method(setType);
  method(setStops);
  method(getStops);

  getset(getColor, setColor);
  getset(getStart, setStart);
  getset(getEnd, setEnd);
  getset(getType, setType);
  getset(getStops, setStops);
}
