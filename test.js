import test from 'ava';
import libui from './index';

libui.Ui.init();

test('new UiWindow - throw if too few arguments', t => {
	const err = t.throws(() => new libui.UiWindow('Test window'));
	t.true(err instanceof Error);
	t.is(err.message, 'Wrong number of arguments');
});

test('setting Entry text emit onChange', async (t) => {
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

function checkEvent(Class, eventName, propertyName, propertyType, builder = () => new Class()) {
	return [`Widget ${Class.name} has event ${eventName}`, t => {
		let emitted = false;

		const widget = builder();
		widget[eventName](() => {
			emitted = true;
			libui.stopLoop();
		});

		libui.startLoop();
		if (propertyType === Boolean) {
			widget[propertyName] = true;
		} else if (propertyType === String) {
			widget[propertyName] = 'some value';
		} else if (propertyType === Number) {
			widget[propertyName] = 2;
		}
		t.true(emitted);
	}];
}

function checkProperty(Class, propertyName, type, builder = () => new Class()) {
	return [`Widget ${Class.name} has property ${propertyName}`, t => {
		const widget = builder();
		const setterName = 'set' + propertyName[0].toUpperCase() + propertyName.slice(1);
		const getterName = 'get' + propertyName[0].toUpperCase() + propertyName.slice(1);
		const setter = widget[setterName].bind(widget);
		const getter = widget[getterName].bind(widget);
		t.true(typeof getter === 'function');
		t.true(typeof setter === 'function');

		if (type === Boolean) {
			setter(true);
			t.true(getter());
			t.true(widget[propertyName]);

			setter(false);
			t.false(getter());
			t.false(widget[propertyName]);

			widget[propertyName] = true;
			t.true(getter());

			widget[propertyName] = false;
			t.false(getter());
		}

		if (type === String) {
			setter('some value');
			t.is(widget[propertyName], 'some value');
			t.is(getter(), 'some value');

			setter('');
			t.is(getter(), '');
			t.is(widget[propertyName], '');

			widget[propertyName] = 'some value';
			t.is(getter(), 'some value');

			widget[propertyName] = '';
			setter('');
			t.is(getter(), '');
		}

		if (type === Number) {
			setter(2);
			t.is(getter(), 2);
			t.is(widget[propertyName], 2);

			setter(0);
			t.is(getter(), 0);
			t.is(widget[propertyName], 0);

			widget[propertyName] = 2;
			t.is(getter(), 2);

			widget[propertyName] = 0;
			t.is(getter(), 0);
		}
	}];
}

/* eslint-disable ava/test-title */
/* eslint-disable ava/no-identical-title */

test(...checkProperty(libui.UiEntry, 'visible', Boolean));
test(...checkProperty(libui.UiEntry, 'enabled', Boolean));
test(...checkProperty(libui.UiEntry, 'readOnly', Boolean));
test(...checkProperty(libui.UiEntry, 'text', String));

test(...checkProperty(libui.UiMultilineEntry, 'visible', Boolean));
test(...checkProperty(libui.UiMultilineEntry, 'enabled', Boolean));
test(...checkProperty(libui.UiMultilineEntry, 'readOnly', Boolean));
test(...checkProperty(libui.UiMultilineEntry, 'text', String));

test(...checkProperty(libui.UiLabel, 'visible', Boolean));
test(...checkProperty(libui.UiLabel, 'enabled', Boolean));
test(...checkProperty(libui.UiLabel, 'text', String));

test(...checkProperty(libui.UiSeparator, 'visible', Boolean));
test(...checkProperty(libui.UiSeparator, 'enabled', Boolean));

test(...checkProperty(libui.UiSeparator, 'visible', Boolean));
test(...checkProperty(libui.UiSeparator, 'enabled', Boolean));

test(...checkProperty(libui.UiDatePicker, 'visible', Boolean));
test(...checkProperty(libui.UiDatePicker, 'enabled', Boolean));

test(...checkProperty(libui.UiTimePicker, 'visible', Boolean));
test(...checkProperty(libui.UiTimePicker, 'enabled', Boolean));

test(...checkProperty(libui.UiDateTimePicker, 'visible', Boolean));
test(...checkProperty(libui.UiDateTimePicker, 'enabled', Boolean));

test(...checkProperty(libui.UiButton, 'visible', Boolean));
test(...checkProperty(libui.UiButton, 'enabled', Boolean));
test(...checkProperty(libui.UiButton, 'text', String));

test(...checkProperty(libui.UiCheckbox, 'visible', Boolean));
test(...checkProperty(libui.UiCheckbox, 'enabled', Boolean));
test(...checkProperty(libui.UiCheckbox, 'checked', Boolean));
test(...checkProperty(libui.UiCheckbox, 'text', String));

test(...checkProperty(libui.UiSpinbox, 'visible', Boolean));
test(...checkProperty(libui.UiSpinbox, 'enabled', Boolean));
test(...checkProperty(libui.UiSpinbox, 'value', Number));

test(...checkProperty(libui.UiSlider, 'visible', Boolean));
test(...checkProperty(libui.UiSlider, 'enabled', Boolean));
test(...checkProperty(libui.UiSlider, 'value', Number));

test(...checkProperty(libui.UiProgressBar, 'visible', Boolean));
test(...checkProperty(libui.UiProgressBar, 'enabled', Boolean));
test(...checkProperty(libui.UiProgressBar, 'value', Number));

const comboBuilder = () => {
	const cmb = new libui.UiCombobox();
	cmb.append('1');
	cmb.append('2');
	cmb.append('3');
	return cmb;
};

const radioBuilder = () => {
	const cmb = new libui.UiRadioButtons();
	cmb.append('1');
	cmb.append('2');
	cmb.append('3');
	return cmb;
};

test(...checkProperty(libui.UiCombobox, 'visible', Boolean, comboBuilder));
test(...checkProperty(libui.UiCombobox, 'enabled', Boolean, comboBuilder));
test(...checkProperty(libui.UiCombobox, 'selected', Number, comboBuilder));

test(...checkProperty(libui.UiRadioButtons, 'visible', Boolean, radioBuilder));
test(...checkProperty(libui.UiRadioButtons, 'enabled', Boolean, radioBuilder));
test(...checkProperty(libui.UiRadioButtons, 'selected', Number, radioBuilder));

test(...checkProperty(libui.UiEditableCombobox, 'visible', Boolean));
test(...checkProperty(libui.UiEditableCombobox, 'enabled', Boolean));
test(...checkProperty(libui.UiEditableCombobox, 'text', String));

test(...checkEvent(libui.UiSlider, 'onChanged', 'value', Number));

/*

const slider = mkControl(libui.UiSlider, {
	onChanged: EventHandler
});

const combobox = (props, ...children) => {
	const ctrl = mkControl(libui.UiCombobox, {
		onSelected: EventHandler
	})

const radioButtons = (props, ...children) => {
	const ctrl = mkControl(libui.UiRadioButtons, {
		onSelected: EventHandler
	})

const editableCombobox = (props, ...children) => {
	const ctrl = mkControl(libui.UiEditableCombobox, {
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
