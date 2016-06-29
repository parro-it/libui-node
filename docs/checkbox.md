
# Checkbox

> A checkbox widget.

```js

var libui = require('libui');

libui.Ui.init();
var win = new libui.UiWindow('UiCheckbox example', 320, 60, true);
win.margined = true;

var widget = new libui.UiCheckbox();
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

> new libui.UiCheckbox()

Create a new UiCheckbox object.

