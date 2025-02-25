#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include "Object.h"
#include "windowCfg.h"
#include <string>
#include <map>

using namespace std;

class TextObject : public Object {
public:
    struct FontInfo {
        string fontName;
        string fontPath;
    };

    enum FontType {
        FONT_KURLAND,
        FONT_PIXEL,
        FONT_VISITOR1
    };

    TextObject(uint32_t id, int x, int y, bool isDisplayed, const string &text, FontType fontType, int fontSize, COLORREF color);

    int getHeight();
    int getWidth();

    void setFontSize(int size);
    void addFontSize(int add);
    void resetFontSize();
    void setText(string text);
    void setFont();
    bool isOverlapping(int x, int y);

    void render() override;
    void handleMouseEvent(const MOUSEMSG &msg, string *result) override;

private:
    string text;
    FontType fontType;
    int fontSize;
    COLORREF color;

    static const map<FontType, FontInfo> fontPath;
};

#endif // TEXTOBJECT_H
