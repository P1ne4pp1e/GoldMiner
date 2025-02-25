#include "src/FrameInfo.h"

// 全局变量定义与初始化
double miner_sheet_duration = 0.5;  // 默认持续时间为0.5秒
std::vector<FrameInfo> miner_sheet_frames = {
    {32, 40, 0, 0},
    {32, 40, 32, 0},
    {32, 40, 64, 0},
    {32, 40, 96, 0},
    {32, 40, 128, 0},
    {32, 40, 160, 0},
    {32, 40, 192, 0},
    {32, 40, 224, 0}
};  // 默认的帧信息

double hook_sheet_duration = 0.5;
std::vector<FrameInfo> hook_sheet_frames = {
    {13, 15, 0, 0},
    {13, 15, 13, 0},
    {13, 15, 26, 0}
};
