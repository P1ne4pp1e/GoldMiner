#ifndef IMAGEOBJECT_H
#define IMAGEOBJECT_H

#include <bits/stdc++.h>
#include <conio.h>
#include <graphics.h>

#include "Object.h"
#include "windowCfg.h"

using namespace std;

class ImageObject : public Object {
public:
    ImageObject(uint32_t id, int x, int y, bool isDisplayed, IMAGE* img, IMAGE* mask)
        : Object(x, y, isDisplayed, id), img(img), mask(mask) {}

    void render() override {
        if (this->isDisplayed) {
            putimage(this->x * scaleFactor, this->y * scaleFactor, mask, SRCAND);
            putimage(this->x * scaleFactor, this->y * scaleFactor, img, SRCPAINT);

        }
    }

    void handleMouseEvent(const MOUSEMSG &msg, string *result) override {
        int mouseX = msg.x;
        int mouseY = msg.y;
    }

private:
    IMAGE* img;
    IMAGE* mask;

    bool isOverlapping(int x, int y) const {
        int imgWidth = (*img).getwidth() * scaleFactor;
        int imgHeight = (*img).getheight() * scaleFactor;

        return (x >= this->x * scaleFactor && x <= (this->x * scaleFactor + imgWidth) &&
                y >= this->y * scaleFactor && y <= (this->y * scaleFactor + imgHeight));
    }
};

#endif