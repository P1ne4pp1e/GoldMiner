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




void HighScore() {
    txt_panelLine1.setX(20);
    txt_panelLine1.setX(75);
    txt_panelLine1.setY(100);

    img_bgGoal.render();
    img_textGoldminer.render();
    img_panel.render();

    txt_panelLine1.setText("High Score: ");
    txt_panelLine2_1.setText( "$" + to_string(player["player"]["HIGHSCORE"].as<int>()) );
    txt_panelLine2_2.setX(txt_panelLine2_1.getX() + txt_panelLine2_1.getWidth() + 7.0);

    switch (player["player"]["HIGHLEVEL"].as<int>()) {
        case 1:
            txt_panelLine2_2.setText( _T("at Level1") );
        break;
        case 2:
            txt_panelLine2_2.setText( _T("at Level2") );
        break;
        case 3:
            txt_panelLine2_2.setText( _T("at Level3") );
        break;
        case 4:
            txt_panelLine2_2.setText( _T("at Level4") );
        break;
        case 5:
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