#include <Windows.h>
#include "../../../ui.h"
#include "nbind/nbind.h"

void noop(void* data) {}

int uiLoopWakeup() {
  uiQueueMain(noop, NULL);
  return 0;
}

int uiEventsPending() {
  MSG msg;
  return PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);
}

int waitForNodeEvents(int nodeBackendFd, int timeout) {
  FD_SET readSet;
  FD_ZERO(&readSet);
  FD_SET(nodeBackendFd, &readSet);

  struct timeval timeout_s;
  timeout_s.tv_sec = timeout / 1000;
  timeout_s.tv_usec = (timeout % 1000) * 1000;

  int res;
  if ((res = select(0, &readSet, NULL, NULL, timeout_s)) == SOCKET_ERROR) {
    perror("select() returned with error %d\n", WSAGetLastError());
    return 0;
  }

  return FD_ISSET(nodeBackendFd, &readSet);
}
