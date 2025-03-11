#ifndef MINERAL_CFG_H
#define MINERAL_CFG_H

#include <bits/stdc++.h>
#include "Mineral.h"

// 在MineralConfig.h中
struct MineralConfig {
    int value;          // 价值
    double mass;        // 重量
    double radius;      // 碰撞半径
    const char* imgPath;   // 图像路径
    const char* maskPath;  // 遮罩路径
};

extern const std::map<Mineral::MineralType, MineralConfig> MINERAL_CONFIGS;

#endif