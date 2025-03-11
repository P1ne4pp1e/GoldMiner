#include "src/MineralManager.h"

MineralManager::MineralManager() {
    // 初始化随机种子
    srand(static_cast<unsigned int>(time(nullptr)));
}

MineralManager::~MineralManager() {
    cleanupMinerals();
}

void MineralManager::initializeMinerals(Level level) {
    // 清理之前的矿物
    cleanupMinerals();

    // 随机种子
    srand(time(nullptr));

    // 根据关卡设定不同的矿物数量和分布
    switch(level) {
        case LEVEL_1:
            // 创建金块
            for (int i = 0; i < 3; i++) {
                int x = 50 + rand() % 220;
                int y = 100 + rand() % 100;
                createMineral(x, y, Mineral::GOLD_MINI);
            }

            for (int i = 0; i < 2; i++) {
                int x = 50 + rand() % 220;
                int y = 100 + rand() % 100;
                createMineral(x, y, Mineral::GOLD_NORMAL);
            }

            createMineral(100 + rand() % 120, 150 + rand() % 50, Mineral::GOLD_BIG);

            // 创建石头
            for (int i = 0; i < 5; i++) {
                int x = 40 + rand() % 240;
                int y = 90 + rand() % 120;
                createMineral(x, y, Mineral::ROCK_MINI);
            }

            // 创建钻石
            if (rand() % 100 < 30) { // 30%几率出现钻石
                createMineral(70 + rand() % 180, 160 + rand() % 40, Mineral::DIAMOND);
            }

            // 创建神秘袋子
            if (rand() % 100 < 50) { // 50%几率出现神秘袋子
                createMineral(70 + rand() % 180, 140 + rand() % 60, Mineral::QUESTION_BAG);
            }

    //        // 创建地鼠
    //        if (rand() % 100 < 40) { // 40%几率出现地鼠
    //            createMoving(50 + rand() % 200, 180 + rand() % 30, Mineral::MOLE);
    //        }

            // 创建TNT
            if (rand() % 100 < 20) { // 20%几率出现TNT
                createExplosive(70 + rand() % 180, 120 + rand() % 80);
            }

            break;

        // 其他关卡...
    }
}

void MineralManager::update(double dt) {
    for (auto mineral : minerals) {
        mineral->update();
    }
}

void MineralManager::render() {
    for (auto mineral : minerals) {
        mineral->render();
    }
}

void MineralManager::cleanupMinerals() {
    for (auto mineral : minerals) {
        delete mineral;
    }
    minerals.clear();
}

std::vector<Mineral*>& MineralManager::getMinerals() {
    return minerals;
}

void MineralManager::createMineral(int x, int y, Mineral::MineralType type) {
    IMAGE* img = nullptr;
    IMAGE* mask = nullptr;

    switch (type) {
        case Mineral::GOLD_MINI:
            img = &gold_mini;
            mask = &mask_gold_mini;
            break;
        case Mineral::GOLD_NORMAL:
            img = &gold_normal;
            mask = &mask_gold_normal;
            break;
        case Mineral::GOLD_BIG:
            img = &gold_big;
            mask = &mask_gold_big;
            break;

        case Mineral::ROCK_MINI:
            img = &rock_mini;
            mask = &mask_rock_mini;
            break;
        case Mineral::ROCK_NORMAL:
            img = &rock_normal;
            mask = &mask_rock_normal;
            break;
        case Mineral::ROCK_BIG:
            img = &rock_big;
            mask = &mask_rock_big;
            break;


        case Mineral::DIAMOND:
            img = &diamond;
            mask = &mask_diamond;
            break;
        case Mineral::QUESTION_BAG:
            img = &question_bag;
            mask = &mask_question_bag;
            break;
        case Mineral::SKULL:
            img = &skull;
            mask = &mask_skull;
            break;
        case Mineral::BONE:
            img = &bone;
            mask = &mask_bone;
            break;

        default:
            return; // 不是金块类型
    }

    minerals.push_back(new Mineral(0x00030000 + minerals.size(), x, y, true, type, img, mask));
}


void MineralManager::createExplosive(int x, int y) {
    minerals.push_back(new Mineral(0x00030300 + minerals.size(), x, y, true, Mineral::TNT, &tnt, &mask_tnt));
}