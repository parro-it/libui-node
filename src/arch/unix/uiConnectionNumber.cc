#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <X11/Xlib.h>

int uiConnectionNumber() {
	GdkDisplay *gd = gdk_display_get_default();
	Display *d = gdk_x11_display_get_xdisplay(gd);
	int fd = ConnectionNumber(d);
	return fd;
}

int uiEventsPending() {
	return gtk_events_pending();
}
