#ifndef LEVEL_CFG
#define LEVEL_CFG

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

Level level;
int SCORE = 0;
int HIGHSCORE = 0;
int targetScore = 0;

#endif