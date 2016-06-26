var libui = require('../index.js');

libui.Ui.init();
var win = new libui.UiWindow('Forms window', 800, 600, false);
win.margined = 1;
win.onClosing(function () {
	libui.stopLoop();
});

var hBox = new libui.UiHorizontalBox();
hBox.padded = true;

var name = new libui.UiEntry();
var surname = new libui.UiEntry();
var age = new libui.UiSlider(0, 100);
var JSONData = new libui.UiMultilineEntry();

name.onChanged(setJSON);
surname.onChanged(setJSON);
age.onChanged(setJSON);

name.text = 'Andrea';
surname.text = 'Parodi';
age.value = 40;

var form = new libui.UiForm();
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
	var data = {
		name: name.text,
		surname: surname.text,
		age: age.value
	};
	JSONData.text = JSON.stringify(data, null, 4);
}

