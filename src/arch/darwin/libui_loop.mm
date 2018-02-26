#import <Cocoa/Cocoa.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <uv.h>
void noop(void* data) {}

int uiLoopWakeup() {
  dispatch_async(dispatch_get_main_queue(), ^{
                 });
  return 0;
}

int uiEventsPending() {
  NSEvent* event = [NSApp nextEventMatchingMask:NSAnyEventMask
                                      untilDate:[NSDate distantPast]
                                         inMode:NSDefaultRunLoopMode
                                        dequeue:NO];
  return nil != event;
}

int waitForNodeEvents(uv_loop_t* loop, int timeout) {
  int nodeBackendFd = uv_backend_fd(loop);
  if (nodeBackendFd == -1) {
    fprintf(stderr, "Invalid node backend fd.\n");
    return 0;
  }

  struct kevent event;
  struct timespec ts;
  ts.tv_sec = timeout / 1000;
  ts.tv_nsec = (timeout % 1000) * 1000000;
  return kevent(nodeBackendFd, NULL, 0, &event, 1, &ts);
}
