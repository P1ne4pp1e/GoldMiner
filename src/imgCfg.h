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

#define IMG_GOLD_MINI "./images/gold_mini.png"
#define IMG_GOLD_NORMAL "./images/gold_normal.png"
#define IMG_GOLD_NORMAL_PLUS "./images/gold_normal_plus.png"
#define IMG_GOLD_BIG "./images/gold_big.png"
#define IMG_ROCK_MINI "./images/rock_mini.png"
#define IMG_ROCK_NORMAL "./images/rock_normal.png"
#define IMG_ROCK_BIG "./images/rock_big.png"
#define IMG_DIAMOND "./images/diamond.png"
#define IMG_QUESTION_BAG "./images/question_bag.png"
#define IMG_SKULL "./images/skull.png"
#define IMG_BONE "./images/bone.png"
#define IMG_TNT "./images/tnt.png"
#define IMG_MOLE_SHEET "./images/mole_sheet.png"
#define IMG_MOLE_WITH_DIAMOND_SHEET "./images/mole_with_diamond_sheet.png"
#define IMG_EXPLOSION_SHEET "./images/explosive_fx_sheet.png"



#define IMG_MASK_BG_START_MENU "./images/mask_bg_start_menu.bmp"
#define IMG_MASK_BG_GOAL "./images/mask_bg_goal.bmp"
#define IMG_MASK_TEXT_GOLDMINER "./images/mask_text_goldminer.bmp"
#define IMG_MASK_PANEL "./images/mask_panel.bmp"
#define IMG_MASK_BG_TOP "./images/mask_bg_top.bmp"
#define IMG_MASK_MINER_SHIEET "./images/mask_miner_sheet.bmp"
#define IMG_MASK_BG_LEVEL_A "./images/mask_bg_level_A.bmp"
#define IMG_MASK_HOOK_SHEET "./images/mask_hook_sheet.bmp"
// 遮罩路径
#define IMG_MASK_GOLD_MINI "./images/mask_gold_mini.bmp"
#define IMG_MASK_GOLD_NORMAL "./images/mask_gold_normal.bmp"
#define IMG_MASK_GOLD_NORMAL_PLUS "./images/mask_gold_normal_plus.png"
#define IMG_MASK_GOLD_BIG "./images/mask_gold_big.bmp"
#define IMG_MASK_ROCK_MINI "./images/mask_rock_mini.bmp"
#define IMG_MASK_ROCK_NORMAL "./images/mask_rock_normal.bmp"
#define IMG_MASK_ROCK_BIG "./images/mask_rock_big.bmp"
#define IMG_MASK_DIAMOND "./images/mask_diamond.bmp"
#define IMG_MASK_QUESTION_BAG "./images/mask_question_bag.bmp"
#define IMG_MASK_SKULL "./images/mask_skull.bmp"
#define IMG_MASK_BONE "./images/mask_bone.bmp"
#define IMG_MASK_TNT "./images/mask_tnt.bmp"
#define IMG_MASK_MOLE_SHEET "./images/mask_mole_sheet.bmp"
#define IMG_MASK_MOLE_WITH_DIAMOND_SHEET "./images/mask_mole_with_diamond_sheet.bmp"
#define IMG_MASK_EXPLOSION_SHEET "./images/mask_explosive_fx_sheet.bmp"

// 图片变量声明
extern IMAGE bg_start_menu;
extern IMAGE bg_goal;
extern IMAGE text_goldminer;
extern IMAGE panel;
extern IMAGE bg_top;
extern IMAGE miner_sheet;
extern IMAGE bg_level_A;
extern IMAGE hook_sheet;

extern IMAGE gold_mini, gold_normal, gold_normal_plus, gold_big;
extern IMAGE rock_mini, rock_normal, rock_big;
extern IMAGE diamond, question_bag, skull, bone, tnt;
extern IMAGE mole_sheet, mole_with_diamond_sheet, explosion_sheet;



extern IMAGE mask_bg_start_menu;
extern IMAGE mask_bg_goal;
extern IMAGE mask_text_goldminer;
extern IMAGE mask_panel;
extern IMAGE mask_bg_top;
extern IMAGE mask_miner_sheet;
extern IMAGE mask_bg_level_A;
extern IMAGE mask_hook_sheet;

extern IMAGE mask_gold_mini, mask_gold_normal, mask_gold_normal_plus, mask_gold_big;
extern IMAGE mask_rock_mini, mask_rock_normal, mask_rock_big;
extern IMAGE mask_diamond, mask_question_bag, mask_skull, mask_bone, mask_tnt;
extern IMAGE mask_mole_sheet, mask_mole_with_diamond_sheet, mask_explosion_sheet;

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

extern Images GOLD_MINI, GOLD_NORMAL, GOLD_NORMAL_PLUS, GOLD_BIG;
extern Images ROCK_MINI, ROCK_NORMAL, ROCK_BIG;
extern Images DIAMOND, QUESTION_BAG, SKULL, BONE, TNT;
extern Images MOLE_SHEET, MOLE_WITH_DIAMOND_SHEET, EXPLOSION_SHEET;

extern Images MASK_BG_START_MENU;
extern Images MASK_BG_GOAL;
extern Images MASK_TEXT_GOLDMINER;
extern Images MASK_PANEL;
extern Images MASK_BG_TOP;
extern Images MASK_MINER_SHEET;
extern Images MASK_BG_LEVEL_A;
extern Images MASK_HOOK_SHEET;

extern Images MASK_GOLD_MINI, MASK_GOLD_NORMAL, MASK_GOLD_NORMAL_PLUS, MASK_GOLD_BIG;
extern Images MASK_ROCK_MINI, MASK_ROCK_NORMAL, MASK_ROCK_BIG;
extern Images MASK_DIAMOND, MASK_QUESTION_BAG, MASK_SKULL, MASK_BONE, MASK_TNT;
extern Images MASK_MOLE_SHEET, MASK_MOLE_WITH_DIAMOND_SHEET, MASK_EXPLOSION_SHEET;

// 所有图片对象的集合
extern vector<Images> images;

#endif // IMG_CFG
