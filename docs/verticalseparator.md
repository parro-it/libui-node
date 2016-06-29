
# VerticalSeparator

> A vertical line to visually separate widgets.

```js

var libui = require('libui');

libui.Ui.init();
var win = new libui.UiWindow('UiVerticalSeparator example', 320, 60, true);
win.margined = true;

var widget = new libui.UiVerticalSeparator();
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

> new libui.UiVerticalSeparator()

Create a new UiVerticalSeparator object.

