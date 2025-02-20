#ifndef ANIMATIONOBJECT_H
#define ANIMATIONOBJECT_H

#include "Object.h"
#include "Timer.h"
#include "FrameInfo.h"
#include "windowCfg.h"  // 确保包含了 scaleFactor 定义
#include <graphics.h>
#include <math.h>
#include <vector>

const double PI = 3.141592653589793;

class AnimationObject : public Object {
public:
    AnimationObject(uint32_t id, int x, int y, bool isDisplayed, IMAGE* img, IMAGE* mask, const std::vector<FrameInfo>& frames, double frameDuration)
        : Object(x, y, isDisplayed, id), img(img), mask(mask), frames(frames), frameDuration(frameDuration), currentFrame(0) {
        this->timer.start();
    }

    void render() override {
        if (this->isDisplayed && !this->frameOrder.empty()) {
            // 获取当前帧信息
            const auto& [dstWidth, dstHeight, srcX, srcY] = this->frames[this->frameOrder[this->currentFrame]];

            // 计算缩放后的宽度和高度
            int scaledDstWidth = dstWidth * scaleFactor;
            int scaledDstHeight = dstHeight * scaleFactor;

            if (this->angle == 0.0) {
                // 显示当前帧
                putimage(this->x * scaleFactor, this->y * scaleFactor, scaledDstWidth, scaledDstHeight, this->mask, srcX * scaleFactor, srcY * scaleFactor, SRCAND);
                putimage(this->x * scaleFactor, this->y * scaleFactor, scaledDstWidth, scaledDstHeight, this->img, srcX * scaleFactor, srcY * scaleFactor, SRCPAINT);
            } else {
                // static IMAGE tempImage(320*3, 240*3);
                IMAGE tempImage(scaledDstWidth, scaledDstHeight);
                IMAGE tempMask(scaledDstWidth, scaledDstHeight);

                IMAGE showImage;
                IMAGE showMask;

                SetWorkingImage(&tempMask);
                putimage(0, 0, scaledDstWidth, scaledDstHeight, this->mask, srcX * scaleFactor, srcY * scaleFactor);


                SetWorkingImage(&tempImage);
                cleardevice();
                putimage(0, 0, scaledDstWidth, scaledDstHeight, this->img, srcX * scaleFactor, srcY * scaleFactor);

                SetWorkingImage();


                rotateimage(&showImage, &tempImage, this->angle * (PI / 180.0), BLACK, true);
                rotateimage(&showMask, &tempMask, this->angle * (PI / 180.0), WHITE, true);

                putimage(this->x * scaleFactor, this->y * scaleFactor, &showMask, SRCAND);
                putimage(this->x * scaleFactor, this->y * scaleFactor, &showImage, SRCPAINT);

            }
        }
    }

    void update() override {
        if (this->timer.elapsed() >= this->frameDuration && !this->frameOrder.empty()) {
            this->currentFrame = (this->currentFrame + 1) % this->frameOrder.size();
            this->timer.reset();
        }
    }

    void setFrameOrder(const std::vector<int>& newFrameOrder) {
        this->frameOrder = newFrameOrder;
        this->currentFrame = 0; // 重置当前帧索引
    }

    void setFrameDuration(double newFrameDuration) {
        this->frameDuration = newFrameDuration;
    }

private:
    IMAGE* img;
    IMAGE* mask;
    std::vector<FrameInfo> frames;
    std::vector<int> frameOrder; // 顺序播放的帧索引数组
    double frameDuration; // Duration of each frame in seconds
    int currentFrame;
    Timer timer;
};

#endif // ANIMATIONOBJECT_H
