#include "nbind/nbind.h"
#include <X11/Xlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <uv.h>
#include "../ui.h"


void onEventsPending(uv_poll_t* handle, int status, int events) {
	// printf("status %d, events %d\n", status, events);
	Nan::HandleScope scope;
	while(gtk_events_pending()) {
		gtk_main_iteration_do(FALSE);
	}
}


struct EventLoop {
	static void start () {


		GdkDisplay *pDisplay;
		Display *xDisplay;

		int fd;

		uiMainSteps();

		pDisplay = gdk_display_get_default();
		xDisplay = (Display *) gdk_x11_display_get_xdisplay(pDisplay);
		fd = ConnectionNumber(xDisplay);


		uv_poll_t * handle = new uv_poll_t();

		uv_poll_init(uv_default_loop(), handle, fd);
		uv_poll_start(handle, UV_READABLE, onEventsPending);

	}
};


NBIND_CLASS(EventLoop) {
	method(start);
}
