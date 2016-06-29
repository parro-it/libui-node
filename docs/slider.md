
# Slider

> Horizontal slide to set numerical values.

```js

var libui = require('libui');

libui.Ui.init();
var win = new libui.UiWindow('UiSlider example', 640, 480, true);

var widget = new libui.UiSlider();
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

> new libui.UiSlider()

Create a new UiSlider object.

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



## value: Number

The current numeric value of the slider.
Read write.




---

# Methods



---

# Events

See [events implementation](events.md) for generic details on how events are implemented.


## onChanged

Emitted whenever property value change.



