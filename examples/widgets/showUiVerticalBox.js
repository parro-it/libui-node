
var libui = require('../../index');

libui.Ui.init();
var win = new libui.UiWindow('UiVerticalBox example', 320, 60, true);
win.margined = true;

var widget = new libui.UiVerticalBox();
widget.padded = true;
widget.append(new libui.UiEntry(), false);
widget.append(new libui.UiEntry(), false);
widget.append(new libui.UiEntry(), false);
win.setChild(widget);

win.onClosing(function () {
	win.close();
	libui.Ui.quit();
});

win.show();

libui.Ui.main();

