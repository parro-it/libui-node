#import <Cocoa/Cocoa.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
void noop(void* data) {}

int uiLoopWakeup() {
  dispatch_async(dispatch_get_main_queue(), ^{
                     // NSLog(@"Got to main thread.");
                 });
  return 0;
}

int uiEventsPending() {
  NSEvent* event = [NSApp nextEventMatchingMask:NSAnyEventMask
                                      untilDate:[NSDate distantPast]
                                         inMode:NSDefaultRunLoopMode
                                        dequeue:YES];
  [NSApp sendEvent:event];
  return nil != event;
}

int waitForNodeEvents(int nodeBackendFd, int timeout) {
  struct kevent event;
  struct timespec ts;
  ts.tv_sec = timeout / 1000;
  ts.tv_nsec = (timeout % 1000) * 1000000;
  return kevent(nodeBackendFd, NULL, 0, &event, 1, &ts);
}
