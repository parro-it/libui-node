
#include <uv.h>
#include "../../../ui.h"
#include "nbind/nbind.h"

extern int uiEventsPending();
extern int uiLoopWakeup();
extern int waitForNodeEvents(uv_loop_t* loop, int timeout);

static std::atomic<bool> running;
static uv_thread_t* thread;
static uv_timer_t* redrawTimer;
/*
   This function is executed in the
   background thread and is responsible to continuosly polling
   the node backend for pending events.

   When pending node events are found, the native GUI
   event loop is wake up by calling uiLoopWakeup().
*/
static void backgroundNodeEventsPoller(void* arg) {
  while (running) {
    /* query node for the desired timout */
    int timeout = uv_backend_timeout(uv_default_loop());

    /* if timeout is 0, wait for 1s by default */
    if (timeout == 0) {
      timeout = 1000;
    }

    int pendingEvents;

    /* wait for pending */
    do {
      pendingEvents = waitForNodeEvents(uv_default_loop(), timeout);
    } while (pendingEvents == -1 && errno == EINTR);

    if (pendingEvents > 0) {
      uiLoopWakeup();
    }
  }
}

/*
    This function run all pending native GUI event in the loop
    using libui calls.

    It first do a blocking call to uiMainStep that
    wait for pending GUI events.
    The function also exit when there are pending node
    events, because uiLoopWakeup function posts a GUI event
    from the background thread for this purpose.
 */
void redraw(uv_timer_t* handle) {
  if (!running) {
    return;
  }
  uv_timer_stop(handle);
  Nan::HandleScope scope;

  /* Blocking call that wait for a node or GUI event pending */
  uiMainStep(true);

  /* dequeue and run every event pending */
  while (uiEventsPending()) {
    running = uiMainStep(false);
  }

  /* schedule another call to redraw as soon as possible */
  uv_timer_start(handle, redraw, 1, 0);
}
static void init() {
  uiInitOptions o;
  memset(&o, 0, sizeof(uiInitOptions));
  const char* err = uiInit(&o);
  if (err != NULL) {
    NBIND_ERR(err);
    uiFreeInitError(err);
  }
}

struct EventLoop {
  /* This function start the event loop and exit immediately */
  static void start() {
    /* if the loop is already running, this is a noop */
    if (running) {
      return;
    }

    init();

    running = true;
    /* init libui event loop */
    uiMainSteps();

    /* start the background thread that check for node evnts pending */
    thread = new uv_thread_t();
    uv_thread_create(thread, backgroundNodeEventsPoller, NULL);

    /* start redraw timer */
    redrawTimer = (uv_timer_t*)malloc(sizeof(uv_timer_t));
    uv_timer_init(uv_default_loop(), redrawTimer);
    redraw(redrawTimer);
  }

  /* This function start the event loop and exit immediately */
  static void stop() {
    /* if the loop is already running, this is a noop */
    if (!running) {
      return;
    }
    running = false;
    printf("stopping\n");

    /* stop redraw handler */
    uv_timer_stop(redrawTimer);
    uv_close((uv_handle_t*)redrawTimer, NULL);
    printf("timer end.\n");

    /* await for the background thread to finish */
    uv_thread_join(thread);
    // uv_close((uv_handle_t*)thread, NULL);

    printf("background thread end.\n");

    /* quit libui event loop */
    uiQuit();
    printf("ui loop quit.\n");
  }
};

NBIND_CLASS(EventLoop) {
  method(start);
  method(stop);
}
