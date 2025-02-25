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
    AnimationObject(uint32_t id, int x, int y, bool isDisplayed, IMAGE* img, IMAGE* mask, const std::vector<FrameInfo>& frames, double frameDuration);

    void render() override;
    void update() override;
    void setFrameOrder(const std::vector<int>& newFrameOrder);
    void setFrameDuration(double newFrameDuration);

private:
    IMAGE* img;
    IMAGE* mask;
    std::vector<FrameInfo> frames;
    std::vector<int> frameOrder; // 顺序播放的帧索引数组
    double frameDuration; // Duration of each frame in seconds
    int currentFrame;
    Timer timer;
    int pivotX;
    int pivotY;
};

#endif // ANIMATIONOBJECT_H
