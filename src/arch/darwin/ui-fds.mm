#import <Cocoa/Cocoa.h>
#include <uv.h>
#include <mach/mach.h>
#import <CoreFoundation/CoreFoundation.h>
#include <mach/mach.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/select.h>
#include <poll.h>
#include <errno.h>

extern "C" mach_port_t _dispatch_get_main_queue_port_4CF(void);
void noop(void) {

}

int uiConnectionNumber() {
	mach_port_name_t port = _dispatch_get_main_queue_port_4CF();
	printf ("mach port: %d\n", port);
	int kq;
	struct kevent * evSet = new struct kevent();
	// struct kevent * list = new struct kevent();
	struct timespec t = {0, 0};
	kq = kqueue();

	EV_SET(evSet, port, EVFILT_MACHPORT | EVFILT_READ, 0, MACH_RCV_MSG, 0, NULL);
	int status;
	if ((status = kevent(kq, evSet, 1, evSet, 1, &t)) == -1)
		printf("error %d\n", errno);
	printf ("kevent %d\n", status);
	return kq;
}

int uiEventsPending() {
	return TRUE;
}

