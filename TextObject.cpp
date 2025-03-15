#include "src/TextObject.h"

TextObject::TextObject(uint32_t id, int x, int y, bool isDisplayed, const string &text, FontType fontType, int fontSize, COLORREF color)
    : Object(x, y, isDisplayed, id), text(text), fontType(fontType), fontSize(fontSize), color(color) {}


// 设置行间距
void TextObject::setLineSpacing(int spacing) {
    this->lineSpacing = spacing;
}

// 获取当前行间距
int TextObject::getLineSpacing() const {
    return this->lineSpacing;
}

int TextObject::getHeight() {
    this->setFont();
    std::string currentText = this->text;
    int totalHeight = 0;
    size_t pos = 0;
    std::string line;
    int lineCount = 0;

    // 计算总高度
    while ((pos = currentText.find('\n')) != std::string::npos) {
        line = currentText.substr(0, pos);
        totalHeight += textheight(_T(line.c_str()));
        currentText.erase(0, pos + 1);
        lineCount++;
    }

    // 最后一行或无换行符情况
    if (!currentText.empty()) {
        totalHeight += textheight(_T(currentText.c_str()));
        lineCount++;
    }

    // 如果没有换行符，总高度可能为0，确保至少有一行高度
    if (totalHeight == 0) {
        totalHeight = textheight(_T(this->text.c_str()));
    }

    // 添加行间距（行数-1）* 行间距
    if (lineCount > 1) {
        totalHeight += (lineCount - 1) * this->lineSpacing;
    }

    return totalHeight;
}

string TextObject::getText() {
    return this->text;
}

int TextObject::getWidth() {
    this->setFont();
    std::string currentText = this->text;
    int maxWidth = 0;
    size_t pos = 0;
    std::string line;

    // 计算最大宽度
    while ((pos = currentText.find('\n')) != std::string::npos) {
        line = currentText.substr(0, pos);
        int lineWidth = textwidth(_T(line.c_str()));
        maxWidth = std::max(maxWidth, lineWidth);
        currentText.erase(0, pos + 1);
    }

    // 最后一行或无换行符情况
    if (!currentText.empty()) {
        int lineWidth = textwidth(_T(currentText.c_str()));
        maxWidth = std::max(maxWidth, lineWidth);
    }

    // 如果没有换行符，使用原始方法
    if (maxWidth == 0) {
        maxWidth = textwidth(_T(this->text.c_str()));
    }

    return maxWidth;
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
    // cout << path->second.fontPath.c_str() << endl;
    AddFontResourceEx(path->second.fontPath.c_str(), FR_PRIVATE, 0);
    settextstyle(this->fontSize * scaleFactor, 0, _T(path->second.fontName.c_str()));
}

bool TextObject::isOverlapping(int x, int y) {
    // 处理多行文本的重叠检测
    std::string currentText = this->text;
    int currentY = this->y * scaleFactor;
    int maxWidth = 0;
    int totalHeight = 0;
    size_t pos = 0;
    std::string line;
    int lineCount = 0;

    // 计算最大宽度和总高度
    while ((pos = currentText.find('\n')) != std::string::npos) {
        line = currentText.substr(0, pos);
        int lineWidth = textwidth(_T(line.c_str()));
        maxWidth = std::max(maxWidth, lineWidth);
        int lineHeight = textheight(_T(line.c_str()));
        totalHeight += lineHeight;
        currentText.erase(0, pos + 1);
        lineCount++;
    }

    // 最后一行或无换行符情况
    if (!currentText.empty()) {
        int lineWidth = textwidth(_T(currentText.c_str()));
        maxWidth = std::max(maxWidth, lineWidth);
        totalHeight += textheight(_T(currentText.c_str()));
        lineCount++;
    }

    // 如果没有换行符，总高度可能为0，确保至少有一行高度
    if (totalHeight == 0) {
        totalHeight = textheight(_T(this->text.c_str()));
    }

    // 添加行间距（行数-1）* 行间距
    if (lineCount > 1) {
        totalHeight += (lineCount - 1) * this->lineSpacing * scaleFactor;
    }

    return (x >= this->x * scaleFactor && x <= (this->x * scaleFactor + maxWidth) &&
            y >= this->y * scaleFactor && y <= (this->y * scaleFactor + totalHeight));
}

void TextObject::render() {
    if (this->isDisplayed) {
        setFont();
        setbkmode(TRANSPARENT);
        settextcolor(this->color);

        // 处理多行文本
        std::string currentText = this->text;
        int currentY = this->y * scaleFactor;
        size_t pos = 0;
        std::string line;

        while ((pos = currentText.find('\n')) != std::string::npos) {
            line = currentText.substr(0, pos);
            outtextxy(this->x * scaleFactor, currentY, line.c_str());
            currentText.erase(0, pos + 1); // 删除已处理的行和换行符

            // 增加Y坐标，移到下一行（添加行间距）
            currentY += textheight(_T(line.c_str())) + (this->lineSpacing * scaleFactor);
        }

        // 打印最后一行或没有换行符的情况
        if (!currentText.empty()) {
            outtextxy(this->x * scaleFactor, currentY, currentText.c_str());
        }
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
    {FONT_KURLAND, {"Kurland", "fonts/Kurland.ttf"}},
    {FONT_PIXEL, {"Pixel Square", "fonts/Pixel-Square-10-1.ttf"}},
    {FONT_VISITOR1, {"Visitor TT1 BRK", "fonts/visitor1.ttf"}},
    {FONT_WXZ, {"王羲之书法字体", "fonts/王羲之书法字体.ttf"}},
    {FONT_DIGIT, {"04b_21", "fonts/digit.ttf"}}
};
