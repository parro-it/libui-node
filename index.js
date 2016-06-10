const nbind = require('nbind');
const binding = nbind.init(__dirname);

module.exports = binding.lib;
