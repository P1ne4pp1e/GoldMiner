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


#define HEIGHT 240
#define WIDTH 320


double hookNowAngVel = hookAngularVelocity;



void Level1() {
    txt_timeValue.setText(to_string(60-int(timer.elapsed())));
    ani_hookSheet.setPivot(6.5, 0);


    // cout << rope.getAngle() <<endl;
    if (rope.getAngle()<=15) {
        rope.setAngularVelocity(hookAngularVelocity);
    }
    if (rope.getAngle()>=165) {
        rope.setAngularVelocity(-hookAngularVelocity);
    }
    // cout << rope.getAngularVelocity() << " " << rope.getAngle() << " ";

    ani_hookSheet.setX(rope.getLengthPoint(-7.5).x - 6.5);
    ani_hookSheet.setY(rope.getLengthPoint(-7.5).y);

    ani_hookSheet.setAngle(90-rope.getAngle());


    if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        if (hookState == 0) {
            hookState = 1;
        }
    }

    if (rope.getEnd().x <= 0.05 * WIDTH || rope.getEnd().x >= 0.95 * WIDTH || rope.getEnd().y >= 0.95 * HEIGHT) {
        if (hookState == 1) {
            hookState = 2;
            ani_miner.setFrameOrder({0, 1, 2});
            ani_miner.setFrameDuration(-hookVel[hookState] * 0.0006);
        }
    }

    if (rope.getLength() <= hookLength) {
        if (hookState == 2) {
            hookState = 0;
            ani_miner.setFrameOrder({0});
        }
    }


    if (rope.getAngularVelocity() != 0) {
        hookNowAngVel = rope.getAngularVelocity();
    }

    if (hookState != 0) {
        rope.setAngularVelocity(0);
    }else {
        rope.setAngularVelocity(hookNowAngVel);
    }

    rope.addLength(hookVel[hookState] * frameTime);

    // cout << frameTime << endl;
    rope.update(frameTime);
    ani_hookSheet.update();
    ani_miner.update();

    img_bgTop.render();
    img_bgLevelA.render();

    // ani_miner.setFrameDuration(0.2);
    // ani_miner.addAngle(1);

    // rope.addAngle(1);

    ani_miner.render();


    rope.render();
    ani_hookSheet.render();

    txt_moneyTitle.render();
    txt_moneyValue.render();

    txt_goalTitle.render();
    txt_goalValue.render();

    txt_timeTitle.render();
    txt_timeValue.render();

    txt_levelTitle.render();
    txt_levelValue.render();
}