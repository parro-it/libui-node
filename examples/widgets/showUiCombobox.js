
var libui = require('../../index');

libui.Ui.init();
var win = new libui.UiWindow('UiCombobox example', 320, 60, true);
win.margined = true;

var widget = new libui.UiCombobox();
widget.append('Item1');
widget.append('Item2');
widget.append('Item3');
win.setChild(widget);

win.onClosing(function () {
	win.close();
	libui.Ui.quit();
});

win.show();

libui.Ui.main();

