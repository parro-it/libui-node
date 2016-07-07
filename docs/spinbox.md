
# Spinbox

> An entry widget for numerical values.

![UiSpinbox example](media/UiSpinbox.png)

```js

var libui = require('libui');

libui.Ui.init();
var win = new libui.UiWindow('UiSpinbox example', 640, 480, true);

var widget = new libui.UiSpinbox();
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

> new libui.UiSpinbox()

Create a new UiSpinbox object.

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



### value: Number

The current numeric value of the spinbox.
Read write.




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




## setVisible

Set the value of property `visible`

**Arguments**

* value: Boolean - The new value for `visible` property.

## getVisible

Return the value of property `visible`



## setEnabled

Set the value of property `enabled`

**Arguments**

* value: Boolean - The new value for `enabled` property.

## getEnabled

Return the value of property `enabled`



## setValue

Set the value of property `value`

**Arguments**

* value: Number - The new value for `value` property.

## getValue

Return the value of property `value`



---

# Events

See [events implementation](events.md) for generic details on how events are implemented.


### onChanged

Emitted whenever property `value` change.




