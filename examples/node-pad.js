const libui = require('../index.js');
libui.Ui.init();
const {
	label,
	window,
	tab,
	menu,
	multilineEntry
} = require('./utils.js');

const onClosing = () => libui.stopLoop();

const winProps = {
	hasMenubar: true,
	title: 'Node Pad',
	width: 640,
	height: 480,
	onClosing
};

libui.Ui.init();

let win;

menu([{
	label: 'File',
	submenu: [
		{
			label: 'Open',
			click: () => {
				const filename = libui.UiDialogs.openFile(win);
				if (filename) {
					libui.UiDialogs.msgBoxError(win, 'File selected', filename);
				}
			}
		}, {
			label: 'Close current tab',
			click: () => {

			}
		}, {
			label: 'Save',
			click: () => {

			}
		}, {
			label: 'Save as',
			click: () => {
				const filename = libui.UiDialogs.saveFile(win);
				if (filename) {
					libui.UiDialogs.msgBoxError(win, 'File selected', filename);
				}
			}
		}, {
			role: 'quit'
		}
	]
}, {
	label: 'Edit',
	submenu: [
		{
			label: 'Copy'
		}, {
			label: 'Paste'
		}, {
			label: 'Cut'
		}, {
			label: 'Select all'
		}
	]
}, {
	label: 'Help',
	submenu: [
		{
			label: 'Help',
			click: () => {}
		}, {
			role: 'about'
		}
	]
}]);

win = window(winProps,
	tab({stretchy: true},
		multilineEntry({stretchy: true, tabTitle: 'New file'})
	),
	label({stretchy: false, text: 'File not changed'})
);

win.show();
libui.startLoop();

