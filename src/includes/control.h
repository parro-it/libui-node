#ifndef UI_NODE_CONTROL
#define UI_NODE_CONTROL 1

#include <map>
#include "ui.h"

#define DEFINE_EVENT(NAME)                                                     \
  private:                                                                     \
	nbind::cbFunction *NAME##Callback = NULL;                                  \
                                                                               \
  public:                                                                      \
	void NAME(nbind::cbFunction &cb);

#define IMPLEMENT_EVENT(CLASS, WIDGET, NAME, LIBUI_FUN)                        \
	static void CLASS##_##NAME(WIDGET *w, void *data) {                        \
		nbind::cbFunction *cb = (nbind::cbFunction *)data;                     \
		(*cb)();                                                               \
	}                                                                          \
	void CLASS::NAME(nbind::cbFunction &cb) {                                  \
		NAME##Callback = new nbind::cbFunction(cb);                            \
		LIBUI_FUN((WIDGET *)getHandle(), CLASS##_##NAME, NAME##Callback);      \
	}

#define DISPOSE_EVENT(NAME)                                                    \
	/*if (NAME##Callback != nullptr) {                                         \
		delete NAME##Callback;                                                 \
		NAME##Callback = nullptr;                                              \
	}*/

typedef void (*DestroyCb)(uiControl *);

class UiControl {
  private:
	uiControl *handle;

  public:
	DestroyCb originalDestroy;
	bool destroyed;
	virtual void onDestroy(uiControl *);

	uiControl *getHandle();
	UiControl(uiControl *hnd);
	virtual ~UiControl();
	void destroy();
	void setParent(UiControl *parent);
	bool toplevel();
	bool getVisible();
	void setVisible(bool visible);
	bool getEnabled();
	void setEnabled(bool enabled);
};

extern std::map<uiControl *, UiControl *> controlsMap;

// This is included at end of file
// to minimize conflicts with existing
// symbols from other headers.
#include "nbind/nbind.h"

#endif
