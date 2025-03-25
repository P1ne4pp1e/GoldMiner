# 黄金矿工控制台集成指南

## 概述

本指南将帮助您集成改进的控制台系统到您的黄金矿工游戏中。这个控制台系统允许游戏开发者和玩家通过命令行与游戏交互，进行调试、测试和控制游戏的各个方面。

## 文件结构

控制台系统由以下文件组成：

1. `Console.h` - 控制台类的头文件
2. `Console.cpp` - 控制台实现
3. `GameCommands.h` - 游戏命令接口
4. `GameCommands.cpp` - 游戏命令实现

## 集成步骤

### 1. 复制文件到项目中

将提供的文件复制到您的项目目录中，确保放在正确的位置：

- `Console.h` 和 `GameCommands.h` 放在 `src/` 目录下
- `Console.cpp` 和 `GameCommands.cpp` 放在项目根目录下

### 2. 更新 CMakeLists.txt

确保在 `CMakeLists.txt` 中添加新文件：

```cmake
add_executable(GoldMiner
    # 其他源文件...
    Console.cpp
    GameCommands.cpp
)
```

### 3. 修改 main.cpp

按照提供的 `main-update.cpp` 中的代码片段，修改您的 `main.cpp` 文件。关键步骤是：

1. 包含头文件
2. 创建全局矿物管理器指针
3. 初始化控制台和命令
4. 在消息循环中处理控制台输入

### 4. 测试和验证

编译项目并运行。按 `~` 键应该能够切换控制台的显示。尝试一些基本命令如 `help`、`version` 来验证控制台是否正常工作。

## 命令系统

控制台实现了一系列命令，这些命令分为几个主要类别：

### 基本命令

- `help` - 显示帮助信息
- `clear` - 清空控制台
- `exit` - 隐藏控制台
- `version` - 显示版本信息

### 游戏控制命令

- `game status` - 显示当前游戏状态
- `game level <n>` - 设置游戏关卡
- `game pause` - 暂停游戏
- `game resume` - 恢复游戏
- `game reset` - 重置当前关卡
- `game start` - 开始新游戏
- `game target` - 显示目标分数
- `game time <n>` - 设置剩余时间（秒）

### 矿工控制命令

- `miner status` - 显示矿工状态
- `miner hook` - 立即发射钩子
- `miner angle <degrees>` - 设置钩子角度
- `miner speed <value>` - 设置钩子角速度
- `miner power <value>` - 设置钩子拉力

### 矿物相关命令

- `mineral list` - 列出所有屏幕上的矿物
- `mineral count` - 按类型统计矿物数量
- `mineral values` - 显示不同矿物的价值
- `mineral spawn <type> <x> <y>` - 生成新矿物
  - 可用类型: gold_small, gold_normal, gold_medium, gold_big, rock_small, rock_normal, rock_big, diamond, bag, skull, bone, tnt

### 分数相关命令

- `score show` - 显示当前分数和目标
- `score add <amount>` - 添加分数
- `score set <amount>` - 设置特定分数
- `score high` - 显示最高分
- `score target <amount>` - 设置目标分数

### 调试命令

- `debug fps <value>` - 设置目标帧率
- `debug info` - 显示一般调试信息
- `debug scale <value>` - 设置缩放因子
- `debug win` - 切换到通关状态（完成关卡）
- `debug lose` - 切换到失败状态（关卡失败）
- `debug hooks` - 显示钩子信息

## 扩展控制台功能

如果您想添加更多自定义命令，您可以在 `GameCommands.cpp` 文件中添加。方法如下：

```cpp
console.RegisterCommand("custom", [&console](const std::string& params) {
    if (params.empty()) {
        console.AddLog("Error: Missing parameter.");
        console.AddLog("Use 'custom help' for more information.");
        return;
    }

    std::istringstream iss(params);
    std::string subCommand;
    iss >> subCommand;

    if (subCommand == "help") {
        console.AddLog("=== Custom Command Help ===");
        console.AddLog("  custom action - Do something");
        // 更多帮助...
    }
    else if (subCommand == "action") {
        // 实现您的自定义操作
        console.AddLog("Custom action performed!");
    }
    else {
        console.AddLog("Error: Unknown subcommand: " + subCommand);
        console.AddLog("Use 'custom help' for more information.");
    }
});
```

## 美化控制台输出

控制台支持不同颜色的文本输出，这些颜色是通过识别消息前缀来设置的：

- `Error:` - 红色文本
- `Warning:` - 黄色文本
- `Success:` - 绿色文本
- `===` - 金色文本（标题）
- `Command:` - 蓝色文本

您可以在命令实现中使用这些前缀来提供视觉反馈，例如：

```cpp
console.AddLog("Error: Something went wrong!");
console.AddLog("Warning: This might not work as expected.");
console.AddLog("Success: Operation completed successfully!");
console.AddLog("=== Important Section ===");
console.AddLog("Command: game start");
```

## 热键绑定

当前控制台系统使用以下热键：

- `~` (波浪号键) - 切换控制台显示
- `ESC` (Escape键) - 隐藏控制台
- `↑↓` (上下箭头) - 浏览命令历史
- `Tab` - 命令自动补全

如果您想更改这些热键，可以修改 `Console.cpp` 中的相应处理代码。

## 完整功能列表

控制台提供以下功能：

1. 命令历史记录浏览
2. 命令自动补全
3. 文本颜色编码
4. 光标位置编辑
5. 滚动查看
6. 窗口大小调整
7. 显示/隐藏切换

## 命令示例

以下是一些常用命令示例：

```
help
game status
miner hook
mineral spawn diamond 150 120
score add 1000
debug info
```

## 故障排除

如果控制台不正常工作，请检查以下几点：

1. 确保已正确包含所有文件
2. 检查控制台的初始化代码是否正确
3. 确保全局矿物管理器指针已正确设置
4. 检查波浪号键的状态检测代码是否正确
5. 查看游戏的消息循环是否正确处理控制台消息

## 性能考虑

控制台在显示时可能会略微影响游戏性能，特别是在处理大量日志消息时。如果您发现性能问题，可以考虑：

1. 减少日志更新的频率
2. 限制显示的日志条目数量
3. 仅在调试模式下启用某些高开销命令