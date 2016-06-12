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

		if (type === Number) {
			setter(42);
			t.is(getter(), 42);
			setter(0);
			t.is(getter(), 0);
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

test(...checkPropertyTest(libui.UiButton, 'visible', Boolean));
test(...checkPropertyTest(libui.UiButton, 'enabled', Boolean));
test(...checkPropertyTest(libui.UiButton, 'text', String));

test(...checkPropertyTest(libui.UiCheckbox, 'visible', Boolean));
test(...checkPropertyTest(libui.UiCheckbox, 'enabled', Boolean));
test(...checkPropertyTest(libui.UiCheckbox, 'checked', Boolean));
test(...checkPropertyTest(libui.UiCheckbox, 'text', String));

test(...checkPropertyTest(libui.UiSpinbox, 'visible', Boolean));
test(...checkPropertyTest(libui.UiSpinbox, 'enabled', Boolean));
test(...checkPropertyTest(libui.UiSpinbox, 'value', Number));

test(...checkPropertyTest(libui.UiSlider, 'visible', Boolean));
test(...checkPropertyTest(libui.UiSlider, 'enabled', Boolean));
test(...checkPropertyTest(libui.UiSlider, 'value', Number));

test(...checkPropertyTest(libui.UiProgressBar, 'visible', Boolean));
test(...checkPropertyTest(libui.UiProgressBar, 'enabled', Boolean));
test(...checkPropertyTest(libui.UiProgressBar, 'value', Number));

/*

const slider = mkControl(libui.UiSlider, {
	onChanged: EventHandler
});


const combobox = (props, ...children) => {
	const ctrl = mkControl(libui.UiCombobox, {
		enabled: true,
		visible: true,
		selected: 0,
		onSelected: EventHandler
	})

const radioButtons = (props, ...children) => {
	const ctrl = mkControl(libui.UiRadioButtons, {
		enabled: true,
		visible: true,
		selected: 0,
		onSelected: EventHandler
	})

const editableCombobox = (props, ...children) => {
	const ctrl = mkControl(libui.UiEditableCombobox, {
		enabled: true,
		visible: true,
		text: '',
		onChanged: EventHandler
	})

const entry = mkControl(libui.UiEntry, {
	onChanged: EventHandler
});

const multilineEntry = mkControl(libui.UiMultilineEntry, {
	onChanged: EventHandler
});

const button = mkControl(libui.UiButton, {
	onClicked: EventHandler
});

const checkBox = mkControl(libui.UiCheckbox, {
	onToggled: EventHandler
});

const spinbox = mkControl(libui.UiSpinbox, {
	onChanged: EventHandler
});

*/
