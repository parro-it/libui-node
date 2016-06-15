
struct uiAreaDrawParams {
	void *Context;

	// TODO document that this is only defined for nonscrolling areas
	double AreaWidth;
	double AreaHeight;

	double ClipX;
	double ClipY;
	double ClipWidth;
	double ClipHeight;
};
