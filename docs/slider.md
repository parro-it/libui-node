
# Slider

> Horizontal slide to set numerical values.

```js

var libui = require('libui');

libui.Ui.init();
var win = new libui.UiWindow('UiSlider example', 320, 60, true);
win.margined = true;

var widget = new libui.UiSlider();
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

> new libui.UiSlider()

Create a new UiSlider object.

