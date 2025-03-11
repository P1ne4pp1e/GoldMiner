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

IMAGE gold_mini, gold_normal, gold_normal_plus, gold_big;
IMAGE rock_mini, rock_normal, rock_big;
IMAGE diamond, question_bag, skull, bone, tnt;
IMAGE mole_sheet, mole_with_diamond_sheet, explosion_sheet;



IMAGE mask_bg_start_menu;
IMAGE mask_bg_goal;
IMAGE mask_text_goldminer;
IMAGE mask_panel;
IMAGE mask_bg_top;
IMAGE mask_miner_sheet;
IMAGE mask_bg_level_A;
IMAGE mask_hook_sheet;

IMAGE mask_gold_mini, mask_gold_normal, mask_gold_normal_plus, mask_gold_big;
IMAGE mask_rock_mini, mask_rock_normal, mask_rock_big;
IMAGE mask_diamond, mask_question_bag, mask_skull, mask_bone, mask_tnt;
IMAGE mask_mole_sheet, mask_mole_with_diamond_sheet, mask_explosion_sheet;

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
// 添加到images向量中
Images GOLD_MINI(&gold_mini, IMG_GOLD_MINI, 10, 8);
Images GOLD_NORMAL(&gold_normal, IMG_GOLD_NORMAL, 15, 13);
Images GOLD_NORMAL_PLUS(&gold_normal_plus, IMG_GOLD_NORMAL, 20, 18);
Images GOLD_BIG(&gold_big, IMG_GOLD_BIG, 32, 29);
Images ROCK_MINI(&rock_mini, IMG_ROCK_MINI, 15, 11);
Images ROCK_NORMAL(&rock_normal, IMG_ROCK_NORMAL, 22, 19);
Images ROCK_BIG(&rock_big, IMG_ROCK_BIG, 32, 28);
Images DIAMOND(&diamond, IMG_DIAMOND, 10, 8);
Images QUESTION_BAG(&question_bag, IMG_QUESTION_BAG, 20, 23);
Images SKULL(&skull, IMG_SKULL, 18, 17);
Images BONE(&bone, IMG_BONE, 20, 13);
Images TNT(&tnt, IMG_TNT, 26, 33);
Images MOLE_SHEET(&mole_sheet, IMG_MOLE_SHEET, 126, 13);
Images MOLE_WITH_DIAMOND_SHEET(&mole_with_diamond_sheet, IMG_MOLE_WITH_DIAMOND_SHEET, 126, 13);
Images EXPLOSION_SHEET(&explosion_sheet, IMG_EXPLOSION_SHEET, 768, 64);


Images MASK_BG_START_MENU(&mask_bg_start_menu, IMG_MASK_BG_START_MENU, 320, 240);
Images MASK_BG_GOAL(&mask_bg_goal, IMG_MASK_BG_GOAL, 320, 240);
Images MASK_TEXT_GOLDMINER(&mask_text_goldminer, IMG_MASK_TEXT_GOLDMINER, 212, 43);
Images MASK_PANEL(&mask_panel, IMG_MASK_PANEL, 266, 120);
Images MASK_BG_TOP(&mask_bg_top, IMG_MASK_BG_TOP, 320, 40);
Images MASK_MINER_SHEET(&mask_miner_sheet, IMG_MASK_MINER_SHIEET, 256, 40);
Images MASK_BG_LEVEL_A(&mask_bg_level_A, IMG_MASK_BG_LEVEL_A, 320, 200);
Images MASK_HOOK_SHEET(&mask_hook_sheet, IMG_MASK_HOOK_SHEET, 39, 15);

Images MASK_GOLD_MINI(&mask_gold_mini, IMG_MASK_GOLD_MINI, 10, 8);
Images MASK_GOLD_NORMAL(&mask_gold_normal, IMG_MASK_GOLD_NORMAL, 15, 13);
Images MASK_GOLD_NORMAL_PLUS(&mask_gold_normal_plus, IMG_MASK_GOLD_NORMAL, 20, 18);
Images MASK_GOLD_BIG(&mask_gold_big, IMG_MASK_GOLD_BIG, 32, 29);
Images MASK_ROCK_MINI(&mask_rock_mini, IMG_MASK_ROCK_MINI, 15, 11);
Images MASK_ROCK_NORMAL(&mask_rock_normal, IMG_MASK_ROCK_NORMAL, 22, 19);
Images MASK_ROCK_BIG(&mask_rock_big, IMG_MASK_ROCK_BIG, 32, 28);
Images MASK_DIAMOND(&mask_diamond, IMG_MASK_DIAMOND, 10, 8);
Images MASK_QUESTION_BAG(&mask_question_bag, IMG_MASK_QUESTION_BAG, 20, 23);
Images MASK_SKULL(&mask_skull, IMG_MASK_SKULL, 18, 17);
Images MASK_BONE(&mask_bone, IMG_MASK_BONE, 20, 13);
Images MASK_TNT(&mask_tnt, IMG_MASK_TNT, 26, 33);
Images MASK_MOLE_SHEET(&mask_mole_sheet, IMG_MASK_MOLE_SHEET, 126, 13);
Images MASK_MOLE_WITH_DIAMOND_SHEET(&mask_mole_with_diamond_sheet, IMG_MASK_MOLE_WITH_DIAMOND_SHEET, 126, 13);
Images MASK_EXPLOSION_SHEET(&mask_explosion_sheet, IMG_MASK_EXPLOSION_SHEET, 768, 64);

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

    GOLD_MINI, GOLD_NORMAL, GOLD_NORMAL_PLUS, GOLD_BIG,
    ROCK_MINI, ROCK_NORMAL, ROCK_BIG,
    DIAMOND, QUESTION_BAG, SKULL, BONE, TNT,
    MOLE_SHEET, MOLE_WITH_DIAMOND_SHEET, EXPLOSION_SHEET,


    MASK_BG_START_MENU,
    MASK_BG_GOAL,
    MASK_TEXT_GOLDMINER,
    MASK_PANEL,
    MASK_BG_TOP,
    MASK_MINER_SHEET,
    MASK_BG_LEVEL_A,
    MASK_HOOK_SHEET,

    MASK_GOLD_MINI, MASK_GOLD_NORMAL, MASK_GOLD_NORMAL_PLUS, MASK_GOLD_BIG,
    MASK_ROCK_MINI, MASK_ROCK_NORMAL, MASK_ROCK_BIG,
    MASK_DIAMOND, MASK_QUESTION_BAG, MASK_SKULL, MASK_BONE, MASK_TNT,
    MASK_MOLE_SHEET, MASK_MOLE_WITH_DIAMOND_SHEET, MASK_EXPLOSION_SHEET
};
