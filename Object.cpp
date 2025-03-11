#include "src/Object.h"

// 构造函数
Object::Object(double x, double y, bool isDisplayed, uint32_t id)
    : x(x), y(y), isDisplayed(isDisplayed), id(id) {}

// 获取函数实现
double Object::getX() { return this->x; }
double Object::getY() { return this->y; }
int Object::getId() { return this->id; }
double Object::getAngle() { return this->angle; }
double Object::getAngularVelocity() { return this->angularVelocity; }
bool Object::getDisplayed() { return this->isDisplayed; }

// 设置函数实现
void Object::setX(double x) { this->x = x; }
void Object::setY(double y) { this->y = y; }

void Object::setAngle(double ang) { this->angle = ang; }

void Object::addAngle(double ang) {
    this->angle += ang;
    if (this->angle >= 360.0) this->angle -= 360.0;
}

void Object::setAngularVelocity(double newAngularVelocity) { this->angularVelocity = newAngularVelocity; }

// 状态控制实现
void Object::changeDisp() { this->isDisplayed ^= 1; }
void Object::setDisp(bool sta) { this->isDisplayed = sta; }
bool Object::getLapped() { return this->isOverLapped; }
bool Object::getClicked() { return this->isClicked; }

// 空虚函数实现
void Object::rotate() {}

// 虚析构函数
Object::~Object() {}

// 虚拟函数的其他默认实现
void Object::render() {}
void Object::handleMouseEvent(const MOUSEMSG &msg, string *result) {}
void Object::handleKeyboardEvent() {}
void Object::update() {}
