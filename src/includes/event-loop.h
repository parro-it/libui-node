#ifndef ui_node_event_loop
#define ui_node_event_loop 1

#include <uv.h>
#include <atomic>
#include "../../ui.h"
#include "nbind/nbind.h"

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
int waitForNodeEvents(uv_loop_t* loop, int timeout);


/*
        Internal libuv structures
        to deal with timers on macOS
        and linux.
 */

struct heap_node {
  struct heap_node* left;
  struct heap_node* right;
  struct heap_node* parent;
};

struct heap {
  struct heap_node* min;
  unsigned int nelts;
};

#endif
