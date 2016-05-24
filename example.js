const libui = require('.');

libui.init();
const win = libui.newWindow('Test window', 800, 600, true);
const onClosing = () => {
	console.log(1)
	libui.controlDestroy(win);
	console.log(2)
	libui.quit();
	console.log(3)
};

libui.windowOnClosing(win, onClosing);
libui.controlShow(win);
libui.main();
