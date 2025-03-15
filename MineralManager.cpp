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
            // cout << "Size: " << config.size() << endl;
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
            return; // 不是支持的矿物类型
    }

    int imgWidth = img->getwidth() / scaleFactor;
    int imgHeight = img->getheight() / scaleFactor;

    // 如果已经指定坐标，直接使用
    if (x != -1 && y != -1) {
        minerals.push_back(new Mineral(0x00030000 + minerals.size(), x, y, true, type, img, mask));
        return;
    }

    // 创建一个网格来表示可放置区域
    const int spacing = 5; // 矿物之间的最小间距
    const int cellSize = 5; // 网格单元大小

    int gridWidth = (x_range[1] - x_range[0]) / cellSize + 1;
    int gridHeight = (y_range[1] - y_range[0]) / cellSize + 1;

    // 创建并初始化占用网格
    vector<vector<bool>> occupied(gridWidth, vector<bool>(gridHeight, false));

    // 标记已被占用的网格单元
    for (auto mineral : minerals) {
        int minX = (mineral->getX() - x_range[0] - spacing) / cellSize;
        int minY = (mineral->getY() - y_range[0] - spacing) / cellSize;
        int maxX = (mineral->getX() + mineral->getWidth() + spacing - x_range[0]) / cellSize;
        int maxY = (mineral->getY() + mineral->getHeight() + spacing - y_range[0]) / cellSize;

        // 确保边界有效
        minX = max(0, minX);
        minY = max(0, minY);
        maxX = min(gridWidth - 1, maxX);
        maxY = min(gridHeight - 1, maxY);

        // 标记占用区域
        for (int i = minX; i <= maxX; i++) {
            for (int j = minY; j <= maxY; j++) {
                occupied[i][j] = true;
            }
        }
    }

    // 收集所有可用的网格单元
    vector<pair<int, int>> availableCells;
    for (int i = 0; i < gridWidth; i++) {
        for (int j = 0; j < gridHeight; j++) {
            // 检查当前单元是否可放置矿物
            if (!occupied[i][j]) {
                // 检查是否有足够的空间放置矿物
                bool hasEnoughSpace = true;
                int requiredCellsX = (imgWidth + spacing) / cellSize + 1;
                int requiredCellsY = (imgHeight + spacing) / cellSize + 1;

                // 检查右侧和下方是否有足够的空间
                for (int dx = 0; dx < requiredCellsX && hasEnoughSpace; dx++) {
                    for (int dy = 0; dy < requiredCellsY && hasEnoughSpace; dy++) {
                        int checkX = i + dx;
                        int checkY = j + dy;
                        if (checkX >= gridWidth || checkY >= gridHeight || occupied[checkX][checkY]) {
                            hasEnoughSpace = false;
                        }
                    }
                }

                if (hasEnoughSpace) {
                    availableCells.push_back({i, j});
                }
            }
        }
    }

    // 如果没有可用空间，返回
    if (availableCells.empty()) {
        // cout << "No available space for new mineral!" << endl;
        return;
    }

    // 随机选择一个可用空间
    int index = rand() % availableCells.size();
    int gridX = availableCells[index].first;
    int gridY = availableCells[index].second;

    // 转换回实际坐标
    x = x_range[0] + gridX * cellSize;
    y = y_range[0] + gridY * cellSize;

    // 创建矿物
    minerals.push_back(new Mineral(0x00030000 + minerals.size(), x, y, true, type, img, mask));
}


void MineralManager::createExplosive(int x, int y) {
    minerals.push_back(new Mineral(0x00030300 + minerals.size(), x, y, true, Mineral::TNT, &tnt, &mask_tnt));
}