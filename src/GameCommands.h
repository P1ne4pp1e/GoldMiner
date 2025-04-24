#pragma once
#include "Console.h"
#include "MineralManager.h""
// 在GameCommands.h中
extern MineralManager* g_mineralManager;

// 初始化所有游戏相关命令
void InitializeGameCommands(Console& console);