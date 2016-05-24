const libuiNode = require('./build/Release/ui');

libuiNode.init();
const win = libuiNode.newWindow('Test window', 800, 600, true);
libuiNode.show(win);
