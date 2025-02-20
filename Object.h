#ifndef OBJECT_H
#define OBJECT_H

#include <bits/stdc++.h>
#include <conio.h>
#include <graphics.h>

#include "windowCfg.h"

using namespace std;

class Object {
public:
    Object(int x, int y, bool isDisplayed, uint32_t id) : x(x), y(y), isDisplayed(isDisplayed), id(id) {
    };

    int getX() { return this->x; };
    int getY() { return this->y; };
    int getId() { return this->id; };

    void setX(int x) { this->x = x; };
    void setY(int y) { this->y = y; };

    void changeDisp() { this->isDisplayed ^= 1; };

    void setDisp(bool sta) {this->isDisplayed = sta; };

    bool getLapped() { return this->isOverLapped; }
    bool getClicked() { return this->isClicked; }

    void setAngle(double ang) { this->angle = ang; };

    void addAngle(double ang) { this->angle += ang; if (this->angle >= 360.0) this->angle -= 360.0; };

    virtual void rotate() {};

    virtual ~Object() {};

    virtual void render() {};

    virtual void handleMouseEvent(const MOUSEMSG &msg, string *result) {};

    virtual void handleKeyboardEvent() {};

    virtual void update() {};

protected:
    int x;
    int y;
    uint32_t id;
    bool isDisplayed;

    bool isOverLapped = false;
    bool isClicked = false;

    double angle=0;
};

#endif
