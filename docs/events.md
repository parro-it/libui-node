# libui-node widgets events

Many widgets have events that are raised when their properties changed, because user interacts with GUI or because programmer has invoked a property setter.

All events are methods that accepts a single callback that receive 0 arguments.

```js
var widget = new libui.UiEntry();

widget.onChanged(function() {
	console.log(widget.text);
});

// set the text contained in the entry
widget.text = 'sample text';
```

Widgets don't keep an internal list of event listener. If you register more that one callbacks, previous one are lost and never get called. This is implemented directly in `libui`, maybe we implement `Node.js` style event emitter in a future release.

