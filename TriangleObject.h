#ifndef TRIANGLEOBJECT_H
#define TRIANGLEOBJECT_H

#include "Object.h"
#include "windowCfg.h"

using namespace std;

class TriangleObject : public Object {
public:
    TriangleObject(uint32_t id, std::pair<int, int> pt1, std::pair<int, int> pt2, std::pair<int, int> pt3, bool isDisplayed,
                   COLORREF color)
        : Object((pt1.first + pt2.first + pt3.first) / 3, (pt1.second + pt2.second + pt3.second) / 3, isDisplayed, id),
          pt1(pt1), pt2(pt2), pt3(pt3), color(color) {
    }

    void render() override {
        if (this->isDisplayed) {
            // 获取三角形的三个顶点
            int x1 = this->pt1.first * scaleFactor;
            int y1 = this->pt1.second * scaleFactor;
            int x2 = this->pt2.first * scaleFactor;
            int y2 = this->pt2.second * scaleFactor;
            int x3 = this->pt3.first * scaleFactor;
            int y3 = this->pt3.second * scaleFactor;

            // 设置填充颜色
            setfillcolor(this->color);

            // 绘制三角形
            POINT points[] = {{x1, y1}, {x2, y2}, {x3, y3}};
            fillpolygon(points, 3);
        }
    }

    void handleMouseEvent(const MOUSEMSG &msg, string *result) override {
        if (msg.uMsg == WM_MOUSEMOVE) {
            int mouseX = msg.x;
            int mouseY = msg.y;

            if (isOverlapping(mouseX, mouseY)) {
                cout << "Mouse is over the triangle" << endl;
                *result = "OverLapped";
            }
        }
    }

private:
    pair<int, int> pt1;
    pair<int, int> pt2;
    pair<int, int> pt3;
    COLORREF color;

    bool isOverlapping(int x, int y) const {
        int x1 = this->pt1.first * scaleFactor;
        int y1 = this->pt1.second * scaleFactor;
        int x2 = this->pt2.first * scaleFactor;
        int y2 = this->pt2.second * scaleFactor;
        int x3 = this->pt3.first * scaleFactor;
        int y3 = this->pt3.second * scaleFactor;

        // 使用重心法判断点是否在三角形内
        int d1 = (x - x1) * (y2 - y1) - (x2 - x1) * (y - y1);
        int d2 = (x - x2) * (y3 - y2) - (x3 - x2) * (y - y2);
        int d3 = (x - x3) * (y1 - y3) - (x1 - x3) * (y - y3);

        bool hasNeg = (d1 < 0) || (d2 < 0) || (d3 < 0);
        bool hasPos = (d1 > 0) || (d2 > 0) || (d3 > 0);

        return !(hasNeg && hasPos);
    }
};


#endif