#include "src/AnimationObject.h"

AnimationObject::AnimationObject(uint32_t id, int x, int y, bool isDisplayed, IMAGE* img, IMAGE* mask, const std::vector<FrameInfo>& frames, double frameDuration)
    : Object(x, y, isDisplayed, id), img(img), mask(mask), frames(frames), frameDuration(frameDuration), currentFrame(0) {
    this->timer.start();
}

void AnimationObject::render() {
    if (this->isDisplayed && !this->frameOrder.empty()) {
        // 获取当前帧信息
        const auto& [dstWidth, dstHeight, srcX, srcY] = this->frames[this->frameOrder[this->currentFrame]];

        // 计算缩放后的宽度和高度
        int scaledDstWidth = (1.0 * dstWidth + (1.0 * dstWidth / 2 - this->pivotX) * 2) * scaleFactor;
        int scaledDstHeight = (1.0 * dstHeight + (1.0 * dstHeight / 2 - this->pivotY) * 2) * scaleFactor;

        if (this->angle == 0.0) {
            // 显示当前帧
            putimage(this->x * scaleFactor, this->y * scaleFactor, dstWidth * scaleFactor, dstHeight * scaleFactor, this->mask, srcX * scaleFactor, srcY * scaleFactor, SRCAND);
            putimage(this->x * scaleFactor, this->y * scaleFactor, dstWidth * scaleFactor, dstHeight * scaleFactor, this->img, srcX * scaleFactor, srcY * scaleFactor, SRCPAINT);
        } else {
            IMAGE tempImage(scaledDstWidth, scaledDstHeight);
            IMAGE tempMask(scaledDstWidth, scaledDstHeight);

            IMAGE showImage;
            IMAGE showMask;

            SetWorkingImage(&tempMask);
            setfillcolor(WHITE);
            solidrectangle(0, 0, scaledDstWidth, scaledDstHeight);
            putimage(1.0 * (1.0 * dstWidth / 2 - 1.0 * this->pivotX) * 2 * scaleFactor, 1.0 * (1.0 * dstHeight / 2 - 1.0 * this->pivotY) * 2 * scaleFactor, scaledDstWidth, scaledDstHeight, this->mask, srcX * scaleFactor, srcY * scaleFactor);

            SetWorkingImage(&tempImage);
            cleardevice();
            putimage(1.0 * (1.0 * dstWidth / 2 - 1.0 * this->pivotX) * 2 * scaleFactor, 1.0 * (1.0 * dstHeight / 2 - 1.0 * this->pivotY) * 2 * scaleFactor, scaledDstWidth, scaledDstHeight, this->img, srcX * scaleFactor, srcY * scaleFactor);

            SetWorkingImage();

            rotateimage(&showImage, &tempImage, this->angle * (PI / 180.0), BLACK, true);
            rotateimage(&showMask, &tempMask, this->angle * (PI / 180.0), WHITE, true);

            // 调整位置以考虑旋转中心
            int newX = 1.0 * (1.0 * this->x + 1.0 * this->pivotX) * scaleFactor - 1.0 * showImage.getwidth() / 2;
            int newY = 1.0 * (1.0 * this->y + 1.0 * this->pivotY) * scaleFactor - 1.0 * showImage.getheight() / 2;

            putimage(newX, newY, &showMask, SRCAND);
            putimage(newX, newY, &showImage, SRCPAINT);
        }
    }
}

void AnimationObject::update() {
    if (this->timer.elapsed() >= this->frameDuration && !this->frameOrder.empty()) {
        this->currentFrame = (this->currentFrame + 1) % this->frameOrder.size();
        this->timer.reset();
    }
}

void AnimationObject::setFrameOrder(const std::vector<int>& newFrameOrder) {
    this->frameOrder = newFrameOrder;
    this->currentFrame = 0; // 重置当前帧索引
}

void AnimationObject::setFrameDuration(double newFrameDuration) {
    this->frameDuration = newFrameDuration;
}

void AnimationObject::setPivot(double X, double Y) {
    this->pivotX = X;
    this->pivotY = Y;
}