#ifndef UI_NODE_ENTRY
#define UI_NODE_ENTRY 1

#define DEFINE_ENTRY_METHODS()                                                 \
	void setText(std::string text);                                            \
	std::string getText();                                                     \
	void setReadOnly(bool readOnly);                                           \
	bool getReadOnly();

#define INHERITS_ENTRY_METHODS(CLASS)                                          \
	void CLASS::setText(std::string text) {                                    \
		UiEntryBase::setText(text);                                            \
	}                                                                          \
	std::string CLASS::getText() {                                             \
		return UiEntryBase::getText();                                         \
	}                                                                          \
	void CLASS::setReadOnly(bool readOnly) {                                   \
		UiEntryBase::setReadOnly(readOnly);                                    \
	}                                                                          \
	bool CLASS::getReadOnly() {                                                \
		return UiEntryBase::getReadOnly();                                     \
	}                                                                          \
	void CLASS::onChanged(nbind::cbFunction &cb) {                             \
		UiEntryBase::onChanged(cb);                                            \
	}

#define DECLARE_ENTRY_METHODS()                                                \
	getset(getText, setText);                                                  \
	getset(getReadOnly, setReadOnly);                                          \
	method(onChanged);                                                         \
	method(getText);                                                           \
	method(setText);                                                           \
	method(getReadOnly);                                                       \
	method(setReadOnly);

#endif
