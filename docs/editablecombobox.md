
# EditableCombobox

> A drop down combo box that allow selection from list or free text entry.

```js

var libui = require('libui');

libui.Ui.init();
var win = new libui.UiWindow('UiEditableCombobox example', 320, 60, true);
win.margined = true;

var widget = new libui.UiEditableCombobox();
widget.text = 'sample text';
win.setChild(widget);

win.onClosing(function () {
	win.close();
	libui.Ui.quit();
});

win.show();

libui.Ui.main();


```

---

# Constructor

> new libui.UiEditableCombobox()

Create a new UiEditableCombobox object.

