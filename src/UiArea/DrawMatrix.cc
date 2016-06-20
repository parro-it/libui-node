
struct uiDrawMatrix {
	double M11;
	double M12;
	double M21;
	double M22;
	double M31;
	double M32;
};


_UI_EXTERN void uiDrawMatrixSetIdentity(uiDrawMatrix *m);
_UI_EXTERN void uiDrawMatrixTranslate(uiDrawMatrix *m, double x, double y);
_UI_EXTERN void uiDrawMatrixScale(uiDrawMatrix *m, double xCenter, double yCenter, double x, double y);
_UI_EXTERN void uiDrawMatrixRotate(uiDrawMatrix *m, double x, double y, double amount);
_UI_EXTERN void uiDrawMatrixSkew(uiDrawMatrix *m, double x, double y, double xamount, double yamount);
_UI_EXTERN void uiDrawMatrixMultiply(uiDrawMatrix *dest, uiDrawMatrix *src);
_UI_EXTERN int uiDrawMatrixInvertible(uiDrawMatrix *m);
_UI_EXTERN int uiDrawMatrixInvert(uiDrawMatrix *m);
_UI_EXTERN void uiDrawMatrixTransformPoint(uiDrawMatrix *m, double *x, double *y);
_UI_EXTERN void uiDrawMatrixTransformSize(uiDrawMatrix *m, double *x, double *y);

