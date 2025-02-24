#include "Commands.h"

void InitializeDefaultCommands(Console& console) {
    // 注册清屏命令
    console.RegisterCommand("clear", [&console](const std::string&) {
        console.Clear();
    });

    // 注册帮助命令
    console.RegisterCommand("help", [&console](const std::string&) {
        console.AddLog("Available commands:");
        console.AddLog("  clear - Clear the console");
        console.AddLog("  help  - Show this help message");
        console.AddLog("  test  - Add a test message");
    });

    // 注册测试命令
    console.RegisterCommand("test", [&console](const std::string&) {
        console.AddLog("This is a test message!");
    });
}