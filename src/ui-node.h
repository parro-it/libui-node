// A2DD.h
#ifndef ui_node
#define ui_node

class UiControl {
	private:
		uiControl *handle;

	public:
		uiControl * getHandle();
		UiControl(uiControl *hnd);
		void destroy();
		void setParent (UiControl *parent);
		int toplevel();
		int getVisible();
		void setVisible(int visible);
		int getEnabled();
		void setEnabled(int enabled);

};




class UiEntry : public UiControl {
	public:
		UiEntry();
		void destroy();
		void setParent (UiControl *parent);
		int toplevel();
		int getVisible();
		void setVisible(int visible);
		int getEnabled();
		void setEnabled(int enabled);
};

class UiBox : public UiControl {
	public:
		UiBox();
		void append(UiControl *control, int stretchy);

		void destroy();
		void setParent (UiControl *parent);
		int toplevel();
		int getVisible();
		void setVisible(int visible);
		int getEnabled();
		void setEnabled(int enabled);
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
