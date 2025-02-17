#include <bits/stdc++.h>
#include <graphics.h>
#include <conio.h>
#include <filesystem>

#include "imgCfg.h"
#include "levelCfg.h"

#define HEIGHT 240
#define WIDTH 320

#define SET_SINGLE_FONT(height, width, fontName, fontPath) \
do { \
AddFontResourceEx(fontPath, FR_PRIVATE, 0); \
settextstyle(height, width, _T(fontName)); \
} while(0)


const double scaleFactor = 2.0;

using namespace std;
namespace fs = std::filesystem;

void loadingImage(const vector<Images>& images) {
    for (int i = 0; i < images.size(); i++) {
        loadimage(images[i].name, _T(IMG_BG_START_MENU), images[i].width * scaleFactor, images[i].height * scaleFactor);
    }
}

int main() {
    loadingImage(images);

    initgraph(WIDTH * scaleFactor, HEIGHT * scaleFactor);
    outtext(_T("Hello World!"));
    putimage(0, 0, &bg_start_menu);

    SET_SINGLE_FONT(20 * scaleFactor, 0, "Kurland", "fonts/Kurland.ttf");
    setbkmode(TRANSPARENT);
    settextcolor(RGB(255, 255, 0));
    outtextxy(35 * scaleFactor, 155 * scaleFactor, _T("Start Game"));
    outtextxy(35 * scaleFactor, 175 * scaleFactor, _T("High Score"));

    getch();
    closegraph();

    return 0;
}
