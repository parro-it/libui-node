const readdirSync = require('fs').readdirSync;

function listDir(dir) {
	readdirSync(dir)
		.filter(f => f.endsWith('.cc'))
		.forEach(f => console.log(dir + '/' + f));
}

listDir('src');
listDir('src/Font');
listDir('src/UiArea');
listDir('src/arch/win32');
