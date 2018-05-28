const {OpenTypeFeatures: OpenTypeFeaturesC} = require('..');

class OpenTypeFeatures {
	constructor(handle) {
		if (handle) {
			this.handle = handle;
		} else {
			this.handle = OpenTypeFeaturesC.create();
		}
	}

	clone() {
		return new OpenTypeFeatures(OpenTypeFeaturesC.clone(this.handle));
	}

	add(tag, value) {
		if (typeof tag !== 'string' || tag.length !== 4) {
			throw new TypeError('The \'tag\' argument has to be a 4 character string');
		}
		OpenTypeFeaturesC.addTag(this.handle, tag, value);
	}

	remove(tag) {
		if (typeof tag !== 'string' || tag.length !== 4) {
			throw new TypeError('The \'tag\' argument has to be a 4 character string');
		}
		OpenTypeFeaturesC.removeTag(this.handle, tag);
	}

	get(tag) {
		if (typeof tag !== 'string' || tag.length !== 4) {
			throw new TypeError('The \'tag\' argument has to be a 4 character string');
		}
		return OpenTypeFeaturesC.getTag(this.handle, tag);
	}

	forEach(cb) {
		return OpenTypeFeaturesC.forEach(this.handle, (tag, val) => {
			return Boolean(cb(this, tag, val));
		});
	}
}

module.exports = {OpenTypeFeatures};
