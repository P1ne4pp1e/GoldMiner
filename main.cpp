#include <bits/stdc++.h>
#include <graphics.h>
#include <conio.h>
#include <filesystem>
#include <chrono>

#include "Timer.h"
#include "SmoothScale.h"
#include "windowCfg.h"
#include "imgCfg.h"
#include "levelCfg.h"
#include "TextObject.h"
#include "TriangleObject.h"
#include "ImageObject.h"

#define HEIGHT 240
#define WIDTH 320

#define SET_SINGLE_FONT(height, width, fontName, fontPath) \
do { \
AddFontResourceEx(fontPath, FR_PRIVATE, 0); \
settextstyle(height, width, _T(fontName)); \
} while(0)

using namespace std;
namespace fs = std::filesystem;


void loadingImage(const vector<Images>& images) {
    std::filesystem::path currentPath = std::filesystem::current_path();

    for (int i = 0; i < images.size(); i++) {
        IMAGE img;
        loadimage(&img, images[i].path.c_str(), images[i].width, images[i].height);
        smoothScale(&img, images[i].name, images[i].width * scaleFactor, images[i].height * scaleFactor);
    }
}

Timer timer;

ImageObject img_bgStartMenu(0x00000000, 0, 0, true, &bg_start_menu, &mask_bg_start_menu);

TextObject bt_startGame(0x00000001, 35, 155, true, _T("Start Game"), TextObject::FONT_KURLAND, 20, RGB(255, 255, 0));
TextObject bt_highScore(0x00000002, 35, 175, true, _T("High Score"), TextObject::FONT_KURLAND, 20, RGB(255, 255, 0));

TriangleObject tri_startGame(0x00010003, {12, 157}, {12, 173}, {30, 165}, false, RGB(255, 255, 0));
TriangleObject tri_highScore(0x00010004, {12, 177}, {12, 193}, {30, 185}, false, RGB(255, 255, 0));


ImageObject img_bgGoal(0x00010000, 0, 0, true, &bg_goal, &mask_bg_goal);
ImageObject img_textGoldminer(0x00010001, 54, 20, true, &text_goldminer, &mask_text_goldminer);

ImageObject img_panel(0x00010002, 27, 80, true, &panel, &mask_panel);

TextObject txt_panelLine1(0x00010003, 75, 100, true, _T(""), TextObject::FONT_KURLAND, 20, RGB(234, 221, 98));
TextObject txt_panelLine2_1(0x00010004, 75, 145, true, _T(""), TextObject::FONT_KURLAND, 20, RGB(73, 192, 95));
TextObject txt_panelLine2_2(0x00010005, 75, 145, true, _T(""), TextObject::FONT_KURLAND, 20, RGB(234, 221, 98));

ImageObject img_bgTop(0x00020000, 0, 0, true, &bg_top, &mask_bg_top);
ImageObject img_bgLevelA(0x00020001, 0, 40, true, &bg_level_A, &mask_bg_level_A);

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

void HighScore() {
    img_bgGoal.render();
    img_textGoldminer.render();
    img_panel.render();

    txt_panelLine1.setText("High Score: ");
    txt_panelLine2_1.setText( "$" + to_string(HIGHSCORE) );
    txt_panelLine2_2.setX(txt_panelLine2_1.getX() + txt_panelLine2_1.getWidth() + 7.0);

    switch (level) {
        case Level::LEVEL_1:
            txt_panelLine2_2.setText( _T("at Level1") );
            break;
        case Level::LEVEL_2:
            txt_panelLine2_2.setText( _T("at Level2") );
            break;
        case Level::LEVEL_3:
            txt_panelLine2_2.setText( _T("at Level3") );
            break;
        case Level::LEVEL_4:
            txt_panelLine2_2.setText( _T("at Level4") );
            break;
        case Level::LEVEL_5:
            txt_panelLine2_2.setText( _T("at Level5") );
            break;
        default:
            txt_panelLine2_2.setText( _T("at Level1") );
    }

    txt_panelLine1.render();
    txt_panelLine2_1.render();
    txt_panelLine2_2.render();
    // std::cout << "Current path: " << std::filesystem::current_path() << std::endl;

    if (GetAsyncKeyState(VK_BACK) & 0x8000) {
        level = Level::START_MENU;
    }

}

void ShowTarget() {
    img_bgGoal.render();
    img_textGoldminer.render();
    img_panel.render();

    switch (level) {
        case Level::LEVEL_1:
            txt_panelLine1.setText("Your First Goal is");
            targetScore = 650;
            break;
        case Level::LEVEL_2:
            txt_panelLine1.setText("Your Second Goal is");
            break;
        case Level::LEVEL_3:
            txt_panelLine1.setText("Your Third Goal is");
            break;
        case Level::LEVEL_4:
            txt_panelLine1.setText("Your Fourth Goal is");
            break;
        case Level::LEVEL_5:
            txt_panelLine1.setText("Your Fifth Goal is");
            break;
        default:
            txt_panelLine1.setText("Your First Goal is");
            targetScore = 650;
    }
    txt_panelLine2_1.setText( "$" + to_string(targetScore) );

    txt_panelLine1.render();
    txt_panelLine2_1.render();

    if ( timer.elapsed() > 3.0 ) {
        timer.reset();
        level = Level::LEVEL_1;
    }


    if (GetAsyncKeyState(VK_BACK) & 0x8000) {
        level = Level::START_MENU;
    }
}

void Level1() {
    img_bgTop.render();
    img_bgLevelA.render();
}

int main() {
    loadingImage(images);

    initgraph(WIDTH * scaleFactor, HEIGHT * scaleFactor);
    // setbkcolor(BLACK);
    setbkcolor(GREEN);

    level = Level::START_MENU;

    bool running = true;

    int frameCount = 0;
    auto lastTime = chrono::steady_clock::now();
    double fps = 0.0;

    timer.start();
    while (running) {
        auto currentTime = chrono::steady_clock::now();
        frameCount++;

        // 每秒更新一次帧率
        if (chrono::duration_cast<chrono::milliseconds>(currentTime - lastTime).count() >= 500) {
            fps = frameCount / (chrono::duration_cast<chrono::milliseconds>(currentTime - lastTime).count() / 1000.0);
            lastTime = currentTime;
            frameCount = 0;
        }

        BeginBatchDraw();
        cleardevice();

        if (level == Level::START_MENU) {
            StartMenu();
        }else if (level == Level::HIGH_SCORE) {
            HighScore();
        }else if (level == Level::SHOW_TARGET) {
            ShowTarget();
        }else if (level == Level::LEVEL_1) {
            Level1();
        }

        SET_SINGLE_FONT(20, 0, "Kurland", "fonts/Kurland.ttf");
        settextcolor(RGB(255, 255, 255));
        outtextxy(WIDTH * scaleFactor - 70, 10, ("FPS " + to_string(static_cast<int>(fps))).c_str());

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            running = false;
        }

        EndBatchDraw();
    }

    closegraph();

    return 0;
}
