#include "../../includes/event-loop-linux.h"
#include "../../includes/event-loop.h"

int uiLoopWakeup() {
  DEBUG("uiLoopWakeup\n");
  g_main_context_wakeup(NULL);
  DEBUG("uiLoopWakeup exit\n");
  // give main thread some time to react
  usleep(50 * 1000);
  return 0;
}

int uiEventsPending() {
  DEBUG("uiEventsPending\n");
  return gtk_events_pending();
}

int waitForNodeEvents(uv_loop_t* loop, int timeout) {
  DEBUG("uv_backend_fd\n");
  int nodeBackendFd = uv_backend_fd(loop);
  DEBUG_F("uv_backend_fd %d\n", nodeBackendFd);

  if (nodeBackendFd == -1) {
    fprintf(stderr, "Invalid node backend fd.\n");
    return 0;
  }

  struct epoll_event ev;
  DEBUG("epoll_wait\n");

  int ret = epoll_wait(nodeBackendFd, &ev, 1, timeout);
  struct heap* timer_heap = (struct heap*)&loop->timer_heap;
  struct heap_node* timer_node = timer_heap->min;
  if (timer_node != NULL) {
    return 1;
  }

  DEBUG_F("epoll_wait %d\n", ret);
  return ret;
}
