# Event loop

`libui-node` runs an event loop independent of that of Node.js that takes care of processing GUI events. This event loop can run seamlessy together with the Node.js one, so you can still use any asynchronous Node.js function.

You are responsible to start and stop the loop, by calling the `startLoop` and `stopLoop` functions.

`startLoop` returns immediately after it started the event loop. It keeps
a Node.js handle active, so it prevents your process to terminate, until
you call `stopLoop` later.

# Quit handler

The `onShouldQuit` function allows you to register a callback that is called when a "Quit" menu item is clicked. You are responsible to terminate the application in response to this event, usually by calling `stopLoop` method.

# Example

```js
const {
	UiWindow,
	UiMenu,
	startLoop,
	stopLoop,
	onShouldQuit
} = require('libui');


const menu = new UiMenu('File');
menu.appendQuitItem();

const window = UiWindow('Initialization Example', 400, 300, true);

onShouldQuit(() => {
	window.close();
	stopLoop();
});

window.show();
startLoop();
```
