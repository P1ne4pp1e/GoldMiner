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
#include "src/Console.h"

void ShowTarget() {
    txt_panelLine1.setX(20);
    txt_panelLine1.setX(75);
    txt_panelLine1.setY(100);

    img_bgGoal.render();
    img_textGoldminer.render();
    img_panel.render();

    switch (level) {
        case Level::LEVEL_1:
            txt_panelLine1.setText("Your First Goal is");
            targetScore = levels["Level1"][0]["TargetScore"].as<int>();
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
            targetScore = levels["Level1"][0]["TargetScore"].as<int>();
    }
    txt_panelLine2_1.setText( "$" + to_string(targetScore) );

    txt_panelLine1.render();
    txt_panelLine2_1.render();


    if ( timer.elapsed() > showTargetInterval || ((GetAsyncKeyState(VK_SPACE) & 0x8000) && !console.IsVisible())) {
        timer.reset();

        ani_miner.setFrameOrder({0});
        ani_hookSheet.setFrameOrder({0});

        hookState = 0;
        rope.setLength(player["hook"]["hookLength"].as<double>());
        getMass = 0;
        switch (levelNum) {
            case 0:
                level = Level::LEVEL_1;
                levelNum = 1;
                break;
        }
    }
}