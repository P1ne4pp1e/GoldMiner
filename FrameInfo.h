#ifndef FRAMEINFO_H
#define FRAMEINFO_H

#include <bits/stdc++.h>

using FrameInfo = std::tuple<int, int, int, int>;

double miner_sheet_duration = 0.5;
std::vector<FrameInfo> miner_sheet_frames = {
    {32, 40, 0, 0},
    {32, 40, 32, 0},
    {32, 40, 64, 0},
    {32, 40, 96, 0},
    {32, 40, 128, 0},
    {32, 40, 160, 0},
    {32, 40, 192, 0},
    {32, 40, 224, 0}
};

#endif