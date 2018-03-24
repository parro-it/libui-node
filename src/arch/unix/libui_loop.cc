#include "../../includes/event-loop-linux.h"

int uiLoopWakeup() {
  // printf("uiLoopWakeup\n");
  g_main_context_wakeup(NULL);
  // printf("uiLoopWakeup exit\n");
  return 0;
}

int uiEventsPending() {
  // printf("uiEventsPending\n");
  return gtk_events_pending();
}

int waitForNodeEvents(uv_loop_t* loop, int timeout) {
  // printf("uv_backend_fd\n");
  int nodeBackendFd = uv_backend_fd(loop);
  // printf("uv_backend_fd %d\n", nodeBackendFd);

  if (nodeBackendFd == -1) {
    fprintf(stderr, "Invalid node backend fd.\n");
    return 0;
  }

  struct epoll_event ev;
  // printf("epoll_wait\n");

  int ret = epoll_wait(nodeBackendFd, &ev, 1, timeout);
  struct heap_node* node = ((struct heap*)&loop->timer_heap)->min;
  if (node != NULL) {
    return 1;
  }

  // printf("epoll_wait %d\n", ret);
  return ret;
}
