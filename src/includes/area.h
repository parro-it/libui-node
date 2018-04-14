#ifndef UI_NODE_AREA
#define UI_NODE_AREA 1

#include <map>
#include <vector>
#include "nbind/api.h"
#include "control.h"
#include "ui.h"
#include "values.h"

// UIArea

// TODO - document
class UiArea : public UiControl {
  public:
	// Workaround for nbind bug solved in 0.3
	UiArea(int dummy);

	UiArea(nbind::cbFunction &drawCb, nbind::cbFunction &mouseEventCb,
		   nbind::cbFunction &mouseCrossedCb, nbind::cbFunction &dragBrokenCb,
		   nbind::cbFunction &keyEventCb);
	UiArea(nbind::cbFunction &drawCb, nbind::cbFunction &mouseEventCb,
		   nbind::cbFunction &mouseCrossedCb, nbind::cbFunction &dragBrokenCb,
		   nbind::cbFunction &keyEventCb, int width, int height);
	void setSize(int width, int height);
	void queueRedrawAll();
	void scrollTo(double x, double y, double width, double height);
};

extern std::map<uiArea *, UiArea *> areasMap;

class DrawStrokeParams {
  private:
	uiDrawStrokeParams *sp;

  public:
	DrawStrokeParams();
	~DrawStrokeParams();
	int getCap();
	int getJoin();
	double getThickness();
	double getMiterLimit();
	std::vector<double> getDashes();
	double getDashPhase();
	void setCap(int value);
	void setJoin(int value);
	void setThickness(double value);
	void setMiterLimit(double value);
	void setDashes(std::vector<double> value);
	void setDashPhase(double value);
	uiDrawStrokeParams *toStruct();
	// void toJS(nbind::cbOutput output);
};

class UiDrawMatrix {
  private:
	uiDrawMatrix *m;

  public:
	UiDrawMatrix();
	~UiDrawMatrix();
	uiDrawMatrix *getStruct();
	double getM11();
	double getM12();
	double getM21();
	double getM22();
	double getM31();
	double getM32();
	void setM11(double value);
	void setM12(double value);
	void setM21(double value);
	void setM22(double value);
	void setM31(double value);
	void setM32(double value);
	void setIdentity();
	void translate(double x, double y);
	void scale(double xCenter, double yCenter, double x, double y);
	void rotate(double x, double y, double amount);
	void skew(double x, double y, double xamount, double yamount);
	void multiply(UiDrawMatrix *src);
	int invertible();
	int invert();
	PointDouble transformPoint(PointDouble value);
	SizeDouble transformSize(SizeDouble value);
};

class BrushGradientStop {
  private:
	double p;
	Color c;

  public:
	BrushGradientStop(double pos, Color color);
	Color getColor();
	void setColor(Color value);
	double getPos();
	void setPos(double value);
	void toJS(nbind::cbOutput output);
};

class DrawBrush {
  private:
	uiDrawBrush *b;

  public:
	DrawBrush();
	~DrawBrush();
	Color getColor();
	void setColor(Color value);
	Point getStart();
	void setStart(Point value);
	Point getEnd();
	void setEnd(Point value);
	double getOuterRadius();
	void setOuterRadius(double r);
	int getType();
	void setType(int value);
	std::vector<BrushGradientStop> getStops();
	void setStops(std::vector<BrushGradientStop> value);
	uiDrawBrush *toStruct();
};

class UiAreaMouseEvent {
  private:
	uiAreaMouseEvent *e;

  public:
	UiAreaMouseEvent(uiAreaMouseEvent *event);
	double getX();
	double getY();
	double getAreaWidth();
	double getAreaHeight();
	int getDown();
	int getUp();
	int getCount();
	int getModifiers();
	unsigned int getHeld1To64();
};

class UiAreaKeyEvent {
  private:
	uiAreaKeyEvent *e;

  public:
	UiAreaKeyEvent(uiAreaKeyEvent *event);
	std::string getKey();
	int getExtKey();
	int getModifier();
	int getModifiers();
	int getUp();
};

class UiDrawPath {
  private:
	uiDrawPath *handle;

  public:
	uiDrawPath *getHandle();
	UiDrawPath(int fillMode);
	void freePath();
	void newFigure(double x, double y);
	void newFigureWithArc(double xCenter, double yCenter, double radius,
						  double startAngle, double sweep, int negative);
	void lineTo(double x, double y);
	void arcTo(double xCenter, double yCenter, double radius, double startAngle,
			   double sweep, int negative);
	void bezierTo(double c1x, double c1y, double c2x, double c2y, double endX,
				  double endY);
	void closeFigure();
	void addRectangle(double x, double y, double width, double height);
	void end();
};

class DrawTextFontMetrics {
  private:
	uiDrawTextFontMetrics *m;

  public:
	DrawTextFontMetrics(uiDrawTextFontMetrics *metrics);
	double getAscent();
	double getDescent();
	double getLeading();
	double getUnderlinePos();
	double getUnderlineThickness();
};

class DrawTextFontDescriptor {
  private:
	uiDrawTextFontDescriptor *d;

  public:
	DrawTextFontDescriptor(uiDrawTextFontDescriptor *descr);
	const char *getFamily();
	double getSize();
	int getWeight();
	int getItalic();
	int getStretch();
};

class DrawTextFont {
  private:
	uiDrawTextFont *handle;

  public:
	DrawTextFont();
	DrawTextFont(uiDrawTextFont *h);

	uiDrawTextFont *getHandle();
	void free();
	DrawTextFontDescriptor *describe();
	DrawTextFontMetrics *getMetrics();

	static std::vector<char *> listFontFamilies();
	void loadClosestFont(const char *family, double size, int weight,
						 int italic, int stretch);
};

class DrawTextLayout {
  private:
	uiDrawTextLayout *handle;
	double w;

  public:
	DrawTextLayout(const char *text, DrawTextFont *defaultFont, double width);
	void free();
	void setWidth(double value);
	double getWidth();
	SizeDouble getExtents();
	uiDrawTextLayout *getHandle();
	void setColor(int startChar, int endChar, Color color);
};

class UiDrawContext {
  private:
	uiDrawContext *c;

  public:
	UiDrawContext(uiDrawContext *ctx);
	void stroke(UiDrawPath *path, DrawBrush *b, DrawStrokeParams *p);
	void fill(UiDrawPath *path, DrawBrush *b);
	void transform(UiDrawMatrix *m);
	void clip(UiDrawPath *path);
	void save();
	void restore();
	void text(double x, double y, DrawTextLayout *layout);
};

class UiAreaDrawParams {
  private:
	uiAreaDrawParams *p;

  public:
	UiAreaDrawParams(uiAreaDrawParams *params);
	UiDrawContext *getContext();
	double getAreaWidth();
	double getAreaHeight();
	double getClipX();
	double getClipY();
	double getClipWidth();
	double getClipHeight();
};

typedef struct UiAreaHandler {
	void (*Draw)(UiAreaHandler *self, uiArea *area, uiAreaDrawParams *params);
	void (*MouseEvent)(UiAreaHandler *self, uiArea *area,
					   uiAreaMouseEvent *event);
	void (*MouseCrossed)(UiAreaHandler *self, uiArea *area, int left);
	void (*DragBroken)(UiAreaHandler *self, uiArea *area);
	int (*KeyEvent)(UiAreaHandler *self, uiArea *area, uiAreaKeyEvent *event);

	nbind::cbFunction *draw;
	nbind::cbFunction *mouseEvent;
	nbind::cbFunction *mouseCrossed;
	nbind::cbFunction *dragBroken;
	nbind::cbFunction *keyEvent;
} UiAreaHandler;

struct UiAreaHandlerFactory {
	static UiAreaHandler *build(nbind::cbFunction &draw,
								nbind::cbFunction &mouseEvent,
								nbind::cbFunction &mouseCrossed,
								nbind::cbFunction &dragBroken,
								nbind::cbFunction &keyEvent);
};

// This is included at end of file
// to minimize conflicts with existing
// symbols from other headers.
#include "nbind/nbind.h"

#endif
