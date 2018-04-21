#ifndef UI_NODE_AREA
#define UI_NODE_AREA 1

#include <map>
#include <vector>
#include "nbind/api.h"
#include "control.h"
#include "ui.h"
#include "values.h"

// TODO - document
class UiArea : public UiControl {
  public:
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

class OpenTypeFeatures {
  private:
	uiOpenTypeFeatures *f;

  public:
	OpenTypeFeatures();
	OpenTypeFeatures(OpenTypeFeatures &&other);
	OpenTypeFeatures(uiOpenTypeFeatures *feat);
	~OpenTypeFeatures();
	uiOpenTypeFeatures *getHandle();

	static OpenTypeFeatures clone(OpenTypeFeatures *f2);
	void add(const char *tag, uint32_t value);
	void remove(const char *tag);
	std::array<unsigned int, 2> getInternal(const char *tag);

	void forEach(nbind::cbFunction &cb);
};

class FontAttribute {
  private:
	uiAttribute *a;
	int appended = 0;

  public:
	FontAttribute(FontAttribute &&other);
	FontAttribute(uiAttribute *a);
	~FontAttribute();
	void setAppended();
	int getAttributeType();
	uiAttribute *getHandle();

	const char *getFamilyInternal();
	double getSizeInternal();
	int getWeightInternal();
	int getItalicInternal();
	int getStretchInternal();
	Color getColorInternal();
	int getUnderlineInternal();
	std::vector<Color> getUnderlineColorInternal();
	OpenTypeFeatures getOTFeaturesInternal();

	static FontAttribute newFamily(const char *family);
	static FontAttribute newSize(double size);
	static FontAttribute newWeight(int weightAttribute);
	static FontAttribute newItalic(int italicAttribute);
	static FontAttribute newStretch(int stretchAttribute);
	static FontAttribute newColor(Color c);
	static FontAttribute newBackgroundColor(Color c);
	static FontAttribute newUnderline(int underlineAttr);
	static FontAttribute newUnderlineColor2(int underlineColorAttr, Color c);
	static FontAttribute newOTFeatures(OpenTypeFeatures *otf);
};

class AttributedString {
  private:
	uiAttributedString *s;

  public:
	AttributedString(uiAttributedString *str);
	AttributedString(const char *str);
	~AttributedString();
	uiAttributedString *getHandle();
	const char *toString();
	size_t toStringLen();

	void appendUnattributed(const char *str);
	void insertUnattributed(const char *str, size_t at);
	void deleteString(size_t start, size_t end);
	void setAttribute(FontAttribute *attr, size_t start, size_t end);

	void appendAttributedInternal(const char *str,
								  std::vector<FontAttribute *> attrs);
	void insertAttributedInternal(const char *str, size_t start,
								  std::vector<FontAttribute *> attrs);

	void forEach(nbind::cbFunction &cb);

	size_t numGraphemes();
	size_t byteIndexToGrapheme(size_t pos);
	size_t graphemeToByteIndex(size_t pos);
};

class FontDescriptor {
  private:
	uiFontDescriptor *d;
	int buttonCleanup = 0;

  public:
	FontDescriptor(FontDescriptor &&other);
	FontDescriptor(uiFontDescriptor *d);
	FontDescriptor(const char *family, double size, int weight, int italic,
				   int stretch);
	~FontDescriptor();
	char *getFamily();
	double getSize();
	int getWeight();
	int getItalic();
	int getStretch();
	uiFontDescriptor *getHandle();
};

class DrawTextLayout {
  private:
	uiDrawTextLayout *handle;

  public:
	DrawTextLayout(AttributedString *s, FontDescriptor *defaultFont,
				   double width, int align);
	~DrawTextLayout();
	SizeDouble getExtents();
	uiDrawTextLayout *getHandle();
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
