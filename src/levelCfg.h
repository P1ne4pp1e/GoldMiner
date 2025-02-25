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
extern int HIGHSCORE;       // 最高得分
extern int targetScore;     // 目标得分

#endif // LEVEL_CFG_H
