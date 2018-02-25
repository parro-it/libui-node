#include <gdk/gdk.h>
#include <gtk/gtk.h>

#include <poll.h>
#include <sys/epoll.h>

int uiLoopWakeup() {
  g_main_context_wakeup(NULL);
  return 0;
}

int uiEventsPending() {
  return gtk_events_pending();
}

int waitForNodeEvents(int nodeBackendFd, int timeout) {
  struct epoll_event ev;
  return epoll_wait(fd, &ev, 1, timeout);
}
