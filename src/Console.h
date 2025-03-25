#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <cstdint>

// Add this function to Console.h (public section):


class Console {
public:
    Console();
    ~Console();

    // 窗口消息处理
    LRESULT HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    // 调整窗口大小
    void Resize(int width, int height);

    // 绘制窗口内容
    void Draw();

    // 清空控制台
    void Clear();

    // 添加日志
    void AddLog(const std::string& log);

    // 注册命令
    void RegisterCommand(const std::string& command, std::function<void(const std::string&)> callback);

    // 执行命令
    void ExecuteCommand(const std::string& command);

    // 显示窗口
    void Show();

    // 隐藏窗口
    void Hide();

    // 切换窗口显示状态
    void Toggle();

    // 获取窗口句柄
    HWND GetHandle() const { return m_hWnd; }

    // 窗口过程函数
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


    /**
     * Check if the console is currently visible
     * @return true if console is visible, false otherwise
     */
    bool IsVisible() const {
        return IsWindowVisible(m_hWnd);
    }

private:
    HWND m_hWnd;                     // 窗口句柄
    std::vector<std::string> m_items; // 日志条目
    char m_inputBuf[256];            // 输入缓冲区

    // 命令回调映射 (不区分大小写)
    std::map<std::string, std::function<void(const std::string&)>> m_commands;

    // 历史命令相关
    std::vector<std::string> m_commandHistory;  // 历史命令容器
    size_t m_historyIndex;                     // 当前历史命令索引

    // 滚动相关
    bool m_scrollToBottom;
    int m_windowWidth;
    int m_windowHeight;
    int m_scrollOffset;
    int m_lineHeight;
    int m_inputHeight;
    int m_toolbarHeight;
    bool m_showCursor;     // 光标显示状态
    UINT_PTR m_timerID;    // 光标闪烁计时器ID
    size_t m_cursorPos;    // 光标位置
};


extern Console console;
