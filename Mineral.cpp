#include "src/Mineral.h"
#include "src/MineralCfg.h"
#include "src/levelCfg.h"

Mineral::Mineral(uint32_t id, int x, int y, bool isDisplayed, MineralType type, IMAGE* img, IMAGE* mask)
    : Object(x, y, isDisplayed, id), type(type), img(img), mask(mask), hooked(false) {

    // 从配置中加载属性
    const auto& config = MINERAL_CONFIGS.at(type);
    value = config.value;
    mass = config.mass;
    radius = config.radius;
}

void Mineral::render() {
    if (this->isDisplayed) {
        if (this->hooked) {
            // 如果被钩子抓住，根据钩子角度旋转渲染
            // 使用旋转图像的方法（和AnimationObject类似）
            IMAGE tempImage(this->img->getwidth(), this->img->getheight());
            IMAGE tempMask(this->mask->getwidth(), this->mask->getheight());

            IMAGE showImage;
            IMAGE showMask;

            SetWorkingImage(&tempMask);
            setfillcolor(WHITE);
            solidrectangle(0, 0, this->mask->getwidth(), this->mask->getheight());
            putimage(0, 0, this->mask);

            SetWorkingImage(&tempImage);
            cleardevice();
            putimage(0, 0, this->img);

            SetWorkingImage();

            // 根据钩子角度旋转
            double angle = rope.getAngle(); // 从钩子获取角度
            angle = 90 - angle;
            if (angle < 0) {
                angle += 360;
            }
            rotateimage(&showImage, &tempImage, angle * (PI / 180.0), BLACK, true);
            rotateimage(&showMask, &tempMask, angle * (PI / 180.0), WHITE, true);
            cout << "Mineral.cpp: void Mineral::render() " << "rope_angle: " << rope.getAngle() << endl;
            cout << "Mineral.cpp: void Mineral::render() " << "angle: " << angle << endl;

            // 渲染在钩子位置
            Point hookPos = rope.getLengthPoint(rope.getLength() - 1 + showImage.getwidth() / scaleFactor / 2);
            int newX = hookPos.x * scaleFactor - showImage.getwidth() / 2;
            int newY = hookPos.y * scaleFactor - showImage.getheight() / 2;

            putimage(newX, newY, &showMask, SRCAND);
            putimage(newX, newY, &showImage, SRCPAINT);
        } else {
            // if (this->type == 1) {
            //     cout << this->mask->getwidth() << " " << this->mask->getheight() << endl;
            //     cout << this->img->getwidth() << " " << this->img->getheight() << endl;
            // }
            // 普通渲染
            putimage(this->x * scaleFactor, this->y * scaleFactor, this->mask, SRCAND);
            putimage(this->x * scaleFactor, this->y * scaleFactor, this->img, SRCPAINT);
            // circle(getCenter().x * scaleFactor, getCenter().y * scaleFactor, 3);
        }
    }
}

void Mineral::update() {
    // 基础矿物不需要特殊更新逻辑
}

bool Mineral::isHooked() const {
    return hooked;
}

void Mineral::setHooked(bool newHooked) {
    hooked = newHooked;
}

int Mineral::getValue() const {
    return value;
}

int Mineral::getMass() const {
    return mass;
}

double Mineral::getRadius() const {
    return radius;
}

Object::Point Mineral::getCenter() const {
    Point p(this->x + this->img->getwidth()/scaleFactor/2, this->y + this->img->getheight()/scaleFactor/2);
    // Point p(this->x, this->y);
    return p;
}

Mineral::MineralType Mineral::getType() const {
    return type;
}

void Mineral::onHooked() {
    // 默认实现：设置为被抓住状态
    this->hooked = true;
}

void Mineral::onCollected() {
    // 默认实现：只有基本得分逻辑
}

MovingMineral::MovingMineral(uint32_t id, int x, int y, bool isDisplayed, MineralType type,
                           IMAGE* img, IMAGE* mask, const std::vector<FrameInfo>& frames, double frameDuration)
    : Mineral(id, x, y, isDisplayed, type, img, mask),
      animation(id + 0x10000, x, y, isDisplayed, img, mask, frames, frameDuration),
      moveRange(100), speed(0.5), direction(1), startX(x) {
}

void MovingMineral::update() {
    if (this->hooked) {
        // 如果被抓住，不需要移动
        return;
    }

    // 移动逻辑
    this->x += direction * speed;

    // 检查边界，改变方向
    if (this->x >= startX + moveRange) {
        direction = -1;
    } else if (this->x <= startX) {
        direction = 1;
    }

    // 更新动画位置和状态
    animation.setX(this->x);
    animation.setY(this->y);
    animation.update();
}

void MovingMineral::render() {
    if (this->isDisplayed) {
        if (this->hooked) {
            // 如果被抓住，使用特殊渲染
            // 类似于基类的hooked渲染，但使用动画
            // ...
        } else {
            // 使用动画渲染
            animation.render();
        }
    }
}

ExplosiveMineral::ExplosiveMineral(uint32_t id, int x, int y, bool isDisplayed, MineralType type,
                                 IMAGE* img, IMAGE* mask, IMAGE* destroyedImg, IMAGE* destroyedMask)
    : Mineral(id, x, y, isDisplayed, type, img, mask),
      exploded(false), destroyedImg(destroyedImg), destroyedMask(destroyedMask),
      explosionRadius(50),
      explosionAnimation(id + 0x20000, x, y, false, &explosion_sheet, &mask_explosion_sheet,
                         explosion_sheet_frames, explosion_sheet_duration) {
}

void ExplosiveMineral::update() {
    if (exploded) {
        // 如果已爆炸，更新爆炸动画
        explosionAnimation.setX(this->x);
        explosionAnimation.setY(this->y);
        explosionAnimation.update();

        // 检查周围矿物，造成伤害或销毁
        // ...
    }
}

void ExplosiveMineral::render() {
    if (this->isDisplayed) {
        if (exploded) {
            // 如果已爆炸，渲染爆炸后的图像和动画
            putimage(this->x * scaleFactor, this->y * scaleFactor, this->destroyedMask, SRCAND);
            putimage(this->x * scaleFactor, this->y * scaleFactor, this->destroyedImg, SRCPAINT);

            // 渲染爆炸动画
            explosionAnimation.render();
        } else {
            // 普通渲染
            Mineral::render();
        }
    }
}

void ExplosiveMineral::explode() {
    exploded = true;
    explosionAnimation.setDisp(true);

    // 播放爆炸音效
    // ...

    // 设置爆炸动画的帧序列和持续时间
    explosionAnimation.setFrameOrder({0, 1, 2, 3, 4, 5});
    explosionAnimation.setFrameDuration(explosion_sheet_duration);
}