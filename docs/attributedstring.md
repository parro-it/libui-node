# AttributedString

```cpp
class OpenTypeFeatures {
  public:
    OpenTypeFeatures();
    void free();

    static OpenTypeFeatures clone(OpenTypeFeatures *f2);
    void add(const char *tag, uint32_t value);
    void remove(const char *tag);

    // value or `null` if not set
    get(const char *tag);

    // cb(OpenTypeFeatures, tag, value)
    void forEach(nbind::cbFunction& cb);
};

class FontAttribute {
  public:
    // doesn't need to be called when appended
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
    OpenTypeFeatures *getOTFeatures();

    static FontAttribute newFamily(const char *family);
    static FontAttribute newSize(double size);
    static FontAttribute newWeight(int weightAttribute);
    static FontAttribute newItalic(int italicAttribute);
    static FontAttribute newStretch(int stretchAttribute);
    static FontAttribute newColor(Color c);
    static FontAttribute newBackground(Color c);
    static FontAttribute newUnderline(int underlineAttr);
    static FontAttribute newUnderlineColor(int underlineColorAttr, Color c);
    static FontAttribute newOTFeatures(OpenTypeFeatures *otf);
};


class AttributedString {
    AttributedString(const char *str);
    void free();
    const char * toString();
    size_t toStringLen();

    void appendUnattributed(const char *str);
    void insertUnattributed(const char *str, size_t at);
    void deleteString(size_t start, size_t end);
    void setAttribute(FontAttribute *attr, size_t start, size_t end);

    void appendAttributed(const char *str, FontAttribute *attr);
    void appendAttributed(const char *str, FontAttribute *attr, FontAttribute *attr2);

    void forEach(nbind::cbFunction& cb);

    size_t numGraphemes();
    size_t byteIndexToGrapheme(size_t pos);
    size_t graphemeToByteIndex(size_t pos);
};

class FontDescriptor {
    FontDescriptor(const char *family, double size, int weight, int italic, int stretch);
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
  FontDescriptor getFont();
  // onChanged, default button
};


class DrawTextLayout {
 public:
  DrawTextLayout(AttributedString *s, FontDescriptor *defaultFont, double width, int align);
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