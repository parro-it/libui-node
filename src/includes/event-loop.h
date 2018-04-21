#ifndef ui_node_event_loop
#define ui_node_event_loop 1

#include <atomic>
#include <uv.h>
#include "nbind/nbind.h"
#include "ui.h"

// #define UI_NODE_DEBUG 1

#ifdef UI_NODE_DEBUG
#define DEBUG(msg) fprintf(stderr, msg)
#define DEBUG_F(msg, ...) fprintf(stderr, msg, __VA_ARGS__)
#else
#define DEBUG(msg) ;
#define DEBUG_F(msg, ...) ;
#endif

int uiEventsPending();
int uiLoopWakeup();
int waitForNodeEvents(uv_loop_t *loop, int timeout);

#endif
