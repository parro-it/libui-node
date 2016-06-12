const libui = require('../index.js');
const globalMenus = [];

function menu(template) {
	for (const mnu of template) {
		const mnuObj = new libui.UiMenu(mnu.label || '');
		globalMenus.push(mnuObj);

		for (const subMnu of mnu.submenu || []) {
			switch (subMnu.type) {
				case 'separator':
					mnuObj.appendSeparator();
					break;
				case 'checkbox':
					mnuObj.appendCheckItem(subMnu.label || '');
					break;
				default:
					if (subMnu.role) {
						switch (subMnu.role) {
							case 'quit':
								mnuObj.appendQuitItem();
								break;
							case 'about':
								mnuObj.appendAboutItem();
								break;
							case 'preferences':
								mnuObj.appendPreferencesItem();
								break;
							default:
						}
					} else {
						const subMnuObj = mnuObj.appendItem(subMnu.label || '');
						if (subMnu.click) {
							subMnuObj.onClicked(subMnu.click);
						}
					}

			}
		}
	}
}

function appendAll(children, parent, stretchy = false) {
	for (const ctrl of children) {
		const stretch = ctrl.stretchy === undefined ?
			stretchy :
			Boolean(ctrl.stretchy);

		parent.append(ctrl, stretch);
	}
}

function hBox({
	enabled = true,
	visible = true,
	padded = true
}, ...children) {
	const ctrl = new libui.UiHorizontalBox();

	ctrl.visible = visible;
	ctrl.enabled = enabled;
	ctrl.padded = padded;

	appendAll(children, ctrl, true);

	return ctrl;
}

function vBox({
	enabled = true,
	visible = true,
	padded = true
}, ...children) {
	const ctrl = new libui.UiVerticalBox();

	ctrl.visible = visible;
	ctrl.enabled = enabled;
	ctrl.padded = padded;

	appendAll(children, ctrl);

	return ctrl;
}

function wrapChildren(children) {
	const childs = Array.from(children);

	if (childs.length === 1) {
		return childs[0];
	}

	const box = vBox({});
	appendAll(childs, box);
	return box;
}

function window({
	title = '',
	width,
	height,
	margined = true,
	hasMenubar = false,
	onClosing = null
}, ...children) {
	const win = new libui.UiWindow(title, width, height, hasMenubar);
	win.margined = margined;

	if (onClosing) {
		win.onClosing(onClosing);
	}

	win.setChild(wrapChildren(children));

	return win;
}

const EventHandler = Symbol('EventHandler');

function mkControl(Class, defaults) {
	const contructor = (props) => {
		const ctrl = new Class();

		for (const propName of Object.keys(defaults)) {
			const defaultValue = defaults[propName];
			if (defaultValue === EventHandler) {
				if (props[propName]) {
					ctrl[propName](props[propName]);
				}
			} else if (props[propName] !== undefined && props[propName] !== defaultValue) {
				ctrl[propName] = props[propName];
			}
		}
		if (props.stretchy !== undefined) {
			ctrl.stretchy = props.stretchy;
		}

		return ctrl;
	};

	return contructor;
}

const group = (props, ...children) => {
	const ctrl = mkControl(libui.UiGroup, {
		title: '',
		margined: true,
		enabled: true,
		visible: true
	})(props);

	ctrl.setChild(wrapChildren(children));

	return ctrl;
};

const entry = mkControl(libui.UiEntry, {
	readOnly: false,
	enabled: true,
	text: '',
	visible: true,
	onChanged: EventHandler
});

const multilineEntry = mkControl(libui.UiMultilineEntry, {
	readOnly: false,
	enabled: true,
	text: '',
	visible: true,
	onChanged: EventHandler
});

const label = mkControl(libui.UiLabel, {
	enabled: true,
	text: '',
	visible: true
});

const separator = mkControl(libui.UiSeparator, {
	enabled: true,
	visible: true
});

const datePicker = mkControl(libui.UiDatePicker, {
	enabled: true,
	visible: true
});

const timePicker = mkControl(libui.UiTimePicker, {
	enabled: true,
	visible: true
});

const dateTimePicker = mkControl(libui.UiDateTimePicker, {
	enabled: true,
	visible: true
});

const button = mkControl(libui.UiButton, {
	enabled: true,
	visible: true,
	text: '',
	onClicked: EventHandler
});

const checkBox = mkControl(libui.UiCheckbox, {
	enabled: true,
	visible: true,
	text: '',
	checked: false,
	onToggled: EventHandler
});

const spinbox = mkControl(libui.UiSpinbox, {
	enabled: true,
	visible: true,
	value: 0,
	onChanged: EventHandler
});

const slider = mkControl(libui.UiSlider, {
	enabled: true,
	visible: true,
	value: 0,
	onChanged: EventHandler
});

const progressBar = mkControl(libui.UiProgressBar, {
	enabled: true,
	visible: true,
	value: 0
});

const combobox = (props, ...children) => {
	const ctrl = mkControl(libui.UiCombobox, {
		enabled: true,
		visible: true,
		selected: 0,
		onSelected: EventHandler
	})(props);

	for (const child of children) {
		ctrl.append(child);
	}

	return ctrl;
};

const radioButtons = (props, ...children) => {
	const ctrl = mkControl(libui.UiRadioButtons, {
		enabled: true,
		visible: true,
		selected: 0,
		onSelected: EventHandler
	})(props);

	for (const child of children) {
		ctrl.append(child);
	}

	return ctrl;
};

const editableCombobox = (props, ...children) => {
	const ctrl = mkControl(libui.UiEditableCombobox, {
		enabled: true,
		visible: true,
		text: '',
		onChanged: EventHandler
	})(props);

	for (const child of children) {
		ctrl.append(child);
	}

	return ctrl;
};

const tab = (props, ...children) => {
	const ctrl = mkControl(libui.UiTab, {
		enabled: true,
		visible: true,
		margined: true
	})(props);

	for (const child of children) {
		ctrl.append(child, multilineEntry({text: `
			Lorem ipsum dolor sit amet, consectetur adipiscing elit,
			sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.
			Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris
			nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in
			reprehenderit`}));
	}

	return ctrl;
};

module.exports = {
	window,
	menu,
	entry,
	vBox,
	hBox,
	group,
	button,
	checkBox,
	label,
	separator,
	datePicker,
	dateTimePicker,
	timePicker,
	spinbox,
	slider,
	progressBar,
	combobox,
	editableCombobox,
	radioButtons,
	tab,
	multilineEntry
};
