
var libui = require('../../index');

libui.Ui.init();
var win = new libui.UiWindow('UiHorizontalBox example', 320, 60, true);
win.margined = true;

var widget = new libui.UiHorizontalBox();
widget.padded = true;
widget.append(new libui.UiMultilineEntry(), false);
widget.append(new libui.UiMultilineEntry(), false);
widget.append(new libui.UiMultilineEntry(), false);
win.setChild(widget);

win.onClosing(function () {
	win.close();
	libui.Ui.quit();
});

win.show();

libui.Ui.main();

