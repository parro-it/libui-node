
# Entry

> A simple, single line text entry widget.

![UiEntry example](media/UiEntry.png)

```js

var libui = require('libui');

libui.Ui.init();
var win = new libui.UiWindow('UiEntry example', 640, 480, true);

var widget = new libui.UiEntry();
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

> new libui.UiEntry()

Create a new UiEntry object.

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



### readOnly: Boolean

Whether the user is allowed to change the entry text. 
Read write.
Defaults to `true`.



### text: String

The current text of the entry.
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



## setReadOnly

Set the value of property `readOnly`

**Arguments**

* value: Boolean - The new value for `readOnly` property.

## getReadOnly

Return the value of property `readOnly`



## setText

Set the value of property `text`

**Arguments**

* value: String - The new value for `text` property.

## getText

Return the value of property `text`



---

# Events

See [events implementation](events.md) for generic details on how events are implemented.


### onChanged

Emitted whenever property `text` change.




