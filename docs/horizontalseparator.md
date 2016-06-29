
# HorizontalSeparator

> An horizontal line to visually separate widgets.

```js

var libui = require('libui');

libui.Ui.init();
var win = new libui.UiWindow('UiHorizontalSeparator example', 640, 480, true);

var widget = new libui.UiHorizontalSeparator();
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

> new libui.UiHorizontalSeparator()

Create a new UiHorizontalSeparator object.

---

# Properties

See [properties implementation](properties.md) for generic details on how properties are implemented.


## visible: Boolean

Whether the widget should be visible or hidden. 
Read write.
Defaults to `true`.



## enabled: Boolean

Whether the widget should be enabled or disabled. 
Read write.
Defaults to `true`.




---

# Methods



---

# Events

See [events implementation](events.md) for generic details on how events are implemented.



