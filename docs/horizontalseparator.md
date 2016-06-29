
# HorizontalSeparator

> An horizontal line to visually separate widgets.

```js

var libui = require('libui');

libui.Ui.init();
var win = new libui.UiWindow('UiHorizontalSeparator example', 320, 60, true);
win.margined = true;

var widget = new libui.UiHorizontalSeparator();
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

> new libui.UiHorizontalSeparator()

Create a new UiHorizontalSeparator object.

