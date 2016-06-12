const libui = require('../index.js');
const {
	datePicker,
	dateTimePicker,
	timePicker,
	separator,
	label,
	window,
	entry,
	hBox,
	group,
	button,
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

libui.Ui.init();

const onClosing = () => libui.stopLoop();

let win;
let spin;
let slide;
let progress;

const updateValue = value => {
	spin.value = value;
	slide.value = value;
	progress.value = value;
};

menu([{
	label: 'File',
	submenu: [
		{
			label: 'Open',
			click: () => {
				const filename = libui.UiDialogs.openFile(win);
				if (filename) {
					libui.UiDialogs.msgBoxError(win, 'File selected', filename);
				} else {
					libui.UiDialogs.msgBoxError(win, 'No file selected', 'Don\'t be alarmed!');
				}
			}
		}, {
			label: 'Save',
			click: () => {
				const filename = libui.UiDialogs.saveFile(win);
				if (filename) {
					libui.UiDialogs.msgBoxError(win, 'File selected', filename);
				} else {
					libui.UiDialogs.msgBoxError(win, 'No file selected', 'Don\'t be alarmed!');
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
			label: 'Checkable Item',
			type: 'checkbox'
		}, {
			type: 'separator'
		}, {
			label: 'Disabled Item',
			click: () => {}
		}, {
			role: 'preferences'
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

win = window({hasMenubar: true, title: 'Control Gallery', width: 640, height: 480, onClosing},
	hBox({},
		group({margined: true, title: 'Basic Controls'},
			button({text: 'Button'}),
			checkBox({text: 'Checkbox'}),
			entry({text: 'Entry'}),
			label({text: 'Label'}),
			separator({}),
			datePicker({}),
			dateTimePicker({}),
			timePicker({})
		),

		vBox({},
			group({margined: true, title: 'Numbers'},
				spin = spinbox({onChanged: () => updateValue(spin.value)}),
				slide = slider({onChanged: () => updateValue(slide.value)}),
				progress = progressBar({})
			),

			group({margined: true, title: 'Lists', stretchy: true},
				combobox({},
					'Combobox Item 1',
					'Combobox Item 2',
					'Combobox Item 3'
				),
				editableCombobox({},
					'Editable Item 1',
					'Editable Item 2',
					'Editable Item 3'
				),
				radioButtons({},
					'Radio Button 1',
					'Radio Button 2',
					'Radio Button 3'
				),
				tab({stretchy: true},
					'Page 1',
					'Page 2',
					'Page 3'
				)
			)
		)
	)
);

win.show();
libui.startLoop();
