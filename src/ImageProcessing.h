#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <iostream>
#include <windows.h>
#include <graphics.h>
#include <algorithm>

// 双线性插值缩放函数
void smoothScale(IMAGE* src, IMAGE* dst, int newWidth, int newHeight);

void nearestNeighborScale(IMAGE* src, IMAGE* dst, int newWidth, int newHeight);

// 图像锐化函数声明
void sharpenImage(IMAGE* src, IMAGE* dst, double sharpenValue);

#endif // IMAGEPROCESSING_H
