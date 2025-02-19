#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include <bits/stdc++.h>
#include <conio.h>
#include <graphics.h>

#include "Object.h"
#include "windowCfg.h"

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

    TextObject(uint32_t id, int x, int y, bool isDisplayed, const string &text, FontType fontType, int fontSize, COLORREF color)
        : Object(x, y, isDisplayed, id), text(text), fontType(fontType), fontSize(fontSize), color(color) {
    };

    int getHeight() { return 1.0 * textheight(_T(this->text.c_str())); }
    int getWidth() { return 1.0 * textwidth(_T(this->text.c_str())); }

    void setFontSize(int size) {
        this->fontSize = size;
    }

    void addFontSize(int add) {
        this->fontSize += add * scaleFactor;
    }

    void resetFontSize() {
        this->fontSize = fontSize;
    }

    void setText(string text) {
        this->text = text;
    }

    void setFont() {
        auto path = fontPath.find(this->fontType);
        AddFontResourceEx(path->second.fontPath.c_str(), FR_PRIVATE, 0);
        settextstyle(this->fontSize * scaleFactor, 0, _T(path->second.fontName.c_str()));
    }

    bool isOverlapping(int x, int y) {
        int textWidth = textwidth(_T(this->text.c_str()));
        int textHeight = textheight(_T(this->text.c_str()));

        return (x >= this->x * scaleFactor && x <= (this->x * scaleFactor + textWidth) &&
                y >= this->y * scaleFactor && y <= (this->y * scaleFactor + textHeight));
    }

    void render() override {
        if (this->isDisplayed) {
            setFont();
            setbkmode(TRANSPARENT);
            settextcolor(this->color);
            outtextxy(this->x * scaleFactor, this->y * scaleFactor, this->text.c_str());
        }
    }

    void handleMouseEvent(const MOUSEMSG &msg, string *result) override {
        if (msg.uMsg == WM_MOUSEMOVE) {
            int mouseX = msg.x;
            int mouseY = msg.y;

            if (isOverlapping(mouseX, mouseY)) {
                // cout << "Mouse is over the text: " << this->text << endl;
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

private:
    string text;
    FontType fontType;
    int fontSize;
    COLORREF color;

    // 字体路径映射
    static const map<FontType, FontInfo> fontPath;
};

const map<TextObject::FontType, TextObject::FontInfo> TextObject::fontPath = {
    {FONT_KURLAND, {"KURLAND", "fonts/Kurland.ttf"}},
    {FONT_PIXEL, {"PIXEL", "fonts/Pixel-Square-10-1.ttf"}},
    {FONT_VISITOR1, {"VISITOR", "fonts/visitor1.ttf"}}
};


#endif