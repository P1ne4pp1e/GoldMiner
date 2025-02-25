#include "src/ImgCfg.h"

// 图片变量定义
IMAGE bg_start_menu;
IMAGE bg_goal;
IMAGE text_goldminer;
IMAGE panel;
IMAGE bg_top;
IMAGE miner_sheet;
IMAGE bg_level_A;
IMAGE hook_sheet;

IMAGE mask_bg_start_menu;
IMAGE mask_bg_goal;
IMAGE mask_text_goldminer;
IMAGE mask_panel;
IMAGE mask_bg_top;
IMAGE mask_miner_sheet;
IMAGE mask_bg_level_A;
IMAGE mask_hook_sheet;

// 图片信息构造函数定义
Images::Images(IMAGE* name, string path, int width, int height)
    : name(name), path(path), width(width), height(height) {}

// 图片对象定义
Images BG_START_MENU(&bg_start_menu, IMG_BG_START_MENU, 320, 240);
Images BG_GOAL(&bg_goal, IMG_BG_GOAL, 320, 240);
Images TEXT_GOLDMINER(&text_goldminer, IMG_TEXT_GOLDMINER, 212, 43);
Images PANEL(&panel, IMG_PANEL, 266, 120);
Images BG_TOP(&bg_top, IMG_BG_TOP, 320, 40);
Images MINER_SHEET(&miner_sheet, IMG_MINER_SHIEET, 256, 40);
Images BG_LEVEL_A(&bg_level_A, IMG_BG_LEVEL_A, 320, 200);
Images HOOK_SHEET(&hook_sheet, IMG_HOOK_SHEET, 39, 15);

Images MASK_BG_START_MENU(&mask_bg_start_menu, IMG_MASK_BG_START_MENU, 320, 240);
Images MASK_BG_GOAL(&mask_bg_goal, IMG_MASK_BG_GOAL, 320, 240);
Images MASK_TEXT_GOLDMINER(&mask_text_goldminer, IMG_MASK_TEXT_GOLDMINER, 212, 43);
Images MASK_PANEL(&mask_panel, IMG_MASK_PANEL, 266, 120);
Images MASK_BG_TOP(&mask_bg_top, IMG_MASK_BG_TOP, 320, 40);
Images MASK_MINER_SHEET(&mask_miner_sheet, IMG_MASK_MINER_SHIEET, 256, 40);
Images MASK_BG_LEVEL_A(&mask_bg_level_A, IMG_MASK_BG_LEVEL_A, 320, 200);
Images MASK_HOOK_SHEET(&mask_hook_sheet, IMG_MASK_HOOK_SHEET, 39, 15);

// 图片集合定义
vector<Images> images = {
    BG_START_MENU,
    BG_GOAL,
    TEXT_GOLDMINER,
    PANEL,
    BG_TOP,
    MINER_SHEET,
    BG_LEVEL_A,
    HOOK_SHEET,

    MASK_BG_START_MENU,
    MASK_BG_GOAL,
    MASK_TEXT_GOLDMINER,
    MASK_PANEL,
    MASK_BG_TOP,
    MASK_MINER_SHEET,
    MASK_BG_LEVEL_A,
    MASK_HOOK_SHEET
};
