#ifndef MINERAL_MANAGER_H
#define MINERAL_MANAGER_H

#include "LevelCfg.h"
#include "Mineral.h"

// 在src/MineralManager.h中
class MineralManager {
public:
    MineralManager();
    ~MineralManager();

    void initializeMinerals(Level level); // 根据关卡初始化矿物
    void update(double dt);              // 更新所有矿物
    void render();                       // 渲染所有矿物
    void cleanupMinerals();              // 清理矿物

    std::vector<Mineral*>& getMinerals(); // 获取矿物列表

    static std::map<std::string, Mineral::MineralType> mineralMap;

private:
    std::vector<Mineral*> minerals;      // 当前关卡的所有矿物

    // 辅助方法
    void createMineral(int x, int y, Mineral::MineralType type, vector<int>& x_range, vector<int>& y_range);
    void createExplosive(int x, int y);
};


#endif