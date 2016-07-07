
var libui = require('../../index');

libui.Ui.init();
var win = new libui.UiWindow('UiGrid example', 320, 60, true);
win.margined = true;

var grid = new libui.UiGrid();
grid.padded = true;
grid.append(new libui.UiLabel('name'), 0, 0, 2, 1, 0, 0, 0, 1);
grid.append(new libui.UiLabel('surname'), 0, 1, 2, 1, 0, 0, 0, 1);
grid.append(new libui.UiLabel('age'), 0, 2, 2, 1, 0, 0, 0, 1);

grid.append(new libui.UiEntry(), 2, 0, 2, 1, 0, 0, 0, 1);
grid.append(new libui.UiEntry(), 2, 1, 3, 1, 0, 0, 0, 1);
grid.append(new libui.UiEntry(), 2, 2, 4, 2, 0, 0, 0, 1);

win.setChild(grid);

win.onClosing(function () {
	win.close();
	libui.Ui.quit();
});

win.show();

libui.Ui.main();

