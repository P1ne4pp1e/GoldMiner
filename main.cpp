#include <bits/stdc++.h>
#include <graphics.h>
#include <conio.h>
#include <filesystem>

#include "imgCfg.h"
#include "levelCfg.h"

#define HEIGHT 240
#define WIDTH 320

const double scaleFactor = 3.5;

using namespace std;
namespace fs = std::filesystem;

void loadingImage(const vector<Images>& images) {
    for (int i = 0; i < images.size(); i++) {
        loadimage(images[i].name, IMG_BG_START_MENU, images[i].width * scaleFactor, images[i].height * scaleFactor);
    }
}

int main() {
    loadingImage(images);

    initgraph(WIDTH * scaleFactor, HEIGHT * scaleFactor);
    outtext("Hello World!");
    putimage(0, 0, &bg_start_menu);

    getch();
    closegraph();

    return 0;
}
