#include "src/LevelCfg.h"

// 全局变量定义与初始化
Level level = START_MENU;    // 默认初始关卡为 START_MENU
int SCORE = 0;               // 初始得分为 0
int HIGHSCORE = 0;           // 初始最高得分为 0
int targetScore = 0;         // 初始目标得分为 0

double hookAngularVelocity = 75;
int hookState = 0;
double hookLength = 8;
double hookVel[3] = {
    0,
    100,
    -200
};

Timer timer;

ImageObject img_bgStartMenu(0x00000000, 0, 0, true, &bg_start_menu, &mask_bg_start_menu);

TextObject bt_startGame(0x00000001, 35, 155, true, _T("Start Game"), TextObject::FONT_KURLAND, 20, RGB(255, 255, 0));
TextObject bt_highScore(0x00000002, 35, 175, true, _T("High Score"), TextObject::FONT_KURLAND, 20, RGB(255, 255, 0));

TriangleObject tri_startGame(0x00000003, {12, 157}, {12, 173}, {30, 165}, false, RGB(255, 255, 0));
TriangleObject tri_highScore(0x00000004, {12, 177}, {12, 193}, {30, 185}, false, RGB(255, 255, 0));



ImageObject img_bgGoal(0x00010000, 0, 0, true, &bg_goal, &mask_bg_goal);
ImageObject img_textGoldminer(0x00010001, 54, 20, true, &text_goldminer, &mask_text_goldminer);

ImageObject img_panel(0x00010002, 27, 80, true, &panel, &mask_panel);

TextObject txt_panelLine1(0x00010003, 75, 100, true, _T(""), TextObject::FONT_KURLAND, 20, RGB(234, 221, 98));
TextObject txt_panelLine2_1(0x00010004, 75, 145, true, _T(""), TextObject::FONT_KURLAND, 20, RGB(73, 192, 95));
TextObject txt_panelLine2_2(0x00010005, 75, 145, true, _T(""), TextObject::FONT_KURLAND, 20, RGB(234, 221, 98));



ImageObject img_bgTop(0x00020000, 0, 0, true, &bg_top, &mask_bg_top);
ImageObject img_bgLevelA(0x00020001, 0, 40, true, &bg_level_A, &mask_bg_level_A);

AnimationObject ani_miner(0x00020003, 150, -2, true, &miner_sheet, &mask_miner_sheet, miner_sheet_frames, miner_sheet_duration);

LineObject rope(0x00020004, 157.7, 29.8, true, hookLength, 90, RGB(22, 22, 22), 2);

AnimationObject ani_hookSheet(0x00020005, 0, 0, true, &hook_sheet, &mask_hook_sheet, hook_sheet_frames, hook_sheet_duration);
