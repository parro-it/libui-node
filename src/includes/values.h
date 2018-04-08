#ifndef UI_VALUES
#define UI_VALUES 1

#include "nbind/api.h"

class Point {
  private:
	int x;
	int y;

  public:
	Point(const Point &other);
	Point(int x, int y);
	int getX();
	void setX(int value);
	int getY();
	void setY(int value);
	void toJS(nbind::cbOutput output);
};

class Size {
  private:
	int w;
	int h;

  public:
	Size(int w, int h);
	int getWidth();
	void setWidth(int value);
	int getHeight();
	void setHeight(int value);
	void toJS(nbind::cbOutput output);
};

class PointDouble {
  private:
	double x;
	double y;

  public:
	PointDouble(double x, double y);
	PointDouble(const PointDouble &other);
	double getX();
	void setX(double value);
	double getY();
	void setY(double value);
	void toJS(nbind::cbOutput output);
};

class SizeDouble {
  private:
	double w;
	double h;

  public:
	SizeDouble(double w, double h);
	double getWidth();
	void setWidth(double value);
	double getHeight();
	void setHeight(double value);
	void toJS(nbind::cbOutput output);
};

class Color {
  private:
	double r;
	double g;
	double b;
	double a;

  public:
	Color(const Color &other);
	Color(double r, double g, double b, double a);
	double getR();
	void setR(double value);
	double getG();
	void setG(double value);
	double getB();
	void setB(double value);
	double getA();
	void setA(double value);
	void toJS(nbind::cbOutput output);
};

// This is included at end of file
// to minimize conflicts with existing
// symbols from other headers.
#include "nbind/nbind.h"

#endif
