'use strict';

const libui = require('..');

const {
	size,
	datePicker,
	dateTimePicker,
	timePicker,
	separator,
	label,
	window,
	entry,
	searchEntry,
	passwordEntry,
	hBox,
	group,
	button,
	colors,
	colorButton,
	checkBox,
	spinbox,
	slider,
	progressBar,
	vBox,
	combobox,
	editableCombobox,
	radioButtons,
	tab,
	menu
} = require('./utils.js');

const lorem = `Lorem ipsum dolor sit amet, consectetur adipiscing elit,
sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.
Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris
nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in
reprehenderit
`;

let win = null;
let spin;
let slide;
let progress;
let colorBtn;
let status;

const onClosing = () => {
	win.close();
	libui.stopLoop();
};

libui.Ui.onShouldQuit(() => {
	onClosing();
});

function onContentSizeChanged() {
	status.text = `window size: (${win.contentSize.w} x ${win.contentSize.h})`;
}

const updateValue = value => {
	if (value === spin.value) {
		return;
	}
	spin.value = value;
	slide.value = value;
	progress.value = value;
};

const changeTitle = () => {
	win.title = 'Title changed';
	colorBtn.color = colors.red;
};

const areaHandler = {
	drawCb() {
		console.log('drawCb');
	},

	mouseEventCb() {
		console.log('mouseEventCb');
	},

	mouseCrossedCb() {
		console.log('mouseCrossedCb');
	},

	dragBrokenCb() {
		console.log('dragBrokenCb');
	},

	keyEventCb() {
		console.log('keyEventCb');
	}
};

const area = new libui.UiArea(
	areaHandler.drawCb,
	areaHandler.mouseEventCb,
	areaHandler.mouseCrossedCb,
	areaHandler.dragBrokenCb,
	areaHandler.keyEventCb,
	300,
	150);

area.props = {
	tabTitle: 'Area',
	stretchy: true
};

menu([
	{
		label: 'File',
		submenu: [
			{
				label: 'Open',
				click: () => {
					const filename = libui.UiDialogs.openFile(win);
					if (filename) {
						libui.UiDialogs.msgBox(win, 'File selected', filename);
					} else {
						libui.UiDialogs.msgBox(
							win,
							'No file selected',
							`Don't be alarmed!`);
					}
				}
			},
			{
				label: 'Save',
				click: () => {
					const filename = libui.UiDialogs.saveFile(win);
					if (filename) {
						libui.UiDialogs.msgBox(win, 'File selected', filename);
					} else {
						libui.UiDialogs.msgBox(
							win,
							'No file selected',
							`Don't be alarmed!`);
					}
				}
			},
			{
				role: 'quit'
			}
		]
	},
	{
		label: 'Edit',
		submenu: [
			{
				label: 'Checkable Item',
				type: 'checkbox'
			},
			{
				type: 'separator'
			},
			{
				label: 'Disabled Item',
				disabled: true
			},
			{
				role: 'preferences'
			}
		]
	},
	{
		label: 'Help',
		submenu: [
			{
				label: 'Help',
				click: () => {}
			},
			{
				role: 'about'
			}
		]
	},
	{
		label: 'Window',
		submenu: [
			{
				label: 'Full screen',
				click: () => {
					win.fullscreen = !win.fullscreen;
				}
			},
			{
				label: 'Borderless',
				click: () => {
					win.borderless = !win.borderless;
				}
			},
			{
				label: 'Reset size',
				click: () => {
					win.contentSize = size(800, 600);
				}
			}
		]
	}
]);

const winProps = {
	hasMenubar: true,
	title: 'Control Gallery',
	width: 640,
	height: 480,
	onClosing,
	onContentSizeChanged: onContentSizeChanged
};

win = window(
	winProps,
	hBox(
		{padded: true},
		group(
			{margined: true, title: 'Basic Controls'},
			button({text: 'Button', onClicked: changeTitle}),
			(colorBtn = colorButton({})),
			checkBox({text: 'Checkbox'}),
			entry({text: 'Entry'}),
			searchEntry({ text: 'Search Entry' }),
			passwordEntry({text: 'Password Entry'}),
			label({text: 'Label'}),
			separator({}),
			datePicker({}),
			dateTimePicker({}),
			timePicker({})),

		vBox(
			{padded: true},
			group(
				{margined: true, title: 'Numbers'},
				(spin = spinbox({onChanged: () => updateValue(spin.value)})),
				(slide = slider({onChanged: () => updateValue(slide.value)})),
				(progress = progressBar({}))),

			group(
				{margined: true, title: 'Lists', stretchy: true},
				combobox(
					{},
					'Combobox Item 1',
					'Combobox Item 2',
					'Combobox Item 3'),
				editableCombobox(
					{},
					'Editable Item 1',
					'Editable Item 2',
					'Editable Item 3'),
				radioButtons(
					{},
					'Radio Button 1',
					'Radio Button 2',
					'Radio Button 3'),
				tab(
					{stretchy: true},
					entry({
						text: lorem.slice(5),
						tabTitle: 'Page 1',
						stretchy: true
					}),
					entry({
						text: lorem.slice(10),
						tabTitle: 'Page 2',
						stretchy: true
					}),
					entry({
						text: lorem.slice(20),
						tabTitle: 'Page 3',
						stretchy: true
					}),
					area)))),
	(status = label({stretchy: true, text: `window size: (${winProps.width} x ${winProps.height})`})));

win.show();
libui.startLoop();
