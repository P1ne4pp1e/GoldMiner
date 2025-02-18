#ifndef IMG_CFG
#define IMG_CFG

#include <bits/stdc++.h>
#include <graphics.h>

using namespace std;

#define IMG_BG_START_MENU "./images/bg_start_menu.png"
#define IMG_BG_GOAL "./images/bg_goal.png"
#define IMG_TEXT_GOLDMINER "./images/text_goldminer.png"

#define IMG_MASK_BG_START_MENU "./images/mask_bg_start_menu.jpg"
#define IMG_MASK_BG_GOAL "./images/mask_bg_goal.jpg"
#define IMG_MASK_TEXT_GOLDMINER "./images/mask_text_goldminer.jpg"

static IMAGE bg_start_menu;
static IMAGE bg_goal;
static IMAGE text_goldminer;

static IMAGE mask_bg_start_menu;
static IMAGE mask_bg_goal;
static IMAGE mask_text_goldminer;

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

Images MASK_BG_START_MENU(&mask_bg_start_menu, IMG_MASK_BG_START_MENU, 320, 240);
Images MASK_BG_GOAL(&mask_bg_goal, IMG_MASK_BG_GOAL, 320, 240);
Images MASK_TEXT_GOLDMINER(&mask_text_goldminer, IMG_MASK_TEXT_GOLDMINER, 212, 43);

vector<Images> images = {
    BG_START_MENU,
    BG_GOAL,
    TEXT_GOLDMINER,


    MASK_BG_START_MENU,
    MASK_BG_GOAL,
    MASK_TEXT_GOLDMINER
};

#endif