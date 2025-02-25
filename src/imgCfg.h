#ifndef IMG_CFG
#define IMG_CFG

#include <bits/stdc++.h>
#include <graphics.h>

using namespace std;

#define IMG_BG_START_MENU "./images/bg_start_menu.png"
#define IMG_BG_GOAL "./images/bg_goal.png"
#define IMG_TEXT_GOLDMINER "./images/text_goldminer.png"
#define IMG_PANEL "./images/panel.png"
#define IMG_BG_TOP "./images/bg_top.png"
#define IMG_MINER_SHIEET "./images/miner_sheet.png"
#define IMG_BG_LEVEL_A "./images/bg_level_A.png"
#define IMG_HOOK_SHEET "./images/hook_sheet.png"

#define IMG_MASK_BG_START_MENU "./images/mask_bg_start_menu.bmp"
#define IMG_MASK_BG_GOAL "./images/mask_bg_goal.bmp"
#define IMG_MASK_TEXT_GOLDMINER "./images/mask_text_goldminer.bmp"
#define IMG_MASK_PANEL "./images/mask_panel.bmp"
#define IMG_MASK_BG_TOP "./images/mask_bg_top.bmp"
#define IMG_MASK_MINER_SHIEET "./images/mask_miner_sheet.bmp"
#define IMG_MASK_BG_LEVEL_A "./images/mask_bg_level_A.bmp"
#define IMG_MASK_HOOK_SHEET "./images/mask_hook_sheet.bmp"

// 图片变量声明
extern IMAGE bg_start_menu;
extern IMAGE bg_goal;
extern IMAGE text_goldminer;
extern IMAGE panel;
extern IMAGE bg_top;
extern IMAGE miner_sheet;
extern IMAGE bg_level_A;
extern IMAGE hook_sheet;

extern IMAGE mask_bg_start_menu;
extern IMAGE mask_bg_goal;
extern IMAGE mask_text_goldminer;
extern IMAGE mask_panel;
extern IMAGE mask_bg_top;
extern IMAGE mask_miner_sheet;
extern IMAGE mask_bg_level_A;
extern IMAGE mask_hook_sheet;

// 图片信息结构体声明
struct Images {
    IMAGE* name;
    string path;
    int width;
    int height;
    Images(IMAGE* name, string path, int width, int height);
};

// 图像对象声明
extern Images BG_START_MENU;
extern Images BG_GOAL;
extern Images TEXT_GOLDMINER;
extern Images PANEL;
extern Images BG_TOP;
extern Images MINER_SHEET;
extern Images BG_LEVEL_A;
extern Images HOOK_SHEET;

extern Images MASK_BG_START_MENU;
extern Images MASK_BG_GOAL;
extern Images MASK_TEXT_GOLDMINER;
extern Images MASK_PANEL;
extern Images MASK_BG_TOP;
extern Images MASK_MINER_SHEET;
extern Images MASK_BG_LEVEL_A;
extern Images MASK_HOOK_SHEET;

// 所有图片对象的集合
extern vector<Images> images;

#endif // IMG_CFG
