
# Combobox

> A drop down combo box that allow list selection only.

```js

var libui = require('libui');

libui.Ui.init();
var win = new libui.UiWindow('UiCombobox example', 640, 480, true);

var widget = new libui.UiCombobox();
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

> new libui.UiCombobox()

Create a new UiCombobox object.

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



## selected: Number

Return or set the current selected item by index.




---

# Methods



---

# Events

See [events implementation](events.md) for generic details on how events are implemented.


## onSelected

Emitted whenever property selected change.



