#include "src/FrameInfo.h"
#include "src/AnimationObject.h"
#include "src/imgCfg.h"

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

// 地鼠动画帧
double mole_sheet_duration = 0.2;
std::vector<FrameInfo> mole_sheet_frames = {
    {18, 13, 0, 0},
    {18, 13, 30, 0},
    {18, 13, 60, 0},
    {18, 13, 90, 0}
};

// 爆炸动画帧
double explosion_sheet_duration = 0.05;
std::vector<FrameInfo> explosion_sheet_frames = {
    {64, 64, 0, 0},
    {64, 64, 64, 0},
    {64, 64, 2*64, 0},
    {64, 64, 3*64, 0},
    {64, 64, 4*64, 0},
    {64, 64, 5*64, 0},
    {64, 64, 6*64, 0},
    {64, 64, 7*64, 0},
    {64, 64, 8*64, 0},
    {64, 64, 9*64, 0},
    {64, 64, 10*64, 0},
    {64, 64, 11*64, 0}
};

AnimationObject ani_miner(0x00020003, 150, -2, true, &miner_sheet, &mask_miner_sheet, miner_sheet_frames, miner_sheet_duration);

AnimationObject ani_hookSheet(0x00020005, 0, 0, true, &hook_sheet, &mask_hook_sheet, hook_sheet_frames, hook_sheet_duration);
