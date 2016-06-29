
# Form

> A container that organize children as labeled fields.

```js

var libui = require('libui');

libui.Ui.init();
var win = new libui.UiWindow('UiForm example', 320, 60, true);
win.margined = true;

var widget = new libui.UiForm();
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

> new libui.UiForm()

Create a new UiForm object.

