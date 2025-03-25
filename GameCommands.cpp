#include "src/GameCommands.h"
#include "src/levelCfg.h"
#include "src/MineralManager.h"
#include "src/Console.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

// 外部变量，在游戏中需要暴露给控制台
extern MineralManager* g_mineralManager;
extern Timer timer;

void InitializeGameCommands(Console& console) {
    // --------------------------------
    // 游戏控制命令
    // --------------------------------
    console.RegisterCommand("game", [&console](const std::string& params) {
        if (params.empty()) {
            console.AddLog("Error: Missing game command parameter.");
            console.AddLog("Use 'game help' for more information.");
            return;
        }

        std::istringstream iss(params);
        std::string subCommand;
        iss >> subCommand;

        if (subCommand == "help") {
            console.AddLog("=== Game Control Commands ===");
            console.AddLog("  game status   - Display current game status");
            console.AddLog("  game level <n> - Set game level (1-5)");
            console.AddLog("  game pause    - Pause the game");
            console.AddLog("  game resume   - Resume the game");
            console.AddLog("  game reset    - Reset the current level");
            console.AddLog("  game start    - Start a new game");
            console.AddLog("  game target   - Show target score for current level");
            console.AddLog("  game time <n> - Set remaining time (seconds)");
        }
        else if (subCommand == "status") {
            std::string statusStr = "Current game status:";

            // 获取当前关卡信息
            switch (level) {
                case START_MENU:
                    statusStr += " In Start Menu";
                    break;
                case SHOW_TARGET:
                    statusStr += " Showing Target";
                    break;
                case HIGH_SCORE:
                    statusStr += " In High Score Menu";
                    break;
                case SUCCEEDLEVEL:
                    statusStr += " Level Complete";
                    break;
                case FAILEDLEVEL:
                    statusStr += " Level Failed";
                    break;
                case LEVEL_1:
                    statusStr += " Playing Level 1";
                    break;
                case LEVEL_2:
                    statusStr += " Playing Level 2";
                    break;
                case LEVEL_3:
                    statusStr += " Playing Level 3";
                    break;
                case LEVEL_4:
                    statusStr += " Playing Level 4";
                    break;
                case LEVEL_5:
                    statusStr += " Playing Level 5";
                    break;
            }

            statusStr += " | Score: " + std::to_string(SCORE);
            statusStr += " | Target: " + std::to_string(targetScore);
            statusStr += " | Time: " + std::to_string(int(levels["LevelTime"].as<int>() - timer.elapsed())) + "s";

            console.AddLog(statusStr);
        }
        else if (subCommand == "level") {
            int newLevel;
            if (iss >> newLevel) {
                if (newLevel >= 1 && newLevel <= 5) {
                    levelNum = newLevel;
                    switch (newLevel) {
                        case 1: level = LEVEL_1; break;
                        case 2: level = LEVEL_2; break;
                        case 3: level = LEVEL_3; break;
                        case 4: level = LEVEL_4; break;
                        case 5: level = LEVEL_5; break;
                    }

                    // 初始化这个关卡的矿物
                    if (g_mineralManager) {
                        g_mineralManager->initializeMinerals(level);
                    }

                    // 重置计时器
                    timer.reset();

                    console.AddLog("Success: Game level set to " + std::to_string(newLevel));
                } else {
                    console.AddLog("Error: Level must be between 1 and 5.");
                }
            } else {
                console.AddLog("Error: Missing level number parameter.");
                console.AddLog("Usage: game level <number> (1-5)");
            }
        }
        else if (subCommand == "pause") {
            // 暂停游戏逻辑
            timer.pause();
            console.AddLog("Success: Game paused.");
        }
        else if (subCommand == "resume") {
            // 恢复游戏逻辑
            timer.resume();
            console.AddLog("Success: Game resumed.");
        }
        else if (subCommand == "reset") {
            // 重置当前关卡
            timer.reset();

            // 重置钩子状态
            hookState = 0;
            rope.setLength(player["hook"]["hookLength"].as<double>());
            rope.setAngle(90);
            getMass = 0;

            // 重置矿物
            if (g_mineralManager) {
                g_mineralManager->cleanupMinerals();
                g_mineralManager->initializeMinerals(level);
            }

            console.AddLog("Success: Current level reset.");
        }
        else if (subCommand == "start") {
            // 开始新游戏
            SCORE = 0;
            levelNum = 1;
            level = SHOW_TARGET;
            timer.reset();
            console.AddLog("Success: New game started.");
        }
        else if (subCommand == "target") {
            // 显示目标分数
            console.AddLog("Current target score: " + std::to_string(targetScore));
        }
        else if (subCommand == "time") {
            int newTime;
            if (iss >> newTime) {
                if (newTime > 0) {
                    // 计算已经过去的时间
                    double elapsedTime = timer.elapsed();
                    // 设置新的剩余时间（通过调整计时器的起始时间）
                    timer.reset();
                    timer.start();
                    // 将计时器调整到与剩余时间对应的位置
                    double adjustedElapsed = levels["LevelTime"].as<int>() - newTime;
                    // 模拟经过的时间
                    for (int i = 0; i < (int)(adjustedElapsed * 100); i++) {
                        timer.elapsed();
                    }
                    console.AddLog("Success: Game time set to " + std::to_string(newTime) + " seconds.");
                } else {
                    console.AddLog("Error: Time must be positive.");
                }
            } else {
                console.AddLog("Error: Missing time parameter.");
                console.AddLog("Usage: game time <seconds>");
            }
        }
        else {
            console.AddLog("Error: Unknown game command: " + subCommand);
            console.AddLog("Use 'game help' for more information.");
        }
    });

    // --------------------------------
    // 矿工控制命令
    // --------------------------------
    console.RegisterCommand("miner", [&console](const std::string& params) {
        if (params.empty()) {
            console.AddLog("Error: Missing miner command parameter.");
            console.AddLog("Use 'miner help' for more information.");
            return;
        }

        std::istringstream iss(params);
        std::string subCommand;
        iss >> subCommand;

        if (subCommand == "help") {
            console.AddLog("=== Miner Commands ===");
            console.AddLog("  miner status   - Display miner status");
            console.AddLog("  miner hook     - Launch hook immediately");
            console.AddLog("  miner angle <degrees> - Set hook angle");
            console.AddLog("  miner speed <value> - Set hook angular velocity");
            console.AddLog("  miner power <value> - Set hook pull power");
        }
        else if (subCommand == "status") {
            std::ostringstream status;
            status << "Miner status:";
            status << " Angle: " << rope.getAngle() << "°";
            status << " | Length: " << rope.getLength();
            status << " | State: ";

            switch (hookState) {
                case 0: status << "Ready"; break;
                case 1: status << "Extending"; break;
                case 2: status << "Retracting"; break;
                default: status << "Unknown"; break;
            }

            status << " | Mass: " << getMass;

            console.AddLog(status.str());
        }
        else if (subCommand == "hook") {
            if (hookState == 0) {
                hookState = 1; // 设置为发射状态
                console.AddLog("Success: Hook launched!");
            } else {
                console.AddLog("Error: Hook already in use.");
            }
        }
        else if (subCommand == "angle") {
            float newAngle;
            if (iss >> newAngle) {
                if (newAngle >= 0 && newAngle <= 180) {
                    if (hookState == 0) {
                        rope.setAngle(newAngle);
                        console.AddLog("Success: Hook angle set to " + std::to_string(newAngle) + "°");
                    } else {
                        console.AddLog("Error: Cannot change angle while hook is in use.");
                    }
                } else {
                    console.AddLog("Error: Angle must be between 0 and 180 degrees.");
                }
            } else {
                console.AddLog("Error: Missing angle parameter.");
                console.AddLog("Usage: miner angle <degrees>");
            }
        }
        else if (subCommand == "speed") {
            double newSpeed;
            if (iss >> newSpeed) {
                if (newSpeed >= 0 && newSpeed <= 200) {
                    // 更新角速度
                    if (hookState == 0) {
                        player["hook"]["hookAngularVelocity"] = newSpeed;
                        rope.setAngularVelocity(player["hook"]["hookAngularVelocity"].as<double>());
                        console.AddLog("Success: Hook angular velocity set to " + std::to_string(newSpeed));
                    } else {
                        console.AddLog("Error: Cannot change speed while hook is in use.");
                    }
                } else {
                    console.AddLog("Error: Speed must be between 0 and 200.");
                }
            } else {
                console.AddLog("Error: Missing speed parameter.");
                console.AddLog("Usage: miner speed <value>");
            }
        }
        else if (subCommand == "power") {
            double newPower;
            if (iss >> newPower) {
                if (newPower >= 50 && newPower <= 500) {
                    // 更新钩子速度（影响力量）
                    player["hook"]["hookVel"][2] = -newPower;
                    console.AddLog("Success: Hook pull power set to " + std::to_string(newPower));
                } else {
                    console.AddLog("Error: Power must be between 50 and 500.");
                }
            } else {
                console.AddLog("Error: Missing power parameter.");
                console.AddLog("Usage: miner power <value>");
            }
        }
        else {
            console.AddLog("Error: Unknown miner command: " + subCommand);
            console.AddLog("Use 'miner help' for more information.");
        }
    });

    // --------------------------------
    // 矿物信息命令
    // --------------------------------
    console.RegisterCommand("mineral", [&console](const std::string& params) {
        if (params.empty()) {
            console.AddLog("Error: Missing mineral command parameter.");
            console.AddLog("Use 'mineral help' for more information.");
            return;
        }

        std::istringstream iss(params);
        std::string subCommand;
        iss >> subCommand;

        if (subCommand == "help") {
            console.AddLog("=== Mineral Commands ===");
            console.AddLog("  mineral list     - List all minerals on screen");
            console.AddLog("  mineral count    - Count minerals by type");
            console.AddLog("  mineral values   - Show values of different minerals");
            console.AddLog("  mineral spawn <type> <x> <y> - Spawn a new mineral");
        }
        else if (subCommand == "list") {
            if (g_mineralManager) {
                auto& minerals = g_mineralManager->getMinerals();

                if (minerals.empty()) {
                    console.AddLog("No minerals found in the current level.");
                    return;
                }

                console.AddLog("=== Current Minerals (" + std::to_string(minerals.size()) + ") ===");

                int count = 0;
                for (auto mineral : minerals) {
                    std::ostringstream mineralInfo;
                    mineralInfo << "Mineral #" << ++count << ": ";

                    // 获取类型名称
                    std::string typeName;
                    switch (mineral->getType()) {
                        case Mineral::GOLD_MINI: typeName = "Small Gold"; break;
                        case Mineral::GOLD_NORMAL: typeName = "Normal Gold"; break;
                        case Mineral::GOLD_NORMAL_PLUS: typeName = "Medium Gold"; break;
                        case Mineral::GOLD_BIG: typeName = "Big Gold"; break;
                        case Mineral::ROCK_MINI: typeName = "Small Rock"; break;
                        case Mineral::ROCK_NORMAL: typeName = "Normal Rock"; break;
                        case Mineral::ROCK_BIG: typeName = "Big Rock"; break;
                        case Mineral::DIAMOND: typeName = "Diamond"; break;
                        case Mineral::QUESTION_BAG: typeName = "Mystery Bag"; break;
                        case Mineral::SKULL: typeName = "Skull"; break;
                        case Mineral::BONE: typeName = "Bone"; break;
                        case Mineral::TNT: typeName = "TNT"; break;
                        default: typeName = "Unknown"; break;
                    }

                    mineralInfo << typeName;
                    mineralInfo << " at (" << mineral->getX() << ", " << mineral->getY() << ")";
                    mineralInfo << " Value: $" << mineral->getValue();
                    mineralInfo << " Mass: " << mineral->getMass();

                    if (mineral->isHooked()) {
                        mineralInfo << " [HOOKED]";
                    }

                    console.AddLog(mineralInfo.str());
                }
            } else {
                console.AddLog("Error: Mineral manager not initialized.");
            }
        }
        else if (subCommand == "count") {
            if (g_mineralManager) {
                auto& minerals = g_mineralManager->getMinerals();

                if (minerals.empty()) {
                    console.AddLog("No minerals found in the current level.");
                    return;
                }

                // 按类型计数
                std::map<Mineral::MineralType, int> counts;
                for (auto mineral : minerals) {
                    counts[mineral->getType()]++;
                }

                console.AddLog("=== Mineral Counts ===");

                if (counts[Mineral::GOLD_MINI] > 0)
                    console.AddLog("Small Gold: " + std::to_string(counts[Mineral::GOLD_MINI]));
                if (counts[Mineral::GOLD_NORMAL] > 0)
                    console.AddLog("Normal Gold: " + std::to_string(counts[Mineral::GOLD_NORMAL]));
                if (counts[Mineral::GOLD_NORMAL_PLUS] > 0)
                    console.AddLog("Medium Gold: " + std::to_string(counts[Mineral::GOLD_NORMAL_PLUS]));
                if (counts[Mineral::GOLD_BIG] > 0)
                    console.AddLog("Big Gold: " + std::to_string(counts[Mineral::GOLD_BIG]));
                if (counts[Mineral::ROCK_MINI] > 0)
                    console.AddLog("Small Rock: " + std::to_string(counts[Mineral::ROCK_MINI]));
                if (counts[Mineral::ROCK_NORMAL] > 0)
                    console.AddLog("Normal Rock: " + std::to_string(counts[Mineral::ROCK_NORMAL]));
                if (counts[Mineral::ROCK_BIG] > 0)
                    console.AddLog("Big Rock: " + std::to_string(counts[Mineral::ROCK_BIG]));
                if (counts[Mineral::DIAMOND] > 0)
                    console.AddLog("Diamond: " + std::to_string(counts[Mineral::DIAMOND]));
                if (counts[Mineral::QUESTION_BAG] > 0)
                    console.AddLog("Mystery Bag: " + std::to_string(counts[Mineral::QUESTION_BAG]));
                if (counts[Mineral::SKULL] > 0)
                    console.AddLog("Skull: " + std::to_string(counts[Mineral::SKULL]));
                if (counts[Mineral::BONE] > 0)
                    console.AddLog("Bone: " + std::to_string(counts[Mineral::BONE]));
                if (counts[Mineral::TNT] > 0)
                    console.AddLog("TNT: " + std::to_string(counts[Mineral::TNT]));

                console.AddLog("Total: " + std::to_string(minerals.size()));
            } else {
                console.AddLog("Error: Mineral manager not initialized.");
            }
        }
        else if (subCommand == "values") {
            console.AddLog("=== Mineral Values ===");
            console.AddLog("Small Gold: $50");
            console.AddLog("Normal Gold: $100");
            console.AddLog("Medium Gold: $250");
            console.AddLog("Big Gold: $500");
            console.AddLog("Small Rock: $11");
            console.AddLog("Normal Rock: $20");
            console.AddLog("Big Rock: $100");
            console.AddLog("Diamond: $600");
            console.AddLog("Mystery Bag: $? (random)");
            console.AddLog("Skull: $20");
            console.AddLog("Bone: $7");
            console.AddLog("TNT: $2");
        }
        else if (subCommand == "spawn") {
            std::string typeStr;
            int x, y;

            if (!(iss >> typeStr >> x >> y)) {
                console.AddLog("Error: Missing parameters.");
                console.AddLog("Usage: mineral spawn <type> <x> <y>");
                console.AddLog("Available types: gold_small, gold_normal, gold_medium, gold_big, rock_small, rock_normal, rock_big, diamond, bag, skull, bone, tnt");
                return;
            }

            // 检查坐标范围
            if (x < 0 || x > 320 || y < 40 || y > 240) {
                console.AddLog("Error: Coordinates out of range. X must be 0-320, Y must be 40-240.");
                return;
            }

            // 转换类型字符串为矿物类型
            Mineral::MineralType type;

            if (typeStr == "gold_small") type = Mineral::GOLD_MINI;
            else if (typeStr == "gold_normal") type = Mineral::GOLD_NORMAL;
            else if (typeStr == "gold_medium") type = Mineral::GOLD_NORMAL_PLUS;
            else if (typeStr == "gold_big") type = Mineral::GOLD_BIG;
            else if (typeStr == "rock_small") type = Mineral::ROCK_MINI;
            else if (typeStr == "rock_normal") type = Mineral::ROCK_NORMAL;
            else if (typeStr == "rock_big") type = Mineral::ROCK_BIG;
            else if (typeStr == "diamond") type = Mineral::DIAMOND;
            else if (typeStr == "bag") type = Mineral::QUESTION_BAG;
            else if (typeStr == "skull") type = Mineral::SKULL;
            else if (typeStr == "bone") type = Mineral::BONE;
            else if (typeStr == "tnt") type = Mineral::TNT;
            else {
                console.AddLog("Error: Unknown mineral type: " + typeStr);
                console.AddLog("Available types: gold_small, gold_normal, gold_medium, gold_big, rock_small, rock_normal, rock_big, diamond, bag, skull, bone, tnt");
                return;
            }

            if (g_mineralManager) {
                // 创建范围向量
                std::vector<int> x_range = {x, x+1};
                std::vector<int> y_range = {y, y+1};

                // 使用矿物管理器的创建方法
                g_mineralManager->createMineral(x, y, type, x_range, y_range);
                console.AddLog("Success: Spawned " + typeStr + " at (" + std::to_string(x) + ", " + std::to_string(y) + ")");
            } else {
                console.AddLog("Error: Mineral manager not initialized.");
            }
        }
        else {
            console.AddLog("Error: Unknown mineral command: " + subCommand);
            console.AddLog("Use 'mineral help' for more information.");
        }
    });

    // --------------------------------
    // 分数相关命令
    // --------------------------------
    console.RegisterCommand("score", [&console](const std::string& params) {
        if (params.empty()) {
            console.AddLog("Error: Missing score command parameter.");
            console.AddLog("Use 'score help' for more information.");
            return;
        }

        std::istringstream iss(params);
        std::string subCommand;
        iss >> subCommand;

        if (subCommand == "help") {
            console.AddLog("=== Score Commands ===");
            console.AddLog("  score show     - Show current score and target");
            console.AddLog("  score add <amount> - Add to score");
            console.AddLog("  score set <amount> - Set score to specific value");
            console.AddLog("  score high     - Show high score");
            console.AddLog("  score target <amount> - Set target score");
        }
        else if (subCommand == "show") {
            console.AddLog("Current Score: $" + std::to_string(SCORE));
            console.AddLog("Target Score: $" + std::to_string(targetScore));
            console.AddLog("Remaining: $" + std::to_string(std::max(0, targetScore - SCORE)));
        }
        else if (subCommand == "add") {
            int amount;
            if (iss >> amount) {
                SCORE += amount;
                console.AddLog("Success: Added $" + std::to_string(amount) + " to score.");
                console.AddLog("Current Score: $" + std::to_string(SCORE));
            } else {
                console.AddLog("Error: Missing amount parameter.");
                console.AddLog("Usage: score add <amount>");
            }
        }
        else if (subCommand == "set") {
            int amount;
            if (iss >> amount) {
                if (amount >= 0) {
                    SCORE = amount;
                    console.AddLog("Success: Score set to $" + std::to_string(SCORE));
                } else {
                    console.AddLog("Error: Score cannot be negative.");
                }
            } else {
                console.AddLog("Error: Missing amount parameter.");
                console.AddLog("Usage: score set <amount>");
            }
        }
        else if (subCommand == "high") {
            console.AddLog("High Score: $" + std::to_string(player["player"]["HIGHSCORE"].as<int>()));
            console.AddLog("Achieved at Level: " + std::to_string(player["player"]["HIGHLEVEL"].as<int>()));
        }
        else if (subCommand == "target") {
            int amount;
            if (iss >> amount) {
                if (amount > 0) {
                    targetScore = amount;
                    console.AddLog("Success: Target score set to $" + std::to_string(targetScore));
                } else {
                    console.AddLog("Error: Target score must be positive.");
                }
            } else {
                console.AddLog("Error: Missing amount parameter.");
                console.AddLog("Usage: score target <amount>");
            }
        }
        else {
            console.AddLog("Error: Unknown score command: " + subCommand);
            console.AddLog("Use 'score help' for more information.");
        }
    });

    // --------------------------------
    // 调试命令
    // --------------------------------
    console.RegisterCommand("debug", [&console](const std::string& params) {
        if (params.empty()) {
            console.AddLog("Error: Missing debug command parameter.");
            console.AddLog("Use 'debug help' for more information.");
            return;
        }

        std::istringstream iss(params);
        std::string subCommand;
        iss >> subCommand;

        if (subCommand == "help") {
            console.AddLog("=== Debug Commands ===");
            console.AddLog("  debug fps <value> - Set target FPS");
            console.AddLog("  debug info      - Show general debug info");
            console.AddLog("  debug scale <value> - Set scale factor");
            console.AddLog("  debug win       - Toggle win state (complete level)");
            console.AddLog("  debug lose      - Toggle lose state (fail level)");
            console.AddLog("  debug hooks     - Display hook information");
        }
        else if (subCommand == "fps") {
            int newFps;
            if (iss >> newFps) {
                if (newFps >= 0 && newFps <= 240) {
                    targetFPS = newFps;
                    console.AddLog("Success: Target FPS set to " + std::to_string(targetFPS));
                } else {
                    console.AddLog("Error: FPS must be between 0 and 240 (0 = uncapped).");
                }
            } else {
                console.AddLog("Current Target FPS: " + std::to_string(targetFPS));
            }
        }
        else if (subCommand == "info") {
            std::ostringstream info;
            info << "=== Debug Information ===\n";
            info << "Frame Time: " << std::fixed << std::setprecision(4) << frameTime << "s\n";
            info << "Target FPS: " << targetFPS << "\n";
            info << "Scale Factor: " << scaleFactor << "\n";
            info << "Timer Elapsed: " << timer.elapsed() << "s\n";
            info << "Minerals: " << (g_mineralManager ? g_mineralManager->getMinerals().size() : 0) << "\n";
            info << "Hook State: " << hookState << "\n";

            console.AddLog(info.str());
        }
        else if (subCommand == "scale") {
            double newScale;
            if (iss >> newScale) {
                if (newScale >= 1.0 && newScale <= 4.0) {
                    scaleFactor = newScale;
                    console.AddLog("Success: Scale factor set to " + std::to_string(scaleFactor));
                    console.AddLog("Warning: You may need to restart the game for this to take full effect.");
                } else {
                    console.AddLog("Error: Scale must be between 1.0 and 4.0.");
                }
            } else {
                console.AddLog("Current Scale Factor: " + std::to_string(scaleFactor));
            }
        }
        else if (subCommand == "win") {
            // 强制通过当前关卡
            level = SUCCEEDLEVEL;
            timer.reset();
            console.AddLog("Success: Level completed.");
        }
        else if (subCommand == "lose") {
            // 强制失败当前关卡
            level = FAILEDLEVEL;
            timer.reset();
            console.AddLog("Success: Level failed.");
        }
        else if (subCommand == "hooks") {
            std::ostringstream hookInfo;
            hookInfo << "=== Hook Information ===\n";
            hookInfo << "Current Hook State: " << hookState << " (";
            switch (hookState) {
                case 0: hookInfo << "Ready"; break;
                case 1: hookInfo << "Extending"; break;
                case 2: hookInfo << "Retracting"; break;
                default: hookInfo << "Unknown"; break;
            }
            hookInfo << ")\n";

            hookInfo << "Hook Position: (" << rope.getEnd().x << ", " << rope.getEnd().y << ")\n";
            hookInfo << "Hook Angle: " << rope.getAngle() << "°\n";
            hookInfo << "Hook Length: " << rope.getLength() << "\n";
            hookInfo << "Hook Angular Velocity: " << rope.getAngularVelocity() << "\n";
            hookInfo << "Hook Velocity Settings:\n";
            hookInfo << "  Idle: " << player["hook"]["hookVel"][0].as<double>() << "\n";
            hookInfo << "  Extend: " << player["hook"]["hookVel"][1].as<double>() << "\n";
            hookInfo << "  Retract: " << player["hook"]["hookVel"][2].as<double>() << "\n";

            console.AddLog(hookInfo.str());
        }
        else {
            console.AddLog("Error: Unknown debug command: " + subCommand);
            console.AddLog("Use 'debug help' for more information.");
        }
    });
}