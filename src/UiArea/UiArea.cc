
class UiArea {
	UiArea(UiAreaHandler ah);
	UiArea(UiAreaHandler ah, int width, int height);
	void setSize(int width, int height);
	void queueRedrawAll();
	void scrollTo(double x, double y, double width, double height);
}
