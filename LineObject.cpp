#include "src/LineObject.h"

LineObject::LineObject(uint32_t id, double x, double y, bool isDisplayed, int length, double angle, COLORREF color, int lineWidth)
    : Object(x, y, isDisplayed, id), length(length), angle(angle), color(color), lineWidth(lineWidth) {
}

void LineObject::render() {
    if (this->isDisplayed) {
        // 计算终点坐标
        double endX = static_cast<int>(this->x + this->length * cos(1.0 * this->angle * M_PI / 180));
        double endY = static_cast<int>(this->y + this->length * sin(1.0 * this->angle * M_PI / 180));

        // 设置绘制颜色
        setcolor(this->color);

        // 设置线条粗细
        setlinestyle(PS_SOLID, this->lineWidth);

        // 绘制直线
        line(this->x * scaleFactor, this->y * scaleFactor, endX * scaleFactor, endY * scaleFactor);
    }
}

void LineObject::update(double frameTime) {
    // 更新角度，考虑到 fps 和角速度
    this->angle += this->angularVelocity * frameTime;
    if (this->angle > 360) {
        this->angle -= 360; // 保持角度在 0 到 2π 之间
    } else if (this->angle < 0) {
        this->angle += 360; // 保持角度在 0 到 2π 之间
    }
}

void LineObject::setLength(int newLength) {
    this->length = newLength;
}

void LineObject::setColor(COLORREF newColor) {
    this->color = newColor;
}

void LineObject::setLineWidth(int newLineWidth) {
    this->lineWidth = newLineWidth;
}

Object::Point LineObject::getEnd() {
    double endX = static_cast<int>(this->x + this->length * cos(1.0 * this->angle * M_PI / 180));
    double endY = static_cast<int>(this->y + this->length * sin(1.0 * this->angle * M_PI / 180));
    Point p(endX, endY);
    return p;
}
