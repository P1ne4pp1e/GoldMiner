#include "src/MineralManager.h"

std::map<std::string, Mineral::MineralType> MineralManager::mineralMap = {
    {"MiniGold", Mineral::GOLD_MINI},
    {"NormalGold", Mineral::GOLD_NORMAL},
    {"NormalGoldPlus", Mineral::GOLD_NORMAL_PLUS},
    {"BigGold", Mineral::GOLD_BIG},
    {"MiniRock", Mineral::ROCK_MINI},
    {"NormalRock", Mineral::ROCK_NORMAL},
    {"BigRock", Mineral::ROCK_BIG},
    {"Diamond", Mineral::DIAMOND},
    {"Skull", Mineral::SKULL},
    {"Bone", Mineral::BONE},
    {"QuestionBag", Mineral::QUESTION_BAG},
    {"Mole", Mineral::MOLE},
    {"MoleWithDiamond", Mineral::MOLE_WITH_DIAMOND},
};


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
            YAML::Node config = levels["Level1"];
            cout << "Size: " << config.size() << endl;
            for (const auto& item : config) {
                // cout << item << "\n" << mineralMap.size() << "\n\n";
                for (auto mine = mineralMap.begin(); mine != mineralMap.end(); ++mine) {
                    // cout << mine->first << endl;
                    if (item[mine->first]) {
                        string name = mine->first;
                        Mineral::MineralType type = mine->second;
                        YAML::Node param = item[name];
                        // cout << "Mineral: \n" << param << endl;

                        vector<int> x_range, y_range;

                        x_range = {
                            param["range"]["x"][0].as<int>(),
                            param["range"]["x"][1].as<int>(),
                        };
                        y_range = {
                            param["range"]["y"][0].as<int>(),
                            param["range"]["y"][1].as<int>(),
                        };

                        for (int i = 0; i < param["num"]["min"].as<int>(); i++) {
                            createMineral(-1, -1, type, x_range, y_range);
                        }
                        for (int i = param["num"]["min"].as<int>(); i < param["num"]["max"].as<int>(); i++) {
                            if (rand() % 100 <= param["prob"].as<double>() * 100) {
                                createMineral(-1, -1, type, x_range, y_range);
                            }
                        }
                    }
                }
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

void MineralManager::createMineral(int x, int y, Mineral::MineralType type, vector<int>& x_range, vector<int>& y_range) {
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

    if (x == -1 && y == -1) {
        int wid = x_range[1] - x_range[0] - img->getwidth();
        int hei = y_range[1] - y_range[0] - img->getheight();
        x = rand() % wid + x_range[0];
        y = rand() % hei + y_range[0];
    }

    minerals.push_back(new Mineral(0x00030000 + minerals.size(), x, y, true, type, img, mask));
}


void MineralManager::createExplosive(int x, int y) {
    minerals.push_back(new Mineral(0x00030300 + minerals.size(), x, y, true, Mineral::TNT, &tnt, &mask_tnt));
}