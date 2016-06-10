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




class UiRadioButtons : public UiControl {
	public:
		UiRadioButtons();
		void append(const char *text);

		DEFINE_CONTROL_METHODS()
};


class UiTab : public UiControl {
	public:
		UiTab();
		void append(const char *text, UiControl *child);

		DEFINE_CONTROL_METHODS()
};



class UiMultilineEntry : public UiControl {
	public:
		UiMultilineEntry();

		DEFINE_CONTROL_METHODS()
};


class UiCombobox : public UiControl {
	public:
		UiCombobox();
		DEFINE_CONTROL_METHODS()
};


class UiDateTimePicker : public UiControl {
	public:
		UiDateTimePicker();
		DEFINE_CONTROL_METHODS()
};


class UiEditableCombobox : public UiControl {
	public:
		UiEditableCombobox();
		DEFINE_CONTROL_METHODS()
};


#define DEFINE_ENTRY_METHODS() \
	void setText(const char *  text); \
	const char *  getText(); \
	void setReadOnly(int readOnly); \
	int getReadOnly();

#define INHERITS_ENTRY_METHODS(CLASS) \
	void CLASS::setText(const char *  text) { UiEntryBase::setText(text); } \
	const char *  CLASS::getText() { return UiEntryBase::getText(); } \
	void CLASS::setReadOnly(int readOnly) { UiEntryBase::setReadOnly(readOnly); }\
	int CLASS::getReadOnly() { return UiEntryBase::getReadOnly(); }

#define DECLARE_ENTRY_METHODS() \
	getset(getText, setText); \
	getset(getReadOnly, setReadOnly);


class UiEntryBase : public UiControl {
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
};


class UiPasswordEntry : public UiEntryBase {
	public:
		UiPasswordEntry();
		DEFINE_CONTROL_METHODS()
		DEFINE_ENTRY_METHODS()
};


class UiSearchEntry : public UiEntryBase {
	public:
		UiSearchEntry();
		DEFINE_CONTROL_METHODS()
		DEFINE_ENTRY_METHODS()
};


class UiSeparator : public UiControl {
	public:
		UiSeparator();
		DEFINE_CONTROL_METHODS()
};


class UiLabel : public UiControl {
	public:
		UiLabel(const char *text);
		DEFINE_CONTROL_METHODS()
};


class UiGroup : public UiControl {
	public:
		UiGroup(const char *text);
		void setChild(UiControl *control);
		DEFINE_CONTROL_METHODS()
};


class UiButton : public UiControl {
	public:
		UiButton(const char *text);
		DEFINE_CONTROL_METHODS()
};


class UiCheckbox : public UiControl {
	public:
		UiCheckbox(const char *text);
		DEFINE_CONTROL_METHODS()
};


class UiProgressBar : public UiControl {
	public:
		UiProgressBar();
		DEFINE_CONTROL_METHODS()
};


class UiSlider : public UiControl {
	public:
		UiSlider(int min, int max);
		DEFINE_CONTROL_METHODS()

		int getValue();
		void setValue(int value);
};


class UiSpinbox : public UiControl {
	public:
		UiSpinbox(int min, int max);
		DEFINE_CONTROL_METHODS()

		int getValue();
		void setValue(int value);
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
