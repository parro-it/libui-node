
# MultilineEntry

> A multiline text entry widget.

![UiMultilineEntry example](media/UiMultilineEntry.png)

```js

var libui = require('libui');

libui.Ui.init();
var win = new libui.UiWindow('UiMultilineEntry example', 640, 480, true);

var widget = new libui.UiMultilineEntry();
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

> new libui.UiMultilineEntry()

Create a new UiMultilineEntry object.

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

The current text of the multiline entry.
Read write.




---

# Methods


## append

Append specified text to the entry content.


### Arguments

* text: String - the text to append.




## destroy

Destroy and free the control.





## setParent

Change the parent of the control


### Arguments

* parent: UiControl - the new parent of the widget or null to detach it.




## toplevel

Return whether the control is a top level one or not.





---

# Events

See [events implementation](events.md) for generic details on how events are implemented.


### onChanged

Emitted whenever property `text` change.




