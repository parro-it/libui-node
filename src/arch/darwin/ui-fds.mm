#include <uv.h>
#include <mach/port.h> /* mach_port_t */
#include <mach/mach.h> /* mach_port_allocate(), mach_task_self(), mach_port_insert_member(), MACH_PORT_RIGHT_PORT_SET */
#include <sys/event.h> /* kqueue(), kevent64(), struct kevent64_s, EVFILT_MACHPORT, EV_SET64, EV_ADD */
#include <sys/time.h> /* struct timespec */

#include <stdio.h>
#include <errno.h>
#include <unistd.h> /* close() */
#include <dispatch/dispatch.h>

extern "C" mach_port_t _dispatch_get_main_queue_port_4CF(void);
extern "C" void _dispatch_main_queue_callback_4CF(void);

int uiConnectionNumber() {
	int fd;
	struct kevent64_s event;
	struct timespec t = (struct timespec){0,0};

	if (-1 == (fd = kqueue()))
		return (perror("kqueue"), 1);
	/* TODO: set cloexec */

	mach_port_t x = _dispatch_get_main_queue_port_4CF();
	printf("PORT 4CF=%d\n", x);

	/* EVFILT_MACHPORT does not allow ports; only portsets */
	mach_port_t y;
	if (KERN_SUCCESS != mach_port_allocate(mach_task_self(), MACH_PORT_RIGHT_PORT_SET, &y))
		return 1;

	printf("PORT SET=%d\n", y);

	EV_SET64(&event, y, EVFILT_MACHPORT, EV_ADD|EV_CLEAR, MACH_RCV_MSG, 0, 0, 0, 0);
	if (0 != kevent64(fd, &event, 1, NULL, 0, 0, &t))
		return (perror("kevent"), 1);

	/* XXX: a port can only belong to one portset at once. this needs additional hackery when in a CF-using application */
	if (KERN_SUCCESS != mach_port_insert_member(mach_task_self(), x, y))
		return 1;



	return fd;

}

int uiEventsPending() {
	printf("uiEventsPending\n");
	return FALSE;
}

