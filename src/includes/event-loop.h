#ifndef ui_node_evetn_loop
#define ui_node_evetn_loop 1

#include <unistd.h>
#include <uv.h>
#include <atomic>
#include "../../ui.h"
#include "nbind/nbind.h"

int uiEventsPending();
int uiLoopWakeup();
int waitForNodeEvents(uv_loop_t* loop, int timeout);

#endif
