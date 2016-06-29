
# Grid

> A powerful container that allow to specify size and position of each children.

```js

var libui = require('libui');

libui.Ui.init();
var win = new libui.UiWindow('UiGrid example', 320, 60, true);
win.margined = true;

var widget = new libui.UiGrid();
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

> new libui.UiGrid()

Create a new UiGrid object.

