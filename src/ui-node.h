// A2DD.h
#ifndef ui_node
#define ui_node

#define DEFINE_CONTROL_METHODS() \
	void destroy(); \
	void setParent (UiControl *parent); \
	int toplevel(); \
	int getVisible(); \
	void setVisible(int visible); \
	int getEnabled(); \
	void setEnabled(int enabled);

#define INHERITS_CONTROL_METHODS(CLASS) \
	void CLASS::destroy() { UiControl::destroy(); } \
	void CLASS::setParent(UiControl *parent) { UiControl::setParent(parent); } \
	int CLASS::toplevel() { return UiControl::toplevel(); } \
	int CLASS::getVisible() { return UiControl::getVisible(); } \
	void CLASS::setVisible(int visible) { UiControl::setVisible(visible); } \
	int CLASS::getEnabled() { return UiControl::getEnabled(); } \
	void CLASS::setEnabled(int enabled) { UiControl::setEnabled(enabled); }

#define DECLARE_CONTROL_METHODS() \
	method(destroy); \
	method(setParent); \
	method(toplevel); \
	getset(getVisible, setVisible); \
	getset(getEnabled, setEnabled);


class UiControl {
	private:
		uiControl *handle;

	public:
		uiControl * getHandle();
		UiControl(uiControl *hnd);
		DEFINE_CONTROL_METHODS()
};




class UiEntry : public UiControl {
	public:
		UiEntry();
		DEFINE_CONTROL_METHODS()
};


class UiLabel : public UiControl {
	public:
		UiLabel(const char *text);
		DEFINE_CONTROL_METHODS()
};


class UiButton : public UiControl {
	public:
		UiButton(const char *text);
		DEFINE_CONTROL_METHODS()
};


class UiBox : public UiControl {
	public:
		UiBox(uiControl *hnd);
		void append(UiControl *control, int stretchy);
};

class UiVerticalBox : public UiBox {
	public:
		UiVerticalBox();
		void append(UiControl *control, int stretchy);
		DEFINE_CONTROL_METHODS()
};

class UiHorizontalBox : public UiBox {
	public:
		UiHorizontalBox();
		void append(UiControl *control, int stretchy);
		DEFINE_CONTROL_METHODS()
};

class UiWindow {
	private:
		uiWindow *win;

	public:
		UiWindow(const char* title, int width, int height, int hasMenubar);
		void show();
		void close();
		void setMargined(int margined);
		int getMargined();
		void setChild(UiControl *control);
};


#endif
