# 黄金矿工控制台实现方案

## 概述

我已经完成了黄金矿工游戏控制台的全面实现。这个控制台系统专为黄金矿工游戏设计，具有丰富的命令集，让您可以控制游戏的各个方面，包括矿工操作、矿物管理、分数调整和游戏调试等。

## 实现的文件

我已经创建了以下文件：

1. **Console.h** - 控制台类的头文件，定义了控制台的接口和功能
2. **Console.cpp** - 控制台的实现，包括窗口处理、命令解析、输入输出等
3. **GameCommands.h** - 游戏命令接口，定义了初始化游戏命令的函数
4. **GameCommands.cpp** - 游戏命令实现，包含所有特定于黄金矿工的命令
5. **main-update.cpp** - 修改main.cpp的代码片段，用于集成控制台
6. **integration-guide.md** - 详细的集成指南

## 控制台特点

新开发的控制台具有以下特点：

1. **美观的用户界面**
   - 黑色背景，不同颜色的文本（错误为红色，警告为黄色，成功为绿色等）
   - 输入提示符和闪烁光标
   - 可调整大小的窗口

2. **高级输入功能**
   - 命令历史记录浏览（上下箭头键）
   - 命令自动补全（Tab键）
   - 文本编辑功能（光标移动，删除字符等）

3. **丰富的命令系统**
   - 基本命令：help, clear, exit, version
   - 游戏控制命令：game status, game level, game pause, game resume等
   - 矿工控制命令：miner hook, miner angle, miner speed, miner power等
   - 矿物相关命令：mineral list, mineral count, mineral values, mineral spawn等
   - 分数相关命令：score show, score add, score set, score high, score target等
   - 调试命令：debug fps, debug info, debug scale, debug win, debug lose, debug hooks等

4. **完善的文档**
   - 每个命令都有help子命令提供详细帮助信息
   - 详细的集成指南和使用说明

## 如何使用

### 基本操作

1. 按 `~` 键显示/隐藏控制台
2. 输入命令并按回车执行
3. 按 ESC 键隐藏控制台
4. 使用上下箭头键浏览历史命令
5. 使用Tab键自动补全命令

### 游戏控制示例

```
game status                  # 显示当前游戏状态
game level 2                 # 切换到第2关
game pause                   # 暂停游戏
game resume                  # 恢复游戏
game reset                   # 重置当前关卡
game time 60                 # 设置剩余时间为60秒
```

### 矿工控制示例

```
miner status                 # 显示矿工状态
miner hook                   # 立即发射钩子
miner angle 45               # 设置钩子角度为45度
miner speed 100              # 设置钩子摆动速度
miner power 200              # 设置钩子拉力
```

### 矿物管理示例

```
mineral list                 # 列出所有矿物
mineral count                # 按类型统计矿物
mineral values               # 显示各类矿物价值
mineral spawn diamond 150 120 # 在(150,120)位置生成一个钻石
```

### 分数控制示例

```
score show                   # 显示当前分数和目标
score add 500                # 添加500分
score set 1000               # 设置分数为1000
score high                   # 查看最高分
score target 2000            # 设置目标分数为2000
```

### 调试功能示例

```
debug info                   # 显示游戏调试信息
debug fps 60                 # 设置目标帧率为60
debug scale 2.5              # 设置缩放因子为2.5
debug win                    # 强制完成当前关卡
debug hooks                  # 显示钩子详细信息
```

## 集成步骤

请按照集成指南文档中的详细步骤，将控制台系统集成到您的黄金矿工游戏中。主要步骤包括：

1. 将提供的代码文件添加到项目中
2. 更新CMakeLists.txt
3. 修改main.cpp添加控制台初始化和消息处理代码
4. 编译并测试

## 技术细节

控制台系统使用Windows API创建一个独立的窗口，与主游戏窗口并行运行。控制台内部维护自己的命令历史、输入缓冲区和显示缓冲区。它通过全局变量与游戏系统交互，对游戏状态进行读取和修改。

控制台的命令系统使用了基于std::function的回调机制，允许轻松扩展新命令。每个命令都是一个可以接受参数字符串的函数对象，使命令定义和实现保持简洁清晰。

## 扩展和自定义

控制台系统设计为易于扩展和自定义。您可以通过以下方式扩展功能：

1. 在GameCommands.cpp中添加新命令
2. 修改Console.cpp中的绘制代码，自定义界面外观
3. 添加新的命令类别
4. 扩展现有命令的功能

## 总结

这个控制台系统为黄金矿工游戏提供了强大的调试、测试和控制功能，使游戏开发和测试更加便捷。它既可以作为开发工具，也可以作为游戏的一部分提供给高级玩家使用。