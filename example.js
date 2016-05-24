const libui = require('.');

libui.init();
const win = libui.newWindow('Test window', 800, 600, true);
const onClosing = () => {
	libui.controlDestroy(win);
	libui.quit();
};

libui.windowOnClosing(win, onClosing);
libui.windowSetMargined(win, false);
libui.controlShow(win);
libui.main();
