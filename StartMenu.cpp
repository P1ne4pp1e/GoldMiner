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



void StartMenu() {
    img_bgStartMenu.render();

    bt_startGame.render();
    bt_highScore.render();
    tri_startGame.render();
    tri_highScore.render();

    string res1 = "";
    string res2 = "";

    static int choose = 1;

    while (MouseHit()) {
        MOUSEMSG mouseMsg = GetMouseMsg();
        bt_startGame.handleMouseEvent(mouseMsg, &res1);
        bt_highScore.handleMouseEvent(mouseMsg, &res2);
    }
    if (bt_startGame.getLapped()) {
        choose = 1;

        if (bt_startGame.getClicked()) {
            level = Level::SHOW_TARGET;
            timer.reset();
        }
    }

    if (bt_highScore.getLapped()) {
        choose = 2;

        if (bt_highScore.getClicked()) {
            level = Level::HIGH_SCORE;
        }
    }
    if (GetAsyncKeyState(0x26) & 0x8000) {
        choose = 1;
        // cout << "VK_UP"  << endl;
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        choose = 2;
        // cout << "VK_DOWN" << endl;
    }
    if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
        if (choose == 1) {
            level = Level::SHOW_TARGET;
            timer.reset();
        }else if (choose == 2) {
            level = Level::HIGH_SCORE;
        }
    }

    switch (choose) {
        case 1:
            bt_startGame.setFontSize(21);
        bt_highScore.setFontSize(20);
        tri_startGame.setDisp(true);
        tri_highScore.setDisp(false);
        break;
        case 2:
            bt_highScore.setFontSize(21);
        bt_startGame.setFontSize(20);
        tri_startGame.setDisp(false);
        tri_highScore.setDisp(true);
        break;
        default:
            bt_highScore.setFontSize(20);
        tri_highScore.setDisp(false);
        bt_startGame.setFontSize(20);
        tri_startGame.setDisp(false);
    }
}
