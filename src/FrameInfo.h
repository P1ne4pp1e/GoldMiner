#ifndef FRAMEINFO_H
#define FRAMEINFO_H

#include <vector>
#include <tuple>

// 定义帧信息类型
using FrameInfo = std::tuple<int, int, int, int>;

// 全局变量声明
extern double miner_sheet_duration;           // 持续时间
extern std::vector<FrameInfo> miner_sheet_frames; // 帧信息列表

extern double hook_sheet_duration;
extern std::vector<FrameInfo> hook_sheet_frames;

// 地鼠动画帧
extern double mole_sheet_duration;
extern std::vector<FrameInfo> mole_sheet_frames;

// 爆炸动画帧
extern double explosion_sheet_duration;
extern std::vector<FrameInfo> explosion_sheet_frames;

#endif // FRAMEINFO_H
