
# ColorButton

> A button that open a color palette popup.

```js

var libui = require('libui');

libui.Ui.init();
var win = new libui.UiWindow('UiColorButton example', 640, 480, true);

var widget = new libui.UiColorButton();
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

> new libui.UiColorButton()

Create a new UiColorButton object.

---

# Properties

See [properties implementation](properties.md) for generic details on how properties are implemented.


## color: Color

Return or set the currently selected color




---

# Methods



---

# Events

See [events implementation](events.md) for generic details on how events are implemented.


## onChanged

Emitted whenever property color change.



