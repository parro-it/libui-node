
_UI_EXTERN void uiDrawStroke(uiDrawContext *c, uiDrawPath *path, uiDrawBrush *b, uiDrawStrokeParams *p);
_UI_EXTERN void uiDrawFill(uiDrawContext *c, uiDrawPath *path, uiDrawBrush *b);

_UI_EXTERN void uiDrawTransform(uiDrawContext *c, uiDrawMatrix *m);

// TODO add a uiDrawPathStrokeToFill() or something like that
_UI_EXTERN void uiDrawClip(uiDrawContext *c, uiDrawPath *path);

_UI_EXTERN void uiDrawSave(uiDrawContext *c);
_UI_EXTERN void uiDrawRestore(uiDrawContext *c);

_UI_EXTERN void uiDrawText(uiDrawContext *c, double x, double y, uiDrawTextLayout *layout);


class UiDrawContext {
	private:
		uiDrawContext *c;

	public:
		UiDrawContext(uiDrawContext *ctx);
		void stroke(UiDrawPath *path, UiDrawBrush *b, uiDrawStrokeParams *p);
		void fill(uiDrawPath *path, uiDrawBrush *b);
		void transform(uiDrawMatrix *m);
		void clip(uiDrawPath *path);
		void save();
		void restore();
		void text(double x, double y, uiDrawTextLayout *layout);

};
