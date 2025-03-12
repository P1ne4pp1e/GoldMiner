#include "ImageObject.h"
#include "TextObject.h"
#include "TriangleObject.h"
#include "AnimationObject.h"
#include "LineObject.h"
#include "imgCfg.h"
#include "Timer.h"
#include <yaml-cpp/yaml.h>

#ifndef LEVEL_CFG_H
#define LEVEL_CFG_H

// 定义游戏等级的枚举类型
enum Level {
    START_MENU,
    SHOW_TARGET,
    HIGH_SCORE,
    LEVEL_1,
    LEVEL_2,
    LEVEL_3,
    LEVEL_4,
    LEVEL_5
};

// 全局变量声明
extern Level level;         // 当前关卡
extern int SCORE;           // 当前得分
// extern int HIGHSCORE;       // 最高得分
extern int targetScore;     // 目标得分
//
// extern double hookAngularVelocity;
extern int hookState;
// extern double hookLength;
// extern double hookVel[3];




extern Timer timer;

extern ImageObject img_bgStartMenu;

extern TextObject bt_startGame;
extern TextObject bt_highScore;

extern TriangleObject tri_startGame;
extern TriangleObject tri_highScore;



extern ImageObject img_bgGoal;
extern ImageObject img_textGoldminer;

extern ImageObject img_panel;

extern TextObject txt_panelLine1;
extern TextObject txt_panelLine2_1;
extern TextObject txt_panelLine2_2;



extern ImageObject img_bgTop;
extern ImageObject img_bgLevelA;

extern AnimationObject ani_miner;

extern LineObject rope;

extern AnimationObject ani_hookSheet;

extern TextObject txt_moneyTitle;
extern TextObject txt_moneyValue;

extern TextObject txt_goalTitle;
extern TextObject txt_goalValue;

extern TextObject txt_timeTitle;
extern TextObject txt_timeValue;

extern TextObject txt_levelTitle;
extern TextObject txt_levelValue;


extern YAML::Node player;
extern YAML::Node entities;
extern YAML::Node levels;

YAML::Node LoadData(string filename);

void StartMenu();

void HighScore();

void ShowTarget();

#endif // LEVEL_CFG_H
