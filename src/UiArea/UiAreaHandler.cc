class UiAreaHandler {
	void Draw(UiAreaHandler *self, UiArea *area, UiAreaDrawParams *params);
	void MouseEvent(UiAreaHandler *self, UiArea *area, UiAreaMouseEvent *event);
	void MouseCrossed(UiAreaHandler *self, UiArea *area, int left);
	void DragBroken(UiAreaHandler *self, UiArea *area);
	int KeyEvent(UiAreaHandler *self, UiArea *area, UiAreaKeyEvent *event);
};
