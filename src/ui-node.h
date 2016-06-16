// A2DD.h
#ifndef ui_node
#define ui_node

#include "nbind/api.h"


#define DEFINE_EVENT(NAME) \
	private: \
		nbind::cbFunction * NAME ## Callback = NULL; \
	public: \
		void NAME(nbind::cbFunction & cb); \


#define IMPLEMENT_EVENT(CLASS, WIDGET, NAME, LIBUI_FUN) \
	static void CLASS ## _ ## NAME(WIDGET *w, void *data) { \
		nbind::cbFunction *cb = (nbind::cbFunction *) data; \
		(*cb)(); \
	} \
 	void CLASS::NAME(nbind::cbFunction & cb) { \
		NAME ## Callback = new nbind::cbFunction(cb); \
		LIBUI_FUN( \
			(WIDGET *) getHandle(), \
			CLASS ## _ ## NAME, \
			NAME ## Callback \
		); \
	}

#define DEFINE_CONTROL_METHODS() \
	void destroy(); \
	void setParent (UiControl *parent); \
	bool toplevel(); \
	bool getVisible(); \
	void setVisible(bool visible); \
	bool getEnabled(); \
	void setEnabled(bool enabled);

#define INHERITS_CONTROL_METHODS(CLASS) \
	void CLASS::destroy() { UiControl::destroy(); } \
	void CLASS::setParent(UiControl *parent) { UiControl::setParent(parent); } \
	bool CLASS::toplevel() { return UiControl::toplevel(); } \
	bool CLASS::getVisible() { return UiControl::getVisible(); } \
	void CLASS::setVisible(bool visible) { UiControl::setVisible(visible); } \
	bool CLASS::getEnabled() { return UiControl::getEnabled(); } \
	void CLASS::setEnabled(bool enabled) { UiControl::setEnabled(enabled); }

#define DECLARE_CONTROL_METHODS() \
	method(destroy); \
	method(setParent); \
	method(toplevel); \
	method(getVisible); \
	method(setVisible); \
	method(getEnabled); \
	method(setEnabled); \
	getset(getVisible, setVisible); \
	getset(getEnabled, setEnabled);


#define DEFINE_ENTRY_METHODS() \
	void setText(const char *  text); \
	const char *  getText(); \
	void setReadOnly(bool readOnly); \
	bool getReadOnly(); \



#define INHERITS_ENTRY_METHODS(CLASS) \
	void CLASS::setText(const char *  text) { UiEntryBase::setText(text); } \
	const char *  CLASS::getText() { return UiEntryBase::getText(); } \
	void CLASS::setReadOnly(bool readOnly) { UiEntryBase::setReadOnly(readOnly); }\
	bool CLASS::getReadOnly() { return UiEntryBase::getReadOnly(); } \
	void CLASS::onChanged(nbind::cbFunction & cb) { UiEntryBase::onChanged(cb); }

#define DECLARE_ENTRY_METHODS() \
	getset(getText, setText); \
	getset(getReadOnly, setReadOnly); \
	method(onChanged); \
	method(getText); \
	method(setText); \
	method(getReadOnly); \
	method(setReadOnly);


#define DEFINE_BOX_METHODS() \
	void append(UiControl *control, int stretchy); \
	void deleteAt(int index); \
	int getPadded(); \
	void setPadded(int padded);

#define INHERITS_BOX_METHODS(CLASS) \
	void CLASS::append(UiControl *control, int stretchy) { UiBox::append(control, stretchy); } \
	void CLASS::deleteAt(int index) { UiBox::deleteAt(index); } \
	int CLASS::getPadded() { return UiBox::getPadded(); } \
	void CLASS::setPadded(int padded) { UiBox::setPadded(padded); }

#define DECLARE_BOX_METHODS() \
	getset(getPadded, setPadded); \
	method(getPadded); \
	method(setPadded); \
	method(append); \
	method(deleteAt);

class UiControl {
	private:
		uiControl *handle;

	public:
		uiControl * getHandle();
		UiControl(uiControl *hnd);
		DEFINE_CONTROL_METHODS()
};




class UiRadioButtons : public UiControl {
	DEFINE_EVENT(onSelected)

	public:
		UiRadioButtons();
		void append(const char *text);
		int getSelected();
		void setSelected(int n);

		DEFINE_CONTROL_METHODS()
};



class UiTab : public UiControl {
	public:
		UiTab();
		void append(const char *text, UiControl *child);
		void insertAt(const char *name, int before, UiControl *child);
		void deleteAt(int index);
		int numPages();
		int getMargined(int page);
		void setMargined(int page, int margined);

		DEFINE_CONTROL_METHODS()
};



class UiMultilineEntry : public UiControl {
	DEFINE_EVENT(onChanged)


	public:
		UiMultilineEntry();
		DEFINE_CONTROL_METHODS()
		void setText(const char *  text);
		const char * getText();
		void setReadOnly(bool readOnly);
		bool getReadOnly();
		void append(const char *text);
};


class UiCombobox : public UiControl {
	DEFINE_EVENT(onSelected)

	public:
		UiCombobox();
		DEFINE_CONTROL_METHODS()
		void append(const char *text);
		int getSelected();
		void setSelected(int n);
};




class UiDateTimePicker : public UiControl {
	public:
		UiDateTimePicker();
		DEFINE_CONTROL_METHODS()
};

class UiDatePicker : public UiControl {
	public:
		UiDatePicker();
		DEFINE_CONTROL_METHODS()
};

class UiTimePicker : public UiControl {
	public:
		UiTimePicker();
		DEFINE_CONTROL_METHODS()
};


class UiEditableCombobox : public UiControl {
	DEFINE_EVENT(onChanged)

	public:
		UiEditableCombobox();
		DEFINE_CONTROL_METHODS()
		void append(const char *text);
		const char * getText();
		void setText(const char *text);

};



class UiEntryBase : public UiControl {
	DEFINE_EVENT(onChanged)

	public:
		UiEntryBase(uiControl *);
		DEFINE_CONTROL_METHODS()
		DEFINE_ENTRY_METHODS()
};

class UiEntry : public UiEntryBase {
	public:
		UiEntry();
		DEFINE_CONTROL_METHODS()
		DEFINE_ENTRY_METHODS()
		void onChanged(nbind::cbFunction & cb);
};


class UiPasswordEntry : public UiEntryBase {
	public:
		UiPasswordEntry();
		DEFINE_CONTROL_METHODS()
		DEFINE_ENTRY_METHODS()
		void onChanged(nbind::cbFunction & cb);
};


class UiSearchEntry : public UiEntryBase {
	public:
		UiSearchEntry();
		DEFINE_CONTROL_METHODS()
		DEFINE_ENTRY_METHODS()
		void onChanged(nbind::cbFunction & cb);
};


class UiSeparator : public UiControl {
	public:
		UiSeparator();
		DEFINE_CONTROL_METHODS()
};


class UiLabel : public UiControl {
	public:
		UiLabel();
		UiLabel(const char *text);
		DEFINE_CONTROL_METHODS()
		void setText(const char * text);
		const char * getText();
};


class UiGroup : public UiControl {
	public:
		UiGroup(const char *text);
		UiGroup();
		void setChild(UiControl *control);
		int getMargined();
		void setMargined(int margined);
		const char * getTitle();
		void setTitle(const char * title);
		DEFINE_CONTROL_METHODS()
};


class UiButton : public UiControl {
	DEFINE_EVENT(onClicked)

	public:
		UiButton(const char *text);
		UiButton();
		DEFINE_CONTROL_METHODS()
		void setText(const char * text);
		const char * getText();
};




class UiCheckbox : public UiControl {
	DEFINE_EVENT(onToggled)

	public:
		UiCheckbox(const char *text);
		UiCheckbox();
		DEFINE_CONTROL_METHODS()
		void setText(const char * text);
		const char * getText();
		void setChecked(bool checked);
		bool getChecked();
};


class UiProgressBar : public UiControl {
	private:
		int value = 0;

	public:
		UiProgressBar();
		DEFINE_CONTROL_METHODS()
		int getValue();
		void setValue(int value);
};


class UiSlider : public UiControl {
	DEFINE_EVENT(onChanged)

	public:
		UiSlider(int min, int max);
		UiSlider();
		DEFINE_CONTROL_METHODS()

		int getValue();
		void setValue(int value);
};


class UiSpinbox : public UiControl {
	DEFINE_EVENT(onChanged)

	public:
		UiSpinbox(int min, int max);
		UiSpinbox();
		DEFINE_CONTROL_METHODS()

		int getValue();
		void setValue(int value);
};

class UiBox : public UiControl {
	public:
		UiBox(uiControl *hnd);
	DEFINE_BOX_METHODS()
};

class UiVerticalBox : public UiBox {
	public:
		UiVerticalBox();
		DEFINE_BOX_METHODS()
		DEFINE_CONTROL_METHODS()
};

class UiHorizontalBox : public UiBox {
	public:
		UiHorizontalBox();
		DEFINE_BOX_METHODS()
		DEFINE_CONTROL_METHODS()
};

class UiWindow {
	DEFINE_EVENT(onClosing)

	private:
		uiWindow *win;

	public:
		UiWindow(const char* title, int width, int height, int hasMenubar);
		uiWindow * getHandle();
		void show();
		void close();
		void setMargined(int margined);
		int getMargined();
		void setChild(UiControl *control);
		void setTitle(const char * title);
		const char * getTitle();
};

class UiMenuItem {
	DEFINE_EVENT(onClicked)

	private:
		uiMenuItem *handle;

	public:
		UiMenuItem(uiMenuItem *hnd);
		void enable();
		void disable();
		int getChecked();
		void setChecked(int checked);
};

class UiMenu {
	private:
		uiMenu *handle;

	public:
		UiMenu(const char *name);
		UiMenuItem * appendItem(const char *name);
		UiMenuItem * appendCheckItem(const char *name);
		UiMenuItem * appendQuitItem();
		UiMenuItem * appendPreferencesItem();
		UiMenuItem * appendAboutItem();
		void appendSeparator();
};



class Color {
	private:
		double r;
		double g;
		double b;
		double a;

	public:
		Color(double r, double g, double b, double a);
		double getR(); void setR(double value);
		double getG(); void setG(double value);
		double getB(); void setB(double value);
		double getA(); void setA(double value);
		void toJS(nbind::cbOutput output);
};

class UiColorButton : public UiControl {
	DEFINE_EVENT(onChanged)

	public:
		UiColorButton();
		Color getColor();
		void setColor(Color value);
		DEFINE_CONTROL_METHODS()
};

// UIArea





// TODO document drag captures
struct UiAreaMouseEvent {
	// TODO document what these mean for scrolling areas
	double x;
	double y;

	// TODO see draw above
	double AreaWidth;
	double AreaHeight;

	int Down;
	int Up;
	int Count;
	char Modifiers;

	uint Held1To64;

};

struct UiAreaKeyEvent {
	char Key;
	int ExtKey;
	char Modifier;
	char Modifiers;
	int Up;
};

struct UiAreaDrawParams {
	void *Context;

	// TODO document that this is only defined for nonscrolling areas
	double AreaWidth;
	double AreaHeight;

	double ClipX;
	double ClipY;
	double ClipWidth;
	double ClipHeight;
};


class UiArea  : public UiControl {
	public:
		UiArea(
			nbind::cbFunction &drawCb,
			nbind::cbFunction &mouseEventCb ,
			nbind::cbFunction &mouseCrossedCb,
			nbind::cbFunction &dragBrokenCb,
			nbind::cbFunction &keyEventCb
		);
		UiArea(
			nbind::cbFunction &drawCb,
			nbind::cbFunction &mouseEventCb ,
			nbind::cbFunction &mouseCrossedCb,
			nbind::cbFunction &dragBrokenCb,
			nbind::cbFunction &keyEventCb,
			int width,
			int height
		);
		void setSize(int width, int height);
		void queueRedrawAll();
		void scrollTo(double x, double y, double width, double height);
		DEFINE_CONTROL_METHODS()
};

typedef struct UiAreaHandler {
	void (*Draw)(UiAreaHandler *self, UiArea *area, UiAreaDrawParams *params);
	void (*MouseEvent)(UiAreaHandler *self, UiArea *area, UiAreaMouseEvent *event);
	void (*MouseCrossed)(UiAreaHandler *self, UiArea *area, int left);
	void (*DragBroken)(UiAreaHandler *self, UiArea *area);
	int (*KeyEvent)(UiAreaHandler *self, UiArea *area, UiAreaKeyEvent *event);

	nbind::cbFunction *draw;
	nbind::cbFunction *mouseEvent;
	nbind::cbFunction *mouseCrossed;
	nbind::cbFunction *dragBroken;
	nbind::cbFunction *keyEvent;
} UiAreaHandler;

struct UiAreaHandlerFactory {
	static UiAreaHandler * build(
		nbind::cbFunction &draw,
		nbind::cbFunction &mouseEvent ,
		nbind::cbFunction &mouseCrossed,
		nbind::cbFunction &dragBroken,
		nbind::cbFunction &keyEvent
	);
};



#endif
