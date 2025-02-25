#include "src/ImageObject.h"

ImageObject::ImageObject(uint32_t id, int x, int y, bool isDisplayed, IMAGE* img, IMAGE* mask)
    : Object(x, y, isDisplayed, id), img(img), mask(mask) {}

void ImageObject::render() {
    if (this->isDisplayed) {
        putimage(this->x * scaleFactor, this->y * scaleFactor, mask, SRCAND);
        putimage(this->x * scaleFactor, this->y * scaleFactor, img, SRCPAINT);
    }
}

void ImageObject::handleMouseEvent(const MOUSEMSG &msg, std::string *result) {
    int mouseX = msg.x;
    int mouseY = msg.y;
}

bool ImageObject::isOverlapping(int x, int y) const {
    int imgWidth = (*img).getwidth() * scaleFactor;
    int imgHeight = (*img).getheight() * scaleFactor;

    return (x >= this->x * scaleFactor && x <= (this->x * scaleFactor + imgWidth) &&
            y >= this->y * scaleFactor && y <= (this->y * scaleFactor + imgHeight));
}
