
var libui = require('../../index');

libui.Ui.init();
var win = new libui.UiWindow('UiTab example', 320, 90, true);
win.margined = true;

var widget = new libui.UiTab();
widget.padded = true;
widget.append("Tab 1", new libui.UiEntry());
widget.append("Tab 2", new libui.UiEntry());
widget.append("Tab 3", new libui.UiEntry());
win.setChild(widget);

win.onClosing(function () {
	win.close();
	libui.Ui.quit();
});

win.show();

libui.Ui.main();

