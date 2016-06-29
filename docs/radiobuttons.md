
# RadioButtons

> A widget that represent a group of radio options.



```js

var libui = require('libui');

libui.Ui.init();
var win = new libui.UiWindow('UiRadioButtons example', 640, 480, true);

var widget = new libui.UiRadioButtons();
win.setChild(widget);

win.onClosing(function () {
	win.close();
	libui.stopLoop();
});

win.show();

libui.startLoop();

```

---

# Constructor

> new libui.UiRadioButtons()

Create a new UiRadioButtons object.

---

# Properties

See [properties implementation](properties.md) for generic details on how properties are implemented.


### visible: Boolean

Whether the widget should be visible or hidden. 
Read write.
Defaults to `true`.



### enabled: Boolean

Whether the widget should be enabled or disabled. 
Read write.
Defaults to `true`.



### selected: Number

Return or set the current choosed option by index.




---

# Methods



---

# Events

See [events implementation](events.md) for generic details on how events are implemented.


### onSelected

Emitted whenever property `selected` change.



