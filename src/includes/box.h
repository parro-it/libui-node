#ifndef UI_NODE_BOX
#define UI_NODE_BOX 1

#define DEFINE_BOX_METHODS()                                                   \
	void append(std::shared_ptr<UiControl>, bool stretchy);                    \
	void deleteAt(int index);                                                  \
	bool getPadded();                                                          \
	void setPadded(bool padded);

#define INHERITS_BOX_METHODS(CLASS)                                            \
	void CLASS::append(std::shared_ptr<UiControl> control, bool stretchy) {    \
		UiBox::append(control, stretchy);                                      \
	}                                                                          \
	void CLASS::deleteAt(int index) {                                          \
		UiBox::deleteAt(index);                                                \
	}                                                                          \
	bool CLASS::getPadded() {                                                  \
		return UiBox::getPadded();                                             \
	}                                                                          \
	void CLASS::setPadded(bool padded) {                                       \
		UiBox::setPadded(padded);                                              \
	}

#define DECLARE_BOX_METHODS()                                                  \
	getset(getPadded, setPadded);                                              \
	method(getPadded);                                                         \
	method(setPadded);                                                         \
	method(append);                                                            \
	method(deleteAt);

#endif
