UI_EXTERN uiDrawPath *uiDrawNewPath(uiDrawFillMode fillMode);
_UI_EXTERN void uiDrawFreePath(uiDrawPath *p);
_UI_EXTERN void uiDrawPathNewFigure(uiDrawPath *p, double x, double y);
_UI_EXTERN void uiDrawPathNewFigureWithArc(uiDrawPath *p, double xCenter, double yCenter, double radius, double startAngle, double sweep, int negative);
_UI_EXTERN void uiDrawPathLineTo(uiDrawPath *p, double x, double y);
_UI_EXTERN void uiDrawPathArcTo(uiDrawPath *p, double xCenter, double yCenter, double radius, double startAngle, double sweep, int negative);
_UI_EXTERN void uiDrawPathBezierTo(uiDrawPath *p, double c1x, double c1y, double c2x, double c2y, double endX, double endY);
_UI_EXTERN void uiDrawPathCloseFigure(uiDrawPath *p);
_UI_EXTERN void uiDrawPathAddRectangle(uiDrawPath *p, double x, double y, double width, double height);
_UI_EXTERN void uiDrawPathEnd(uiDrawPath *p);


class UiDrawPath {
	private:
		uiDrawPath *handler;

	public:
		UiDrawPath(int fillMode);
		void freePath();
		void newFigure(double x, double y);
		void newFigureWithArc(double xCenter, double yCenter, double radius, double startAngle, double sweep, int negative);
		void lineTo(double x, double y);
		void arcTo(double xCenter, double yCenter, double radius, double startAngle, double sweep, int negative);
		void bezierTo(double c1x, double c1y, double c2x, double c2y, double endX, double endY);
		void closeFigure();
		void addRectangle(double x, double y, double width, double height);
		void end();
};
