# Libui-node initialization

`libui-node` must be initialized to be able to create any GUI control.
This can be done by calling the `init` method:

```js
var libui = require('libui');

libui.Ui.init();
```

After initialization, you can freely create windows or control objects.


# Event loop

`libui-node` has an event loop independent  of the Node.js one that take care of processing GUI events. It process events one tick at a time, so it can run seamlessy with Node.js loop.

Each bit of GUI event loop is executed by a call to `libui.Ui.mainStep` method. This method could be used directly by your code, or you can leverage the `startLoop` event that continuosly schedules calls to `mainStep` using Node.js `setImmediate` function.



## Start the event loop

To start the event loop, you simply call the `startLoop` method. The function return immediately, and optionally accept a callback arguments that is called when `libui-node` event loop terminates.


```js
libui.startLoop(function () {
	console.log('event loop terminated.');
});
```

## Stop the event loop

To stop the event loop, you simply call the `stopLoop` method. The function return immediately.

```js
libui.stopLoop();
```

## Main method

The `main` method is an alternative way to start GUI event loop. It defers event loop execution to the underlyng native GUI framework.

This is a blocking call, so Node.js event loop is stopped until `libui-node` event loop terminate.
This mean that your GUI events callbacks are executed because they are called by the native GUI event loop, but Node.js callbacks doesn't.

To stop the loop and allow `main` method to return, you have to call `libui.Ui.quit` method.






