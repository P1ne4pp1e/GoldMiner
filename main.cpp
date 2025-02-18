#include <bits/stdc++.h>
#include <graphics.h>
#include <conio.h>
#include <filesystem>
#include <chrono>

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
    for (int i = 0; i < images.size(); i++) {
        loadimage(images[i].name, images[i].path.c_str(), images[i].width * scaleFactor, images[i].height * scaleFactor);
    }
}

ImageObject img_bgStartMenu(0x00000000, 0, 0, true, &bg_start_menu, &mask_bg_start_menu);

TextObject bt_startGame(0x00000001, 35, 155, true, _T("Start Game"), TextObject::FONT_KURLAND, 20, RGB(255, 255, 0));
TextObject bt_highScore(0x00000002, 35, 175, true, _T("High Score"), TextObject::FONT_KURLAND, 20, RGB(255, 255, 0));

TriangleObject tri_startGame(0x00010003, {12, 157}, {12, 173}, {30, 165}, false, RGB(255, 255, 0));
TriangleObject tri_highScore(0x00010004, {12, 177}, {12, 193}, {30, 185}, false, RGB(255, 255, 0));


ImageObject img_bgGoal(0x00010000, 0, 0, true, &bg_goal, &mask_bg_goal);
ImageObject img_textGoldminer(0x00010001, 0, 0, true, &text_goldminer, &mask_text_goldminer);

void StartMenu() {
    img_bgStartMenu.render();

    bt_startGame.render();
    bt_highScore.render();
    tri_startGame.render();
    tri_highScore.render();

    string res1 = "";
    string res2 = "";

    MOUSEMSG mouseMsg = GetMouseMsg();
    bt_startGame.handleMouseEvent(mouseMsg, &res1);
    bt_highScore.handleMouseEvent(mouseMsg, &res2);
    if (bt_startGame.getLapped()) {
        bt_startGame.setFontSize(21);
        bt_highScore.setFontSize(20);
        tri_startGame.setDisp(true);
        tri_highScore.setDisp(false);

        if (bt_startGame.getClicked()) {
            level = Level::SHOW_TARGET;
        }
    }else {
        bt_startGame.setFontSize(20);
        tri_startGame.setDisp(false);
    }

    if (bt_highScore.getLapped()) {
        bt_highScore.setFontSize(21);
        bt_startGame.setFontSize(20);
        tri_startGame.setDisp(false);
        tri_highScore.setDisp(true);

        if (bt_highScore.getClicked()) {
            level = Level::HIGH_SCORE;
        }
    }else {
        bt_highScore.setFontSize(20);
        tri_highScore.setDisp(false);
    }
}

void HighScore() {
    // img_bgGoal.render();
    // img_textGoldminer.render();
    putimage(0, 0, &mask_text_goldminer);
}

int main() {
    loadingImage(images);

    initgraph(WIDTH * scaleFactor, HEIGHT * scaleFactor);
    // setbkcolor(BLACK);
    setbkcolor(WHITE);

    level = Level::START_MENU;

    bool running = true;

    int frameCount = 0;
    auto lastTime = chrono::steady_clock::now();
    double fps = 0.0;

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
