#include <bits/stdc++.h>
#include <graphics.h>
using namespace std;

#define IMG_BG_START_MENU "./images/bg_start_menu.png"

IMAGE bg_start_menu;

struct Images {
    IMAGE* name;
    string path;
    int width;
    int height;
    Images(IMAGE* name, string path, int width, int height) : name(name), path(path), width(width), height(height) {}
};

Images BG_START_MENU(&bg_start_menu, IMG_BG_START_MENU, 320, 240);

vector<Images> images = {
    BG_START_MENU
};