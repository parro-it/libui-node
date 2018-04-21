#include "event-loop-windows.h"
#include "event-loop.h"

void noop(void *data) {}

int uiLoopWakeup() {
	uiQueueMain(noop, NULL);
	// give main thread some time to react
	return 0;
}

int uiEventsPending() {
	MSG msg;
	return PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);
}

int waitForNodeEvents(uv_loop_t *loop, int timeout) {
	DWORD bytes;
	ULONG_PTR key;
	OVERLAPPED *overlapped;

	struct _internal_uv_loop_s *_loop = (_internal_uv_loop_s *)loop;

	if (timeout == -1) {
		timeout = INFINITE;
	}

	int ret = GetQueuedCompletionStatus(_loop->iocp, &bytes, &key, &overlapped,
										timeout);

	// Does we need to requeue the queued completions?
	// this happen to be same code used by Electron
	// on Windows:
	// https://github.com/electron/electron/blob/master/atom/common/node_bindings_win.cc#L24
	// but the application become unstable when this
	// part is uncommented.
	// See laso this PRs on libuv repo:
	// https://github.com/libuv/libuv/pull/1007
	// https://github.com/libuv/libuv/pull/1544
	// https://github.com/libuv/libuv/pull/1651
	if (overlapped != NULL) {
		DEBUG("node event!\n");
		PostQueuedCompletionStatus(_loop->iocp, bytes, key, overlapped);
	}

	return ret;
}
