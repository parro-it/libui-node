import test from 'ava';
import libui from './index';

test('new UiWindow - throw if too few arguments', t => {
	const err = t.throws(() => new libui.UiWindow('Test window'));
	t.true(err instanceof Error);
	t.is(err.message, 'Wrong number of arguments');
});

test('setting Entry text emit onChange', async (t) => {
	libui.Ui.init();
	let emitted;

	const entry = new libui.UiEntry();
	entry.onChanged(() => {
		emitted = true;
		libui.stopLoop();
	});

	libui.startLoop();
	entry.text = 'changed';
	t.true(emitted);
});

function checkPropertyTest(Class, propertyName, type) {
	return [`Widget ${Class.name} has property ${propertyName}`, t => {
		const widget = new Class();
		const setterName = 'set' + propertyName[0].toUpperCase() + propertyName.slice(1);
		const getterName = 'get' + propertyName[0].toUpperCase() + propertyName.slice(1);
		const setter = widget[setterName].bind(widget);
		const getter = widget[getterName].bind(widget);
		t.true(typeof getter === 'function');
		t.true(typeof setter === 'function');

		if (type === Boolean) {
			setter(true);
			t.true(getter());
			setter(false);
			t.false(getter());
		}

		if (type === String) {
			setter('some value');
			t.is(getter(), 'some value');
			setter('');
			t.is(getter(), '');
		}
	}];
}

/* eslint-disable ava/test-title */
/* eslint-disable ava/no-identical-title */

test(...checkPropertyTest(libui.UiEntry, 'visible', Boolean));
test(...checkPropertyTest(libui.UiEntry, 'enabled', Boolean));
test(...checkPropertyTest(libui.UiEntry, 'readOnly', Boolean));
test(...checkPropertyTest(libui.UiEntry, 'text', String));

test(...checkPropertyTest(libui.UiMultilineEntry, 'visible', Boolean));
test(...checkPropertyTest(libui.UiMultilineEntry, 'enabled', Boolean));
test(...checkPropertyTest(libui.UiMultilineEntry, 'readOnly', Boolean));
test(...checkPropertyTest(libui.UiMultilineEntry, 'text', String));

test(...checkPropertyTest(libui.UiLabel, 'visible', Boolean));
test(...checkPropertyTest(libui.UiLabel, 'enabled', Boolean));
test(...checkPropertyTest(libui.UiLabel, 'text', String));

test(...checkPropertyTest(libui.UiSeparator, 'visible', Boolean));
test(...checkPropertyTest(libui.UiSeparator, 'enabled', Boolean));

test(...checkPropertyTest(libui.UiSeparator, 'visible', Boolean));
test(...checkPropertyTest(libui.UiSeparator, 'enabled', Boolean));

test(...checkPropertyTest(libui.UiDatePicker, 'visible', Boolean));
test(...checkPropertyTest(libui.UiDatePicker, 'enabled', Boolean));

test(...checkPropertyTest(libui.UiTimePicker, 'visible', Boolean));
test(...checkPropertyTest(libui.UiTimePicker, 'enabled', Boolean));

test(...checkPropertyTest(libui.UiDateTimePicker, 'visible', Boolean));
test(...checkPropertyTest(libui.UiDateTimePicker, 'enabled', Boolean));



/*
const entry = mkControl(libui.UiEntry, {
	onChanged: EventHandler
});

const multilineEntry = mkControl(libui.UiMultilineEntry, {
	onChanged: EventHandler
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
*/
