#include "event-loop-linux.h"
#include "event-loop.h"

int uiLoopWakeup() {
	DEBUG("uiLoopWakeup\n");
	g_main_context_wakeup(NULL);
	DEBUG("uiLoopWakeup exit\n");
	return 0;
}

int uiEventsPending() {
	DEBUG("uiEventsPending\n");
	return gtk_events_pending();
}

int waitForNodeEvents(uv_loop_t *loop, int timeout) {
	DEBUG("uv_backend_fd\n");
	int nodeBackendFd = uv_backend_fd(loop);
	DEBUG_F("uv_backend_fd %d\n", nodeBackendFd);

	if (nodeBackendFd == -1) {
		fprintf(stderr, "Invalid node backend fd.\n");
		return 0;
	}

	struct epoll_event ev;
	DEBUG("epoll_wait\n");

	return epoll_wait(nodeBackendFd, &ev, 1, timeout);
}
