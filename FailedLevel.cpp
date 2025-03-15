#include "src/Timer.h"
#include "src/windowCfg.h"
#include "src/imgCfg.h"
#include "src/levelCfg.h"
#include "src/FrameInfo.h"
#include "src/ImageProcessing.h"
#include "src/ImageObject.h"
#include "src/TextObject.h"
#include "src/TriangleObject.h"
#include "src/AnimationObject.h"
#include "src/LineObject.h"
#include "src/Mineral.h"
#include "src/MineralManager.h"
#include "src/LevelFunctions.h"

#define HEIGHT 240
#define WIDTH 320

void FailedLevel() {
    txt_panelLine1.setText("You didn't reach the goal!");

    txt_panelLine1.setFontSize(20);
    txt_panelLine1.setX((WIDTH - txt_panelLine1.getWidth() / scaleFactor) / 2);
    txt_panelLine1.setY(130);

    if (timer.elapsed() > failedLevelInterval || (GetAsyncKeyState(VK_SPACE) & 0x8000)) {
        level = START_MENU;
        SCORE = 0;
        levelNum = 0;
        txt_mineralValue.setDisp(false);
        timer.reset();
    }

    img_bgGoal.render();
    img_textGoldminer.render();
    img_panel.render();




    txt_panelLine1.render();
}