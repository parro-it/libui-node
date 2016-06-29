
# Combobox

> A drop down combo box that allow list selection only.

```js

var libui = require('libui');

libui.Ui.init();
var win = new libui.UiWindow('UiCombobox example', 320, 60, true);
win.margined = true;

var widget = new libui.UiCombobox();
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

> new libui.UiCombobox()

Create a new UiCombobox object.

