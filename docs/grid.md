
# Grid

> A powerful container that allow to specify size and position of each children.



```js

var libui = require('libui');

libui.Ui.init();
var win = new libui.UiWindow('UiGrid example', 640, 480, true);

var widget = new libui.UiGrid();
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

> new libui.UiGrid()

Create a new UiGrid object.

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



### padded: Boolean

If true, the container insert some space between widgets. 
Defaults to false.




---

# Methods



---

# Events

See [events implementation](events.md) for generic details on how events are implemented.



