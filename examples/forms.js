'use strict';
const libui = require('..');

const win = new libui.UiWindow('Forms window', 800, 600, false);
win.margined = 1;
win.onClosing(() => {
	libui.stopLoop();
});

const hBox = new libui.UiHorizontalBox();
hBox.padded = true;

const name = new libui.UiEntry();
const surname = new libui.UiEntry();
const age = new libui.UiSlider(0, 100);
const JSONData = new libui.UiMultilineEntry();

name.onChanged(setJSON);
surname.onChanged(setJSON);
age.onChanged(setJSON);

name.text = 'Andrea';
surname.text = 'Parodi';
age.value = 40;

const form = new libui.UiForm();
form.padded = true;
form.append('name', name, 0);
form.append('surname', surname, 0);
form.append('age', age, 0);

hBox.append(form, 1);
hBox.append(JSONData, 1);

win.setChild(hBox);
win.show();
libui.startLoop();

function setJSON() {
	const data = {
		name: name.text,
		surname: surname.text,
		age: age.value
	};
	JSONData.text = JSON.stringify(data, null, 4);
}
