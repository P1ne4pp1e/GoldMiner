#ifndef MINERAL_H
#define MINERAL_H

#include "Object.h"
#include "AnimationObject.h"

// 在src/Mineral.h中
class Mineral : public Object {
public:
    enum MineralType {
        GOLD_MINI,      // 小金块
        GOLD_NORMAL,    // 普通金块
        GOLD_NORMAL_PLUS,
        GOLD_BIG,       // 大金块
        ROCK_MINI,      // 小石头
        ROCK_NORMAL,    // 普通石头
        ROCK_BIG,       // 大石头
        DIAMOND,        // 钻石
        QUESTION_BAG,   // 神秘袋子
        SKULL,          // 骷髅头
        BONE,           // 骨头
        TNT,            // 炸药
        MOLE,
        MOLE_WITH_DIAMOND
    };

    Mineral(uint32_t id, int x, int y, bool isDisplayed, MineralType type, IMAGE* img, IMAGE* mask);

    virtual void render() override;
    virtual void update() override;

    int getValue() const;         // 获取价值
    int getMass() const;          // 获取重量
    Point getCenter() const;
    double getRadius() const;     // 获取碰撞半径
    MineralType getType() const;

    bool isHooked() const;        // 是否被抓住
    void setHooked(bool hooked);  // 设置抓取状态

    virtual void onHooked();      // 被抓住时的回调
    virtual void onCollected();   // 被收集时的回调

protected:
    MineralType type;
    int value;          // 价值
    int mass;           // 重量，影响拉回速度
    double radius;      // 碰撞半径
    bool hooked;        // 是否被钩子抓住
    IMAGE* img;
    IMAGE* mask;
};



// 会移动的矿物（如地鼠）
class MovingMineral : public Mineral {
public:
    MovingMineral(uint32_t id, int x, int y, bool isDisplayed, MineralType type,
                IMAGE* img, IMAGE* mask, const std::vector<FrameInfo>& frames, double frameDuration);

    void update() override;
    void render() override;

    void setMoveRange(int range);
    void setSpeed(double speed);

private:
    int moveRange;       // 移动范围
    double speed;        // 移动速度
    int direction;       // 移动方向 (1 或 -1)
    int startX;          // 起始X坐标
    AnimationObject animation;  // 动画对象
};



// 爆炸性矿物（如TNT）
class ExplosiveMineral : public Mineral {
public:
    ExplosiveMineral(uint32_t id, int x, int y, bool isDisplayed, MineralType type,
                   IMAGE* img, IMAGE* mask, IMAGE* destroyedImg, IMAGE* destroyedMask);

    void update() override;
    void render() override;
    void explode();     // 触发爆炸

private:
    bool exploded;            // 是否已爆炸
    IMAGE* destroyedImg;      // 爆炸后的图像
    IMAGE* destroyedMask;     // 爆炸后的遮罩
    double explosionRadius;   // 爆炸半径
    AnimationObject explosionAnimation; // 爆炸动画
};



// 随机效果矿物（如问号袋）
class RandomEffectMineral : public Mineral {
public:
    RandomEffectMineral(uint32_t id, int x, int y, bool isDisplayed,
                      IMAGE* img, IMAGE* mask);

    void onCollected() override; // 重写收集回调以添加随机效果

private:
    int getRandomBonus(); // 获取随机奖励金额
    void applyRandomEffect(); // 应用随机效果
};

#endif