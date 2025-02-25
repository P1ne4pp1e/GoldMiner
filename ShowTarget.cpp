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

    if ( timer.elapsed() > 1.0 ) {
        timer.reset();
        level = Level::LEVEL_1;
    }


    if (GetAsyncKeyState(VK_BACK) & 0x8000) {
        level = Level::START_MENU;
    }
}