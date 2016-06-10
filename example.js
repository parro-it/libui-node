const libui = require('.');
libui.Ui.init();
const win = new libui.UiWindow('Test window', 800, 600, false);
win.margined = 1;

const box = new libui.UiBox();
const e1 = new libui.UiEntry();
e1.enabled = 0;
box.append(new libui.UiEntry(), 1);
box.append(e1, 0);
box.append(new libui.UiEntry(), 1);
box.append(new libui.UiEntry(), 0);
win.setChild(box);
win.show();
libui.Ui.main();

/*
const win = libui.newWindow('Test window', 800, 600, true);
const entry = libui.newEntry();
libui.windowSetChild(win, entry);
libui.windowOnClosing(win, () => {
	libui.controlDestroy(win);
	libui.quit();
});
libui.windowSetMargined(win, false);
libui.controlShow(win);
libui.main();
*/
