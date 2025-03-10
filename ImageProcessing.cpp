#include "src/ImageProcessing.h"

void smoothScale(IMAGE* src, IMAGE* dst, int newWidth, int newHeight) {
    int srcWidth = src->getwidth();
    int srcHeight = src->getheight();
    if (srcWidth == newWidth && srcHeight == newHeight) {
        *dst = *src;
        return;
    }

    // 创建目标图像
    dst->Resize(newWidth, newHeight);

    // 关键修复：初始化目标图像背景为白色（或任何合适的颜色）
    SetWorkingImage(dst);
    setbkcolor(WHITE);  // 设置背景色为白色
    cleardevice();      // 使用背景色清空图像
    SetWorkingImage(NULL);  // 恢复默认工作区

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

// 图像锐化函数定义
void sharpenImage(IMAGE* src, IMAGE* dst, double sharpenValue) {
    // 拉普拉斯锐化卷积核
    const double kernel[3][3] = {
        { 0, -1, 0 },
        { -1, 4 + sharpenValue, -1 },
        { 0, -1, 0 }
    };

    int width = src->getwidth();
    int height = src->getheight();

    // 确保目标图像具有相同的大小
    dst->Resize(width, height);

    // 遍历图像像素并应用卷积核
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            double r = 0, g = 0, b = 0;
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    SetWorkingImage(src);
                    int pixelColor = getpixel(x + kx, y + ky);
                    COLORREF color = RGB(GetRValue(pixelColor), GetGValue(pixelColor), GetBValue(pixelColor));
                    r += GetRValue(color) * kernel[ky + 1][kx + 1];
                    g += GetGValue(color) * kernel[ky + 1][kx + 1];
                    b += GetBValue(color) * kernel[ky + 1][kx + 1];
                }
            }

            // 确保颜色值在合法范围内
            r = std::min(std::max(0.0, r), 255.0);
            g = std::min(std::max(0.0, g), 255.0);
            b = std::min(std::max(0.0, b), 255.0);

            COLORREF newColor = RGB(static_cast<int>(r), static_cast<int>(g), static_cast<int>(b));

            SetWorkingImage(dst);
            putpixel(x, y, newColor);


            SetWorkingImage();
        }
    }
}