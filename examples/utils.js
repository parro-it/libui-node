'use strict';
const libui = require('..');

const globalMenus = [];

function buildMenu(mnu) {
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
					if (subMnu.disabled) {
						subMnuObj.disable();
					}
				}
		}
	}
}

function menu(template) {
	template.forEach(buildMenu);
}

function appendAll(children, parent, stretchy = false) {
	for (const ctrl of children) {
		const stretch =
			ctrl.stretchy === undefined ? stretchy : Boolean(ctrl.stretchy);

		parent.append(ctrl, stretch);
	}
}

const EventHandler = Symbol('EventHandler');

function mkControl(Class, defaults) {
	const contructor = props => {
		const ctrl = new Class();
		ctrl.props = props;
		for (const propName of Object.keys(defaults)) {
			const defaultValue = defaults[propName];
			if (defaultValue === EventHandler) {
				if (props[propName]) {
					ctrl[propName](props[propName]);
				}
			} else if (
				props[propName] !== undefined &&
				props[propName] !== defaultValue) {
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

const hBox = (props, ...children) => {
	const ctrl = mkControl(libui.UiHorizontalBox, {
		padded: false,
		enabled: true,
		visible: true
	})(props);

	appendAll(children, ctrl, true);

	return ctrl;
};

const vBox = (props, ...children) => {
	const ctrl = mkControl(libui.UiVerticalBox, {
		padded: false,
		enabled: true,
		visible: true
	})(props);

	appendAll(children, ctrl, false);

	return ctrl;
};

function wrapChildren(children) {
	const childs = Array.from(children);

	if (childs.length === 1) {
		return childs[0];
	}

	const box = vBox({padded: true});
	appendAll(childs, box);
	return box;
}

function point(x, y) {
	return new libui.Point(x, y);
}

function size(w, h) {
	return new libui.Size(w, h);
}

function window(
	{
		title = '',
		width,
		height,
		margined = true,
		hasMenubar = false,
		fullscreen = false,
		borderless = false,
		onClosing = null,
		onContentSizeChanged= null,
	},
	...children) {
	const win = new libui.UiWindow(title, width, height, hasMenubar);
	win.margined = margined;
	win.fullscreen = fullscreen;
	win.borderless = borderless;

	if (onClosing) {
		win.onClosing(onClosing);
	}
	if (onContentSizeChanged) {
		win.onContentSizeChanged(onContentSizeChanged)
	}

	win.setChild(wrapChildren(children));

	return win;
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

const searchEntry = mkControl(libui.UiSearchEntry, {
	readOnly: false,
	enabled: true,
	text: '',
	visible: true,
	onChanged: EventHandler
});

const passwordEntry = mkControl(libui.UiPasswordEntry, {
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

const separator = mkControl(libui.UiHorizontalSeparator, {
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

const colorButton = mkControl(libui.UiColorButton, {
	enabled: true,
	visible: true
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
		const title = child.props.tabTitle || '';
		ctrl.append(title, child);
	}

	return ctrl;
};

function color(r, g, b, a) {
	return new new libui.Color(r, g, b, a)();
}

const colors = {
	red: new libui.Color(255, 0, 0, 1),
	green: new libui.Color(0, 255, 0, 1),
	blue: new libui.Color(0, 0, 255, 1)
};

module.exports = {
	size,
	color,
	colors,
	point,
	window,
	menu,
	entry,
	searchEntry,
	passwordEntry,
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
	multilineEntry,
	colorButton
};
