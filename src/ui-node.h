// A2DD.h
#ifndef ui_node
#define ui_node

#include "nbind/api.h"

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


#define DEFINE_ENTRY_METHODS() \
	void setText(const char *  text); \
	const char *  getText(); \
	void setReadOnly(int readOnly); \
	int getReadOnly(); \
	void onChange(nbind::cbFunction & cb);



#define INHERITS_ENTRY_METHODS(CLASS) \
	void CLASS::setText(const char *  text) { UiEntryBase::setText(text); } \
	const char *  CLASS::getText() { return UiEntryBase::getText(); } \
	void CLASS::setReadOnly(int readOnly) { UiEntryBase::setReadOnly(readOnly); }\
	int CLASS::getReadOnly() { return UiEntryBase::getReadOnly(); } \
	void CLASS::onChange(nbind::cbFunction & cb) { UiEntryBase::onChange(cb); }

#define DECLARE_ENTRY_METHODS() \
	getset(getText, setText); \
	getset(getReadOnly, setReadOnly); \
	method(onChange);


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
	public:
		UiMultilineEntry();
		DEFINE_CONTROL_METHODS()
		void setText(const char *  text);
		const char * getText();
		void setReadOnly(int readOnly);
		int getReadOnly();
		void append(const char *text);
};


class UiCombobox : public UiControl {
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


class UiEditableCombobox : public UiControl {
	public:
		UiEditableCombobox();
		DEFINE_CONTROL_METHODS()
		void append(const char *text);
		const char * getText();
		void setText(const char *text);

};



class UiEntryBase : public UiControl {
	private:
		nbind::cbFunction * onChangeCallback = NULL;

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
		void setText(const char * text);
		const char * getText();
};


class UiGroup : public UiControl {
	public:
		UiGroup(const char *text);
		void setChild(UiControl *control);
		int getMargined();
		void setMargined(int margined);
		const char * getTitle();
		void setTitle(const char * title);
		DEFINE_CONTROL_METHODS()
};


class UiButton : public UiControl {
	public:
		UiButton(const char *text);
		DEFINE_CONTROL_METHODS()
		void setText(const char * text);
		const char * getText();
};


class UiCheckbox : public UiControl {
	public:
		UiCheckbox(const char *text);
		DEFINE_CONTROL_METHODS()
		void setText(const char * text);
		const char * getText();
		void setChecked(int checked);
		int getChecked();
};


class UiProgressBar : public UiControl {
	public:
		UiProgressBar();
		DEFINE_CONTROL_METHODS()

		void setValue(int value);
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

/*
class UiMenu {
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



_UI_EXTERN void uiMenuItemEnable(uiMenuItem *m);
_UI_EXTERN void uiMenuItemDisable(uiMenuItem *m);
_UI_EXTERN void uiMenuItemOnClicked(uiMenuItem *m, void (*f)(uiMenuItem *sender, uiWindow *window, void *data), void *data);
_UI_EXTERN int uiMenuItemChecked(uiMenuItem *m);
_UI_EXTERN void uiMenuItemSetChecked(uiMenuItem *m, int checked);

typedef struct uiMenu uiMenu;
#define uiMenu(this) ((uiMenu *) (this))
_UI_EXTERN uiMenuItem *uiMenuAppendItem(uiMenu *m, const char *name);
_UI_EXTERN uiMenuItem *uiMenuAppendCheckItem(uiMenu *m, const char *name);
_UI_EXTERN uiMenuItem *uiMenuAppendQuitItem(uiMenu *m);
_UI_EXTERN uiMenuItem *uiMenuAppendPreferencesItem(uiMenu *m);
_UI_EXTERN uiMenuItem *uiMenuAppendAboutItem(uiMenu *m);
_UI_EXTERN void uiMenuAppendSeparator(uiMenu *m);
_UI_EXTERN uiMenu *uiNewMenu(const char *name);
*/

#endif
