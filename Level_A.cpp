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

#define HEIGHT 240
#define WIDTH 320


double hookNowAngVel = player["hook"]["hookAngularVelocity"].as<double>();


// 辅助函数
void handleHookMineral(MineralManager& mineralManager) {
    // 如果钩子正在伸出（状态1）
    if (hookState == 1) {
        // 获取钩子位置
        Object::Point hookPos = rope.getEnd();

        // 检查是否与任何矿物碰撞
        for (auto mineral : mineralManager.getMinerals()) {
            // 碰撞检测和抓取逻辑...
        }
    }

    // 如果钩子正在返回（状态2）
    if (hookState == 2) {
        // 更新被抓住的矿物位置
        for (auto mineral : mineralManager.getMinerals()) {
            if (mineral->isHooked()) {
                // 更新位置...
            }
        }

        // 钩子返回顶部的处理...
    }
}


void Level1(MineralManager& mineralManager) {
    static int getMass = 0;

    txt_timeValue.setText(to_string(60-int(timer.elapsed())));
    ani_hookSheet.setPivot(6.5, 0);

    // 更新矿物
    mineralManager.update(frameTime);

    // cout << &mineralManager << " " << mineralManager.getMinerals().size() << endl;

    // 钩子逻辑
    if (rope.getAngle()<=15) {
        rope.setAngularVelocity(player["hook"]["hookAngularVelocity"].as<double>());
    }
    if (rope.getAngle()>=165) {
        rope.setAngularVelocity(-player["hook"]["hookAngularVelocity"].as<double>());
    }

    ani_hookSheet.setX(rope.getLengthPoint(-7.5).x - 6.5);
    ani_hookSheet.setY(rope.getLengthPoint(-7.5).y);
    ani_hookSheet.setAngle(90-rope.getAngle());

    // 按下键抓取
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        if (hookState == 0) {
            hookState = 1;
        }
    }

    // 处理钩子与矿物的碰撞
    if (hookState == 1) {
        ani_miner.setFrameOrder({2});
        getMass = 0;
        for (auto mineral : mineralManager.getMinerals()) {
            if (!mineral->isHooked() && mineral->getDisplayed()) {
                Object::Point hookPos = rope.getEnd();
                Object::Point center = mineral->getCenter();
                double dx = hookPos.x - center.x;
                double dy = hookPos.y - center.y;
                double distance = sqrt(dx*dx + dy*dy);

                if (distance <= mineral->getRadius() + 5) { // 10是钩子半径
                    mineral->setHooked(true);

                    hookState = 2;
                    ani_miner.setFrameOrder({0, 1, 2});
                    ani_miner.setFrameDuration(-player["hook"]["hookVel"][hookState].as<int>() * 0.0004 * mineral->getMass());
                    getMass = mineral->getMass();
                    // cout << getMass << endl;

                    break;
                }
            }
        }
    }

    // 检查钩子边界
    if (rope.getEnd().x <= 0.05 * WIDTH || rope.getEnd().x >= 0.95 * WIDTH || rope.getEnd().y >= 0.95 * HEIGHT) {
        if (hookState == 1) {
            hookState = 2;
            ani_miner.setFrameOrder({0, 1, 2});
            ani_miner.setFrameDuration(-player["hook"]["hookVel"][hookState].as<double>() * 0.00075);
        }
    }

    // 更新被抓住的矿物位置
    if (hookState == 2) {
        for (auto mineral : mineralManager.getMinerals()) {
            if (mineral->isHooked()) {
                Object::Point hookPos = rope.getLengthPoint(-7.5);
                mineral->setX(hookPos.x);
                mineral->setY(hookPos.y);
            }
        }
    }

    // 钩子返回到顶部
    if (rope.getLength() <= player["hook"]["hookLength"].as<double>()) {
        if (hookState == 2) {
            getMass = 0;
            // 处理抓到的矿物
            auto& minerals = mineralManager.getMinerals();
            for (auto it = minerals.begin(); it != minerals.end(); ) {
                if ((*it)->isHooked()) {
                    // 增加分数
                    SCORE += (*it)->getValue();

                    // 删除矿物
                    delete *it;
                    it = minerals.erase(it);
                } else {
                    ++it;
                }
            }

            hookState = 0;
            ani_miner.setFrameOrder({0});
        }
    }

    // 钩子角速度控制
    if (rope.getAngularVelocity() != 0) {
        hookNowAngVel = rope.getAngularVelocity();
    }

    if (hookState != 0) {
        rope.setAngularVelocity(0);
    } else {
        rope.setAngularVelocity(hookNowAngVel);
    }

    rope.addLength((player["hook"]["hookVel"][hookState].as<double>() + getMass*8) * frameTime);

    // cout << getMass << " " << (player["hook"]["hookVel"][hookState].as<double>() + getMass*8) << endl;

    // 更新对象
    rope.update(frameTime);
    ani_hookSheet.update();
    ani_miner.update();

    // 渲染背景
    img_bgTop.render();
    img_bgLevelA.render();
    ani_miner.render();
    rope.render();
    ani_hookSheet.render();

    // 渲染矿物
    mineralManager.render();

    ani_hookSheet.setFrameOrder({1});
    ani_hookSheet.render();
    ani_hookSheet.setFrameOrder({0});

    // 渲染UI
    txt_moneyTitle.render();
    txt_moneyValue.render();
    txt_goalTitle.render();
    txt_goalValue.render();
    txt_timeTitle.render();
    txt_timeValue.render();
    txt_levelTitle.render();
    txt_levelValue.render();
}