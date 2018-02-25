#include <Windows.h>
#include <uv.h>
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
