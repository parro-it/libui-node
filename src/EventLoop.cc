
#include <uv.h>
#include "../../../ui.h"
#include "nbind/nbind.h"

bool running = false;

extern int uiEventsPending();
extern int uiLoopWakeup();
extern int waitForNodeEvents(uv_loop_t* loop, int timeout);

uv_thread_t* thread;

static void signalNodeActivity(void* arg) {
  int r = 0;
  int timeout;
  // printf("signalNodeActivity\n");

  while (running) {
    // printf("signalNodeActivity check\n");

    timeout = uv_backend_timeout(uv_default_loop());

    if (timeout == 0) {
      timeout = 1000;
    }

    do {
      r = waitForNodeEvents(uv_default_loop(), timeout);
    } while (r == -1 && errno == EINTR);

    if (r > 0) {
      uiLoopWakeup();
    }
  }
}

// static int idx = 0;
void redraw(uv_timer_t* handle) {
  uv_timer_stop(handle);
  // printf("redraw %d\n", idx++);
  Nan::HandleScope scope;

  uiMainStep(true);
  while (uiEventsPending()) {
    // printf("pending %d\n", idx++);

    running = uiMainStep(false);
  }
  uv_timer_start(handle, redraw, 16, 1000000);
}

struct EventLoop {
  static void start() {
    if (running) {
      return;
    }

    running = true;
    uiMainSteps();

    thread = new uv_thread_t();
    uv_thread_create(thread, signalNodeActivity, NULL);

    uv_timer_t* handle = (uv_timer_t*)malloc(sizeof(uv_timer_t));
    uv_timer_init(uv_default_loop(), handle);
    uv_timer_start(handle, redraw, 16, 1000000);
  }

  static void stop() {
    if (!running) {
      return;
    }
    running = false;

    uiQuit();
    /*uv_thread_join(thread);
    delete thread;*/
  }
};

NBIND_CLASS(EventLoop) {
  method(start);
  method(stop);
}
