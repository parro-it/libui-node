#ifndef ui_node_evetn_loop_linux
#define ui_node_evetn_loop_linux 1

#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <poll.h>
#include <sys/epoll.h>
#include <uv.h>

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
