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
#define IMG_BG_LEVEL_A "./images/bg_level_A.png"

#define IMG_MASK_BG_START_MENU "./images/mask_bg_start_menu.bmp"
#define IMG_MASK_BG_GOAL "./images/mask_bg_goal.bmp"
#define IMG_MASK_TEXT_GOLDMINER "./images/mask_text_goldminer.bmp"
#define IMG_MASK_PANEL "./images/mask_panel.bmp"
#define IMG_MASK_BG_TOP "./images/mask_bg_top.bmp"
#define IMG_MASK_BG_LEVEL_A "./images/mask_bg_level_A.bmp"

static IMAGE bg_start_menu;
static IMAGE bg_goal;
static IMAGE text_goldminer;
static IMAGE panel;
static IMAGE bg_top;
static IMAGE bg_level_A;

static IMAGE mask_bg_start_menu;
static IMAGE mask_bg_goal;
static IMAGE mask_text_goldminer;
static IMAGE mask_panel;
static IMAGE mask_bg_top;
static IMAGE mask_bg_level_A;

struct Images {
    IMAGE* name;
    string path;
    int width;
    int height;
    Images(IMAGE* name, string path, int width, int height) : name(name), path(path), width(width), height(height) {}
};

Images BG_START_MENU(&bg_start_menu, IMG_BG_START_MENU, 320, 240);
Images BG_GOAL(&bg_goal, IMG_BG_GOAL, 320, 240);
Images TEXT_GOLDMINER(&text_goldminer, IMG_TEXT_GOLDMINER, 212, 43);
Images PANEL(&panel, IMG_PANEL, 266, 120);
Images BG_TOP(&bg_top, IMG_BG_TOP, 320, 40);
Images BG_LEVEL_A(&bg_level_A, IMG_BG_LEVEL_A, 320, 200);

Images MASK_BG_START_MENU(&mask_bg_start_menu, IMG_MASK_BG_START_MENU, 320, 240);
Images MASK_BG_GOAL(&mask_bg_goal, IMG_MASK_BG_GOAL, 320, 240);
Images MASK_TEXT_GOLDMINER(&mask_text_goldminer, IMG_MASK_TEXT_GOLDMINER, 212, 43);
Images MASK_PANEL(&mask_panel, IMG_MASK_PANEL, 266, 120);
Images MASK_BG_TOP(&mask_bg_top, IMG_MASK_BG_TOP, 320, 40);
Images MASK_BG_LEVEL_A(&mask_bg_level_A, IMG_MASK_BG_LEVEL_A, 320, 200);

vector<Images> images = {
    BG_START_MENU,
    BG_GOAL,
    TEXT_GOLDMINER,
    PANEL,
    BG_TOP,
    BG_LEVEL_A,


    MASK_BG_START_MENU,
    MASK_BG_GOAL,
    MASK_TEXT_GOLDMINER,
    MASK_PANEL,
    MASK_BG_TOP,
    MASK_BG_LEVEL_A
};

#endif