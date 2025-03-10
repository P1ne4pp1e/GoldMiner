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
        FONT_VISITOR1,
        FONT_WXZ,
        FONT_DIGIT
    };

    TextObject(uint32_t id, int x, int y, bool isDisplayed, const string &text, FontType fontType, int fontSize, COLORREF color);

    int getHeight();
    int getWidth();


    void setLineSpacing(int spacing); // 新增：设置行间距
    int getLineSpacing() const; // 新增：获取行间距

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
    int lineSpacing = 0; // 新增：行间距属性，默认为0

    static const map<FontType, FontInfo> fontPath;
};

#endif // TEXTOBJECT_H
