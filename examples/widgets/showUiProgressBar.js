
var libui = require('../../index');

libui.Ui.init();
var win = new libui.UiWindow('UiProgressBar example', 320, 60, true);
win.margined = true;

var widget = new libui.UiProgressBar();
widget.value = 50;
win.setChild(widget);

win.onClosing(function () {
	win.close();
	libui.Ui.quit();
});

win.show();

libui.Ui.main();

