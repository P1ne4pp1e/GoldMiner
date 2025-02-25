#ifndef TRIANGLEOBJECT_H
#define TRIANGLEOBJECT_H

#include "Object.h"
#include "windowCfg.h"
#include <utility> // For std::pair
#include <string>

using namespace std;

class TriangleObject : public Object {
public:
    TriangleObject(uint32_t id, std::pair<int, int> pt1, std::pair<int, int> pt2, std::pair<int, int> pt3, bool isDisplayed, COLORREF color);

    void render() override;
    void handleMouseEvent(const MOUSEMSG &msg, string *result) override;

private:
    pair<int, int> pt1;
    pair<int, int> pt2;
    pair<int, int> pt3;
    COLORREF color;

    bool isOverlapping(int x, int y) const;
};

#endif // TRIANGLEOBJECT_H
