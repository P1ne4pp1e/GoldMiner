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