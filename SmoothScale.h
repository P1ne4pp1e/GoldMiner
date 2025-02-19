#ifndef SMOOTH_SCALE_H
#define SMOOTH_SCALE_H

#include <iostream>
#include <windows.h>

// 双线性插值缩放函数
void smoothScale(IMAGE* src, IMAGE* dst, int newWidth, int newHeight) {
    int srcWidth = src->getwidth();
    int srcHeight = src->getheight();

    // 创建目标图像
    dst->Resize(newWidth, newHeight);

    // 获取像素缓冲区
    DWORD* srcBuf = GetImageBuffer(src);
    DWORD* dstBuf = GetImageBuffer(dst);

    // 遍历目标图像的每个像素
    for (int y = 0; y < newHeight; y++) {
        for (int x = 0; x < newWidth; x++) {
            // 计算原图对应的浮点坐标
            float srcX = (float)x / newWidth * srcWidth;
            float srcY = (float)y / newHeight * srcHeight;

            // 取相邻四个像素的坐标
            int x1 = (int)srcX;
            int y1 = (int)srcY;
            int x2 = x1 + 1;
            int y2 = y1 + 1;

            // 边界处理
            if (x2 >= srcWidth) x2 = srcWidth - 1;
            if (y2 >= srcHeight) y2 = srcHeight - 1;

            // 计算权重
            float u = srcX - x1;
            float v = srcY - y1;

            // 获取四个相邻像素的颜色
            DWORD c11 = srcBuf[y1 * srcWidth + x1];
            DWORD c12 = srcBuf[y2 * srcWidth + x1];
            DWORD c21 = srcBuf[y1 * srcWidth + x2];
            DWORD c22 = srcBuf[y2 * srcWidth + x2];

            // 对每个颜色通道插值
            BYTE r = (BYTE)((1 - u) * (1 - v) * GetRValue(c11) +
                            (1 - u) * v * GetRValue(c12) +
                            u * (1 - v) * GetRValue(c21) +
                            u * v * GetRValue(c22));

            BYTE g = (BYTE)((1 - u) * (1 - v) * GetGValue(c11) +
                            (1 - u) * v * GetGValue(c12) +
                            u * (1 - v) * GetGValue(c21) +
                            u * v * GetGValue(c22));

            BYTE b = (BYTE)((1 - u) * (1 - v) * GetBValue(c11) +
                            (1 - u) * v * GetBValue(c12) +
                            u * (1 - v) * GetBValue(c21) +
                            u * v * GetBValue(c22));

            // 设置目标像素颜色
            dstBuf[y * newWidth + x] = RGB(r, g, b);
        }
    }
}

#endif // SMOOTH_SCALE_H
