#include "../../ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"

DrawBrush::DrawBrush(Color color, Point start, Point end, int type, std::vector<BrushGradientStop> stops) :
c(color), s(start), e(end)
 {
	t = type;
	st = stops;
}

uiDrawBrush * DrawBrush::toStruct() {
	uiDrawBrush * b = new uiDrawBrush();
	b->R = c.getR();
	b->G = c.getG();
	b->B = c.getB();
	b->A = c.getA();
	b->X0 = s.getX();
	b->Y0 = s.getY();
	b->X1 = e.getX();
	b->Y1 = e.getY();
	b->NumStops = st.size();
	uiDrawBrushGradientStop* stops = new uiDrawBrushGradientStop[st.size()];
	for (unsigned long i = 0; i < st.size(); i++) {
		stops[i].Pos = st[i].getPos();
		stops[i].R = st[i].getColor().getR();
		stops[i].G = st[i].getColor().getG();
		stops[i].B = st[i].getColor().getB();
		stops[i].A = st[i].getColor().getA();
	}
	b->Stops = stops;
	return b;
}

Color DrawBrush::getColor() {
	return c;
}

void DrawBrush::setColor(Color value) {
	c = value;
}


Point DrawBrush::getStart() {
	return s;
}

void DrawBrush::setStart(Point value) {
	s = value;
}

Point DrawBrush::getEnd() {
	return e;
}

void DrawBrush::setEnd(Point value) {
	e = value;
}

int DrawBrush::getType() {
	return t;
}

void DrawBrush::setType(int value) {
	t = value;
}


std::vector<BrushGradientStop> DrawBrush::getStops() {
	return st;
}

void DrawBrush::setStops(std::vector<BrushGradientStop> value) {
	st = value;
}

void DrawBrush::toJS(nbind::cbOutput output) {
	output(c, s, e, t, st);
}

NBIND_CLASS(DrawBrush) {
  construct<Color, Point, Point, int, std::vector<BrushGradientStop>>();
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
