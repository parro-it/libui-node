
var libui = require('../../index');

libui.Ui.init();
var win = new libui.UiWindow('UiForm example', 320, 60, true);
win.margined = true;

var widget = new libui.UiForm();
widget.padded = true;
widget.append('name', new libui.UiEntry(), false);
widget.append('surname', new libui.UiEntry(), false);
widget.append('age', new libui.UiEntry(), false);
win.setChild(widget);

win.onClosing(function () {
	win.close();
	libui.Ui.quit();
});

win.show();

libui.Ui.main();

