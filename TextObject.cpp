#include "src/TextObject.h"

TextObject::TextObject(uint32_t id, int x, int y, bool isDisplayed, const string &text, FontType fontType, int fontSize, COLORREF color)
    : Object(x, y, isDisplayed, id), text(text), fontType(fontType), fontSize(fontSize), color(color) {}

int TextObject::getHeight() {
    return 1.0 * textheight(_T(this->text.c_str()));
}

int TextObject::getWidth() {
    return 1.0 * textwidth(_T(this->text.c_str()));
}

void TextObject::setFontSize(int size) {
    this->fontSize = size;
}

void TextObject::addFontSize(int add) {
    this->fontSize += add * scaleFactor;
}

void TextObject::resetFontSize() {
    this->fontSize = fontSize;
}

void TextObject::setText(string text) {
    this->text = text;
}

void TextObject::setFont() {
    auto path = fontPath.find(this->fontType);
    AddFontResourceEx(path->second.fontPath.c_str(), FR_PRIVATE, 0);
    settextstyle(this->fontSize * scaleFactor, 0, _T(path->second.fontName.c_str()));
}

bool TextObject::isOverlapping(int x, int y) {
    int textWidth = textwidth(_T(this->text.c_str()));
    int textHeight = textheight(_T(this->text.c_str()));

    return (x >= this->x * scaleFactor && x <= (this->x * scaleFactor + textWidth) &&
            y >= this->y * scaleFactor && y <= (this->y * scaleFactor + textHeight));
}

void TextObject::render() {
    if (this->isDisplayed) {
        setFont();
        setbkmode(TRANSPARENT);
        settextcolor(this->color);
        outtextxy(this->x * scaleFactor, this->y * scaleFactor, this->text.c_str());
    }
}

void TextObject::handleMouseEvent(const MOUSEMSG &msg, string *result) {
    if (msg.uMsg == WM_MOUSEMOVE) {
        int mouseX = msg.x;
        int mouseY = msg.y;

        if (isOverlapping(mouseX, mouseY)) {
            if (!this->isOverLapped) {
                *result = to_string(this->id) + "Show";
            }
            this->isOverLapped = true;
        } else {
            if (this->isOverLapped) {
                *result = to_string(this->id) + "Hide";
            }
            this->isOverLapped = false;
        }
    }

    if (msg.uMsg == WM_LBUTTONDOWN) {
        if (this->isOverLapped) {
            this->isClicked = true;
        }
    }
    if (msg.uMsg == WM_LBUTTONUP) {
        if (this->isClicked) {
            this->isClicked = false;
        }
    }
}

// 字体路径映射
const map<TextObject::FontType, TextObject::FontInfo> TextObject::fontPath = {
    {FONT_KURLAND, {"KURLAND", "fonts/Kurland.ttf"}},
    {FONT_PIXEL, {"PIXEL", "fonts/Pixel-Square-10-1.ttf"}},
    {FONT_VISITOR1, {"VISITOR", "fonts/visitor1.ttf"}}
};
