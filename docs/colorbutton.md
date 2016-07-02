
# ColorButton

> A button that open a color palette popup.

![UiColorButton example](media/UiColorButton.png)

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


### color: Color

Return or set the currently selected color




---

# Methods


## destroy

Destroy and free the control.




## setParent

Change the parent of the control


**Arguments**

* parent: UiControl - the new parent of the widget or null to detach it.



## toplevel

Return whether the control is a top level one or not.




## setColor

Set the value of property `color`

**Arguments**

* value: Color - The new value for `color` property.

## getColor

Return the value of property `color`



---

# Events

See [events implementation](events.md) for generic details on how events are implemented.


### onChanged

Emitted whenever property `color` change.




