const libui = require('.');

libui.init();
const win = libui.newWindow('Test window', 800, 600, true);
libui.show(win);
libui.main();
