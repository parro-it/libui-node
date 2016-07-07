
var libui = require('../../index');

libui.Ui.init();
var win = new libui.UiWindow('UiSlider example', 320, 60, true);
win.margined = true;

var widget = new libui.UiSlider();
widget.value = 50;

var cnt = new libui.UiVerticalBox();
cnt.padded = true;
cnt.append(widget, false);

win.setChild(cnt);

win.onClosing(function () {
	win.close();
	libui.Ui.quit();
});

win.show();

libui.Ui.main();

