const resolve = require('path').resolve;
const writeFileSync = require('fs').writeFileSync;


function writeFile(name, description, ...contents) {
	const path = resolve(__dirname, '../docs', name.slice(2).toLowerCase() + '.md');
	const template = `
# ${name.slice(2)}

> ${description}
`;
	writeFileSync(path, template);
}

function property(name, description, type) {

}

function event(name, description) {

}

writeFile('UiForm', 'A container that organize children as labeled fields.',
	property('visible', Boolean),
	property('enabled', Boolean),
	property('padded', Boolean)
);

writeFile('UiGrid', 'A powerful container that allow to specify size and position of each children.',
	property('visible', Boolean),
	property('enabled', Boolean),
	property('padded', Boolean)
);

writeFile('UiEntry', 'A simple, single line text entry widget.',
	property('visible', Boolean),
	property('enabled', Boolean),
	property('readOnly', Boolean),
	property('text', String),
	event('onChanged', 'text', String)
);

writeFile('UiMultilineEntry', 'A multiline text entry widget.',
	property('visible', Boolean),
	property('enabled', Boolean),
	property('readOnly', Boolean),
	property('text', String)
);


writeFile('UiLabel', 'A static text label.',
	property('visible', Boolean),
	property('enabled', Boolean),
	property('text', String)
);

writeFile('UiVerticalSeparator', 'A vertical line to visually separate widgets.',
	property('visible', Boolean),
	property('enabled', Boolean)
);

writeFile('UiHorizontalSeparator', 'An horizontal line to visually separate widgets.',
	property('visible', Boolean),
	property('enabled', Boolean)
);

writeFile('UiDatePicker', 'A widgets to edit dates.',
	property('visible', Boolean),
	property('enabled', Boolean)
);

writeFile('UiTimePicker', 'A widgets to edit times.',
	property('visible', Boolean),
	property('enabled', Boolean)
);

writeFile('UiDateTimePicker', 'A widgets to edit date/times.',
	property('visible', Boolean),
	property('enabled', Boolean)
);

writeFile('UiButton', 'A simple button.',
	property('visible', Boolean),
	property('enabled', Boolean),
	property('text', String)
);

writeFile('UiCheckbox', 'A checkbox widget.',
	property('visible', Boolean),
	property('enabled', Boolean),
	property('checked', Boolean),
	property('text', String),
	event('onToggled', 'checked', Boolean)
);

writeFile('UiSpinbox', 'An entry widget for numerical values.',
	property('visible', Boolean),
	property('enabled', Boolean),
	property('value', Number),
	event('onChanged', 'value', Number)
);

writeFile('UiSlider', 'Horizontal slide to set numerical values.',
	property('visible', Boolean),
	property('enabled', Boolean),
	property('value', Number),
	event('onChanged', 'value', Number)

);

writeFile('UiProgressBar','Progress bar widget.',
	property('visible', Boolean),
	property('enabled', Boolean),
	property('value', Number)
);

writeFile('UiCombobox', 'A drop down combo box that allow list selection only.',
	property('visible', Boolean, comboBuilder),
	property('enabled', Boolean, comboBuilder),
	property('selected', Number, comboBuilder),
	event('onSelected', 'selected', Number, comboBuilder)
);

writeFile('UiRadioButtons', 'A widget that represent a group of radio options.',
	property('visible', Boolean, radioBuilder),
	property('enabled', Boolean, radioBuilder),
	property('selected', Number, radioBuilder),
	event('onSelected', 'selected', Number, radioBuilder)
);

writeFile('UiEditableCombobox', 'A drop down combo box that allow selection from list or free text entry.',
	property('visible', Boolean),
	property('enabled', Boolean),
	property('text', String),
	event('onChanged', 'text', String)
);

writeFile('UiColorButton', 'A button that open a color palette popup.',
	property('color', libui.Color),
	event('onChanged', 'color', libui.Color)
);




/*
var libui = require('../index.js');

libui.Ui.init();

var win = new libui.UiWindow("Example window", 640, 480, true);
win.borderless = true;
var box = new libui.UiVerticalBox();
var entry = new libui.UiMultilineEntry();
entry.text = 'This is some text';

box.append(entry, 1);

win.setChild(box);

win.onClosing(function () {
	libui.stopLoop();
});

win.show();

libui.startLoop();
*/
