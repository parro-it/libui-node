const libui = require('.');

libui.init();
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
