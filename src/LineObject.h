#ifndef LINEOBJECT_H
#define LINEOBJECT_H

#include "Object.h"
#include "Timer.h"
#include "windowCfg.h"
#include <graphics.h>
#include <math.h>

class LineObject : public Object {
public:
    LineObject(uint32_t id, double x, double y, bool isDisplayed, int length, double angle, COLORREF color, int lineWidth);

    void render() override;
    void update(double frameTime);
    void setLength(int newLength);
    void setColor(COLORREF newColor);
    void setLineWidth(int newLineWidth);
    Point getEnd();

private:
    int length; // 直线长度
    COLORREF color; // 直线颜色
    int lineWidth; // 线条粗细

    double angle;
};

#endif // LINEOBJECT_H
