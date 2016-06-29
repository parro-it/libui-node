# Libui initialization

`libui` must be initialized to be able to create any GUI control.
This can be done by calling the `init` method:

```js
var libui = require('libui');

libui.Ui.init();
```

After initialization, you can freely create any number of windows or control objects. Next steo is to start the `libui` event loop that allow the library to process GUI events.


# `libui` event loop



## Start the event loop

To start the event loop, you simply call the `startLoop` method. The function return immediately, and optionally accept a callback arguments that is called when `libui` event loop terminates.


```js
var libui = require('libui');

libui.Ui.init();

libui.startLoop(function () {
	console.log('event loop terminated.');
});
```

## Stop the event loop

To stop the event loop, you simply call the `stopLoop` method. The function return immediately.


```js
var libui = require('libui');

libui.Ui.init();

libui.startLoop(function () {
	console.log('event loop terminated.');
});

libui.stopLoop();
```

## Main method
