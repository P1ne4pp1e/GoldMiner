#ifndef OBJECT_H
#define OBJECT_H

#include <bits/stdc++.h>
#include <conio.h>
#include <graphics.h>
#include "windowCfg.h"

using namespace std;

class Object {
public:
    struct Point {
        double x, y;
        Point(double xCoord, double yCoord) : x(xCoord), y(yCoord) {}
    };

    // 构造函数
    Object(double x, double y, bool isDisplayed, uint32_t id);

    // 获取函数
    double getX();
    double getY();
    int getId();
    virtual double getAngle();
    virtual double getAngularVelocity();

    // 设置函数
    void setX(double x);
    void setY(double y);
    void setAngle(double ang);
    void addAngle(double ang);
    void setAngularVelocity(double newAngularVelocity);

    // 状态控制
    void changeDisp();
    void setDisp(bool sta);
    bool getLapped();
    bool getClicked();
    bool getDisplayed();

    virtual void rotate();
    virtual void render();
    virtual void handleMouseEvent(const MOUSEMSG &msg, string *result);
    virtual void handleKeyboardEvent();
    virtual void update();

    // 虚析构函数
    virtual ~Object();

protected:
    double x;
    double y;
    uint32_t id;
    bool isDisplayed;
    bool isOverLapped = false;
    bool isClicked = false;
    double angle = 0;
    double angularVelocity = 0; // 角速度
};

#endif // OBJECT_H
