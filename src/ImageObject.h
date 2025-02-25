#ifndef IMAGEOBJECT_H
#define IMAGEOBJECT_H

#include <graphics.h>
#include <bits/stdc++.h>
#include <conio.h>

#include "Object.h"
#include "windowCfg.h"  // 确保包含了 scaleFactor 定义

class ImageObject : public Object {
public:
    ImageObject(uint32_t id, int x, int y, bool isDisplayed, IMAGE* img, IMAGE* mask);
    void render() override;
    void handleMouseEvent(const MOUSEMSG &msg, std::string *result) override;

private:
    IMAGE* img;
    IMAGE* mask;

    bool isOverlapping(int x, int y) const;
};

#endif // IMAGEOBJECT_H
