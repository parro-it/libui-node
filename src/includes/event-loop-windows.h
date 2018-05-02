#ifndef ui_node_event_loop_windows
#define ui_node_event_loop_windows 1

#include <stdio.h>

struct _internal_uv_loop_s {
	/* User data - use this for whatever. */
	void *data;
	/* Loop reference counting. */
	unsigned int active_handles;
	void *handle_queue[2];
	void *active_reqs[2];
	/* Internal flag to signal loop stop. */
	unsigned int stop_flag;
	/* The loop's I/O completion port */
	void *iocp;
	/* The current time according to the event loop. in msecs.
	//  uint64_t tim
	// Tail of a single-linked circular queue of pending reqs. If the queue
	// is empty, tail_ is NULL. If there is only one item,
	// tail_->next_req == tail_
	void* pending_reqs_tail;
	// Head of a single-linked list of closed handles
	void* endgame_handles;
	// The head of the timers tree
	struct uv_timer_tree_s timers;
	// Lists of active loop (prepare / check / idle) watchers
	uv_prepare_t* prepare_handles;
	uv_check_t* check_handles;
	uv_idle_t* idle_handles;
	// This pointer will refer to the prepare/check/idle handle whose
	// callback is scheduled to be called next. This is needed to allow
	// safe removal from one of the lists above while that list being
	// iterated over.
	uv_prepare_t* next_prepare_handle;
	uv_check_t* next_check_handle;
	uv_idle_t* next_idle_handle;
	// This handle holds the peer sockets for the fast variant of uv_poll_t
	SOCKET poll_peer_sockets[UV_MSAFD_PROVIDER_COUNT];
	// Counter to keep track of active tcp streams
	unsigned int active_tcp_streams;
	// Counter to keep track of active udp streams
	unsigned int active_udp_streams;
	// Counter to started timer
	uint64_t timer_counter;
	// Threadpool
	void* wq[2];
	uv_mutex_t wq_mutex;
	uv_async_t wq_async;
	*/
};

#endif
