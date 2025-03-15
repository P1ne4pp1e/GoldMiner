#include <bits/stdc++.h>
#include <graphics.h>
#include <conio.h>
#include <filesystem>
#include <chrono>
#include <windows.h>

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

#include "src/Console.h"
#include "src/Commands.h"

#include <yaml-cpp/yaml.h>

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
        IMAGE img1, img2;
        loadimage(&img1, images[i].path.c_str(), images[i].width, images[i].height);
        nearestNeighborScale(&img1, images[i].name, images[i].width * scaleFactor, images[i].height * scaleFactor);
    }
}




YAML::Node player = LoadData("src/yaml/player.yaml");
YAML::Node entities = LoadData("src/yaml/entities.yaml");
YAML::Node levels = LoadData("src/yaml/levels.yaml");

int main() {
#ifdef EnableConsole
    Console console;

    // 初始化默认命令
    InitializeDefaultCommands(console);

    // 添加欢迎消息
    console.AddLog("Welcome to the Console!");
    console.AddLog("Type 'help' for available commands.");

    console.Hide();
#endif

    loadingImage(images);

    initgraph(WIDTH * scaleFactor, HEIGHT * scaleFactor);
    // setbkcolor(BLACK);
    setbkcolor(GREEN);


    // 创建矿物管理器
    MineralManager mineralManager;


    level = Level::START_MENU;


    int frameCount = 0;
    auto lastTime = chrono::steady_clock::now();
    double fps = 0.0;

    // 帧率控制相关变量
    Timer frameTimer;                              // 帧计时器


    ani_miner.setFrameOrder({0});
    ani_hookSheet.setFrameOrder({0});


    // 消息循环
    MSG msg = {};

#ifdef EnableConsole
    // 添加~键状态跟踪变量
    static bool prevTildeState = false;
#endif


    timer.start();
    frameTimer.start();  // 开始测量本帧时间
    while (running) {
        frameTimer.reset();
        // static IMAGE img, img1, img2(64, 80), img3;
        // loadimage(&img, "./images/miner_sheet.png");

        auto currentTime = chrono::steady_clock::now();
        frameCount++;

        // 每半秒更新一次帧率
        if (chrono::duration_cast<chrono::milliseconds>(currentTime - lastTime).count() >= 500) {
            fps = frameCount / (chrono::duration_cast<chrono::milliseconds>(currentTime - lastTime).count() / 1000.0);
            lastTime = currentTime;
            frameCount = 0;
        }

        // 如果关卡改变，初始化矿物
        static Level prevLevel = level;
        if (prevLevel != level) {
            if (level == Level::LEVEL_1 || level == Level::LEVEL_2 ||
                level == Level::LEVEL_3 || level == Level::LEVEL_4 || level == Level::LEVEL_5) {
                    mineralManager.initializeMinerals(level);
                }
            prevLevel = level;
        }


        BeginBatchDraw();
        cleardevice();

        txt_moneyValue.setText("$"+to_string(SCORE));
        txt_goalValue.setText("$"+to_string(targetScore));
        switch (level) {
            case Level::LEVEL_1:
                txt_levelValue.setText( _T("1") );
            break;
            case Level::LEVEL_2:
                txt_levelValue.setText( _T("2") );
            break;
            case Level::LEVEL_3:
                txt_levelValue.setText( _T("3") );
            break;
            case Level::LEVEL_4:
                txt_levelValue.setText( _T("4") );
            break;
            case Level::LEVEL_5:
                txt_levelValue.setText( _T("5") );
            break;
            default:
                txt_levelValue.setText( _T("0") );
        }


        switch (level) {
            case START_MENU:
                StartMenu();
                break;
            case HIGH_SCORE:
                HighScore();
                break;
            case SHOW_TARGET:
                ShowTarget();
                break;
            case SUCCEEDLEVEL:
                SucceedLevel();
                break;
            case FAILEDLEVEL:
                FailedLevel();
                break;
            case LEVEL_1:
                mineralManager.update(frameTime);
                Level1(mineralManager); // 修改Level1函数以接收矿物管理器
                break;
        }

        SET_SINGLE_FONT(15, 0, "Pixel Square", "fonts/Pixel-Square-10-1.ttf");
        // SET_SINGLE_FONT(15, 0, "04b_21", "fonts/digit.ttf");
        settextcolor(RGB(255, 255, 255));
        outtextxy(WIDTH * scaleFactor - 80, 10, "FPS ");
        outtextxy(WIDTH * scaleFactor - textwidth(to_string(static_cast<int>(fps)).c_str()) - 5, 10, to_string(static_cast<int>(fps)).c_str());

        // smoothScale(&img, &img1, 512, 80);
        // putimage(50, 180, &img1);
        // SetWorkingImage(&img2);
        // putimage(0, 0, 64, 80, &img1, 256, 0);
        // SetWorkingImage();
        // rotateimage(&img3, &img2, angle_tmp * PI / 180.0, BLACK, true);
        // putimage(50, 300, &img2);
        // putimage(50, 420, &img3);
        // angle_tmp += 1;

        if (GetAsyncKeyState(VK_DELETE) & 0x8000) {
            running = false;
        }

#ifdef EnableConsole
        bool currentTildeState = (GetAsyncKeyState(VK_OEM_3) & 0x8000);
        if (currentTildeState && !prevTildeState) {
            console.Toggle();  // 切换控制台状态
            consoleDisplayed = !consoleDisplayed;
            cout << "Console Displayed: " << consoleDisplayed << endl;
        }
        prevTildeState = currentTildeState;
#endif


        EndBatchDraw();

        // cout << frameTimer.elapsed() << endl;

#ifdef EnableConsole
        if (consoleDisplayed) {
            running = GetMessage(&msg, nullptr, 0, 0);

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
#endif

        // 帧率控制
        frameTime = frameTimer.elapsed();  // 获取本帧实际耗时
        if (targetFPS > 0) {
            const double targetFrameTime = 1.0 / targetFPS; // 目标每帧时间（秒）

            // cout << frameTimer.elapsed() << " " << targetFrameTime << " ";
            // 动态休眠控制（纳秒精度）
            if (frameTime < targetFrameTime) {
                // 计算需要休眠的时间（纳秒）
                frameTime = frameTimer.elapsed();  // 获取本帧实际耗时
                double sleepTime = (targetFrameTime * 1e9 - frameTime * 1e9); // 转换为纳秒
                spinWait(std::chrono::duration<double, std::nano>(sleepTime).count());

                frameTime = targetFrameTime;
            }
        }
    }

    // 清理资源
    mineralManager.cleanupMinerals();

    closegraph();

    return 0;
}
