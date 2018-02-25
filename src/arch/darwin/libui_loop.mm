#import <Cocoa/Cocoa.h>
#include <unistd.h>
#include <uv.h>
#include "../../../ui.h"
#include "nbind/nbind.h"

void noop(void* data) {}

int uiLoopWakeup() {
  dispatch_async(dispatch_get_main_queue(), ^{
    NSLog(@"Got to main thread.");
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
