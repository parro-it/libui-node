#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <X11/Xlib.h>
#include "nbind/nbind.h"
#include <uv.h>
#include "../../../ui.h"

uv_poll_t * handle;

int uiConnectionNumber() {
	GdkDisplay *gd = gdk_display_get_default();
	Display *d = gdk_x11_display_get_xdisplay(gd);
	int fd = ConnectionNumber(d);
	return fd;
}

int uiEventsPending() {
	return gtk_events_pending();
}


static void onEventsPending(uv_poll_t* handle, int status, int events) {
	printf ("onEventsPending\n");

	Nan::HandleScope scope;
	while(uiEventsPending()) {
		uiMainStep(0);
	}

}

bool running = false;

struct EventLoop {
	static void start () {
		if (running) {
			return;
		}
		running = true;
		uiMainSteps();

		int fd = uiConnectionNumber();
		handle = new uv_poll_t();

		uv_poll_init(uv_default_loop(), handle, fd);

		uv_poll_start(handle, UV_WRITABLE, onEventsPending);
		printf("uv_poll_start done.\n");

	}

	static void stop () {
		if (!running) {
			return;
		}
		running = false;
		uiQuit();
		uv_poll_stop(handle);
	}
};


NBIND_CLASS(EventLoop) {
		method(start);
		method(stop);
}
