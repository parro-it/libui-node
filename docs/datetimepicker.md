
# DateTimePicker

> A widgets to edit date/times.

```js

var libui = require('libui');

libui.Ui.init();
var win = new libui.UiWindow('UiDateTimePicker example', 320, 60, true);
win.margined = true;

var widget = new libui.UiDateTimePicker();
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

> new libui.UiDateTimePicker()

Create a new UiDateTimePicker object.

