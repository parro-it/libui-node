// TODO document drag captures
struct UiAreaMouseEvent {
	// TODO document what these mean for scrolling areas
	double X;
	double Y;

	// TODO see draw above
	double AreaWidth;
	double AreaHeight;

	int Down;
	int Up;

	int Count;

	char Modifiers;

	uint Held1To64;
};
