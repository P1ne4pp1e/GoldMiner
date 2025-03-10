#include "src/LevelCfg.h"
#include "src/FrameInfo.h"

// 全局变量定义与初始化
Level level = START_MENU;    // 默认初始关卡为 START_MENU
int SCORE = 0;               // 初始得分为 0
int HIGHSCORE = 0;           // 初始最高得分为 0
int targetScore = 0;         // 初始目标得分为 0

double hookAngularVelocity = 75;
int hookState = 0;
double hookLength = 12;
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

LineObject rope(0x00020004, 157.7, 26, true, hookLength, 90, RGB(46, 46, 46), 2);

TextObject txt_moneyTitle(0x00020006, 5, 4, true, _T("MONEY"), TextObject::FONT_VISITOR1, 10, RGB(194, 136, 4));
TextObject txt_moneyValue(0x00020007, 45, 4, true, _T("$"), TextObject::FONT_VISITOR1, 10, RGB(67, 160, 71));

TextObject txt_goalTitle(0x00020008, 12, 14, true, _T("GOAL"), TextObject::FONT_VISITOR1, 10, RGB(194, 136, 4));
TextObject txt_goalValue(0x00020009, 45, 14, true, _T("$"), TextObject::FONT_VISITOR1, 10, RGB(67, 160, 71));

TextObject txt_timeTitle(0x0002000A, 252, 14, true, _T("TIME:"), TextObject::FONT_VISITOR1, 10, RGB(194, 136, 4));
TextObject txt_timeValue(0x0002000B, 290, 14, true, _T("$"), TextObject::FONT_VISITOR1, 10, RGB(239, 108, 0));

TextObject txt_levelTitle(0x0002000C, 245, 24, true, _T("LEVEL:"), TextObject::FONT_VISITOR1, 10, RGB(194, 136, 4));
TextObject txt_levelValue(0x0002000D, 290, 24, true, _T("$"), TextObject::FONT_VISITOR1, 10, RGB(239, 108, 0));