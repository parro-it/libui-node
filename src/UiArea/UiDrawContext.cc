#include "../../libui/ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"



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
		void text(double x, double y, void *layout);

};

UiDrawContext::UiDrawContext(uiDrawContext *ctx) {
	c = ctx;
}

void UiDrawContext::stroke(UiDrawPath *path, DrawBrush *b, DrawStrokeParams *p) {
	uiDrawStroke(c, path->getHandle(), b->toStruct(), p->toStruct());
}

void UiDrawContext::fill(UiDrawPath *path, DrawBrush *b) {
	uiDrawFill(c, path->getHandle(), b->toStruct());
}

void UiDrawContext::transform(UiDrawMatrix *m) {
	uiDrawTransform(c, m->getStruct());
}

void UiDrawContext::clip(UiDrawPath *path) {
	uiDrawClip(c, path->getHandle());
}

void UiDrawContext::save() {
	uiDrawSave(c);
}

void UiDrawContext::restore() {
	uiDrawRestore(c);
}

void UiDrawContext::text(double x, double y, void *layout) {
	// uiDrawText(c, x, y, layout);
}


NBIND_CLASS(UiDrawContext) {
	method(stroke);
	method(fill);
	method(transform);
	method(clip);
	method(save);
	method(restore);
	method(text);
}
