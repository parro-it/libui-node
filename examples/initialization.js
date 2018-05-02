const {
	UiWindow,
	UiMenu,
	startLoop,
	stopLoop,
	onShouldQuit
} = require('..');

const menu = new UiMenu('File');
menu.appendQuitItem();

const window = UiWindow('Initialization Example', 400, 300, true);

onShouldQuit(() => {
	window.close();
	stopLoop();
});

window.show();
startLoop();
