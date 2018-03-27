# AttributedString

```cpp
class UiOpenTypeFeatures {
  public:
    UiOpenTypeFeatures();
    void free();

    static UiOpenTypeFeatures *clone(UiOpenTypeFeatures *f2);
    void add(const char *tag, uint32_t value);
    void remove(const char *tag);
    // uiOpenTypeFeaturesGet() determines whether the given feature
    // tag is present in otf. If it is, *value is set to the tag's value and
    // nonzero is returned. Otherwise, zero is returned.
    //
    // Note that if uiOpenTypeFeaturesGet() returns zero, value isn't
    // changed. This is important: if a feature is not present in a
    // uiOpenTypeFeatures, the feature is NOT treated as if its
    // value was zero anyway. Script-specific font shaping rules and
    // font-specific feature settings may use a different default value
    // for a feature. You should likewise not treat a missing feature as
    // having a value of zero either. Instead, a missing feature should
    // be treated as having some unspecified default value.
    int get(const char *tag, uint32_t *value);

    // cb(UiOpenTypeFeatures, tag, value)
    void forEach(nbind::cbFunction& cb);
};

class UiFontAttribute {
  public:
    // DON'T CALL IF USED/APPENDED IN AN AttributedString
    void free();
    int getAttributeType();

    // It is an error to call this on a uiAttribute that does not hold the corresponding type
    const char *getFamily();
    double getSize();
    int getWeight();
    int getItalic();
    int getStretch();
    Color getColor();
    int getUnderline();
    int getUnderlineColor(Color *c);
    UiOpenTypeFeatures *getOTFeatures();

    static UiFontAttribute *newFamily(const char *family);
    static UiFontAttribute *newSize(double size);
    static UiFontAttribute *newWeight(int weightAttribute);
    static UiFontAttribute *newItalic(int italicAttribute);
    static UiFontAttribute *newStretch(int stretchAttribute);
    static UiFontAttribute *newColor(Color c);
    static UiFontAttribute *newBackground(Color c);
    static UiFontAttribute *newUnderline(int underlineAttr);
    static UiFontAttribute *newUnderlineColor(int underlineColorAttr, Color c);
    static UiFontAttribute *newOTFeatures(UiOpenTypeFeatures *otf);
};


class UiAttributedString {
    UiAttributedString(const char *str);
    void free();
    const char * toString();
    size_t toStringLen();

    void appendUnattributed(const char *str);
    void insertUnattributed(const char *str, size_t at);
    void deleteString(size_t start, size_t end);
    void setAttribute(UiFontAttribute *attr, size_t start, size_t end);

    //TODO overloaded in javascript?
    void appendAttributed(const char *str, UiFontAttribute *attr);
    void appendAttributed(const char *str, UiFontAttribute *attr, UiFontAttribute *attr2);

    void forEach(nbind::cbFunction& cb);

    size_t numGraphemes();
    size_t byteIndexToGrapheme(size_t pos);
    size_t graphemeToByteIndex(size_t pos);
};

class UiFontDescriptor {
    UiFontDescriptor(const char *family, double size, int weight, int italic, int stretch);
    void free();
    char *getFamily();
    double getSize();
    int getWeight();
    int getItalic();
    int getStretch();
    uiFontDescriptor *getHandle();
};

class UiFontButton : public UiControl {
  UiFontButton();
  UiFontDescriptor* getFont();
  // onChanged, default button
};


class DrawTextLayout {
 public:
  DrawTextLayout(UiAttributedString *s, UiFontDescriptor *defaultFont, double width, int align);
  void free();
  SizeDouble getExtents();
  uiDrawTextLayout* getHandle();
};
```

for drawing: see Area: `UiDrawContext.text`


```js
libui.textWeight = {
    minimum: 0,
    thin: 100,
    ultraLight: 200,
    light: 300,
    book: 350,
    normal: 400,
    medium: 500,
    semiBold: 600,
    bold: 700,
    ultraBold: 800,
    heavy: 900,
    ultraHeavy: 950,
    maximum: 1000
};

libui.textItalic = {
    normal: 0,
    oblique: 1,
    italic: 2
};

libui.textStretch = {
    ultraCondensed: 0,
    extraCondensed: 1,
    condensed: 2,
    semiCondensed: 3,
    normal: 4,
    semiExpanded: 5,
    expanded: 6,
    extraExpanded: 7,
    ultraExpanded: 8
};

libui.textAttributeType = {
    family: 0,
    size: 1,
    weight: 2,
    italic: 3,
    stretch: 4,
    color: 5,
    background: 6,
    underline: 7,
    underlineColor: 8,
    features: 9
};

libui.textUnderline = {
    none: 0,
    single: 1,
    double: 2,
    suggestion: 3
};

libui.textUnderlineColor = {
    custom: 0,
    spelling: 1,
    grammar: 2,
    auxiliary: 3
};

libui.textAlign = {
    left: 0,
    center: 1,
    right: 2
};

libui.forEach = {
    continue: 0,
    stop: 1
};
```