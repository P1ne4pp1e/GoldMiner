#include "src/Console.h"
#include <windowsx.h>
#include <algorithm>
#include <cctype>

// 窗口类名
static const wchar_t* WINDOW_CLASS = L"GoldMinerConsole";

Console::Console()
    : m_hWnd(nullptr)
    , m_scrollToBottom(true)
    , m_windowWidth(800)
    , m_windowHeight(600)
    , m_scrollOffset(0)
    , m_lineHeight(20)
    , m_inputHeight(30)
    , m_toolbarHeight(30)
    , m_showCursor(true)
    , m_timerID(0)
    , m_cursorPos(0)
    , m_historyIndex(0) {
    // 清空输入缓冲区
    memset(m_inputBuf, 0, sizeof(m_inputBuf));

    // 注册窗口类
    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszClassName = WINDOW_CLASS;
    RegisterClassExW(&wc);

    // 创建窗口
    m_hWnd = CreateWindowExW(
        0,
        WINDOW_CLASS,
        L"Gold Miner Console",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        m_windowWidth, m_windowHeight,
        nullptr,
        nullptr,
        GetModuleHandle(nullptr),
        this
    );

    // 设置窗口指针
    SetWindowLongPtr(m_hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

    // 设置光标闪烁定时器
    m_timerID = SetTimer(m_hWnd, 1, 500, nullptr);

    // 注册提示文本自动命令补全
    RegisterCommand("help", [this](const std::string&) {
        AddLog("=== Gold Miner Console ===");
        AddLog("Available commands:");
        AddLog("  help      - Show this help message");
        AddLog("  clear     - Clear the console");
        AddLog("  exit      - Hide the console");
        AddLog("  version   - Show console version");
        AddLog("  game      - Game control commands (use 'game help' for details)");
        AddLog("  miner     - Control the miner character (use 'miner help' for details)");
        AddLog("  mineral   - Mineral information commands (use 'mineral help' for details)");
        AddLog("  score     - Score and goal related commands (use 'score help' for details)");
        AddLog("  debug     - Debug commands (use 'debug help' for details)");
    });

    RegisterCommand("clear", [this](const std::string&) {
        Clear();
    });

    RegisterCommand("exit", [this](const std::string&) {
        Hide();
    });

    RegisterCommand("version", [this](const std::string&) {
        AddLog("Gold Miner Console v1.0");
        AddLog("Author: 马伯龙");
    });

    // 初始隐藏窗口
    Hide();
}

Console::~Console() {
    if (m_hWnd) {
        if (m_timerID) {
            KillTimer(m_hWnd, m_timerID);
        }
        DestroyWindow(m_hWnd);
        m_hWnd = nullptr;
    }
    UnregisterClassW(WINDOW_CLASS, GetModuleHandle(nullptr));
}

LRESULT Console::HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_SIZE:
            Resize(LOWORD(lParam), HIWORD(lParam));
            return 0;

        case WM_PAINT:
            Draw();
            return 0;

        case WM_CHAR:
            if (wParam >= 32) {
                // 添加字符到输入缓冲区
                size_t len = strlen(m_inputBuf);
                if (len < sizeof(m_inputBuf) - 1) {
                    // 在光标位置插入字符
                    memmove(m_inputBuf + m_cursorPos + 1, m_inputBuf + m_cursorPos, len - m_cursorPos + 1);
                    m_inputBuf[m_cursorPos] = static_cast<char>(wParam);
                    m_cursorPos++;
                }
                InvalidateRect(m_hWnd, nullptr, TRUE);
            }
            return 0;

        case WM_KEYDOWN:
            if (wParam == VK_RETURN) {
                // 执行命令
                std::string command = m_inputBuf;
                if (!command.empty()) {
                    ExecuteCommand(command);
                    memset(m_inputBuf, 0, sizeof(m_inputBuf));
                    m_cursorPos = 0;
                    InvalidateRect(m_hWnd, nullptr, TRUE);
                }
            }
            else if (wParam == VK_BACK) {
                // 删除光标前的字符
                if (m_cursorPos > 0) {
                    size_t len = strlen(m_inputBuf);
                    memmove(m_inputBuf + m_cursorPos - 1, m_inputBuf + m_cursorPos, len - m_cursorPos + 1);
                    m_cursorPos--;
                    InvalidateRect(m_hWnd, nullptr, TRUE);
                }
            }
            else if (wParam == VK_DELETE) {
                // 删除光标后的字符
                size_t len = strlen(m_inputBuf);
                if (m_cursorPos < len) {
                    memmove(m_inputBuf + m_cursorPos, m_inputBuf + m_cursorPos + 1, len - m_cursorPos);
                    InvalidateRect(m_hWnd, nullptr, TRUE);
                }
            }
            else if (wParam == VK_LEFT && m_cursorPos > 0) {
                m_cursorPos--;
                InvalidateRect(m_hWnd, nullptr, TRUE);
            }
            else if (wParam == VK_RIGHT && m_cursorPos < strlen(m_inputBuf)) {
                m_cursorPos++;
                InvalidateRect(m_hWnd, nullptr, TRUE);
            }
            else if (wParam == VK_HOME) {
                m_cursorPos = 0;
                InvalidateRect(m_hWnd, nullptr, TRUE);
            }
            else if (wParam == VK_END) {
                m_cursorPos = strlen(m_inputBuf);
                InvalidateRect(m_hWnd, nullptr, TRUE);
            }
            else if (wParam == VK_UP) {
                // 向上浏览历史命令
                if (!m_commandHistory.empty()) {
                    if (m_historyIndex < m_commandHistory.size()) {
                        m_historyIndex++;
                        strcpy_s(m_inputBuf, m_commandHistory[m_commandHistory.size() - m_historyIndex].c_str());
                        m_cursorPos = strlen(m_inputBuf);
                        InvalidateRect(m_hWnd, nullptr, TRUE);
                    }
                }
            }
            else if (wParam == VK_DOWN) {
                // 向下浏览历史命令
                if (m_historyIndex > 0) {
                    m_historyIndex--;
                    if (m_historyIndex == 0) {
                        memset(m_inputBuf, 0, sizeof(m_inputBuf));
                    } else {
                        strcpy_s(m_inputBuf, m_commandHistory[m_commandHistory.size() - m_historyIndex].c_str());
                    }
                    m_cursorPos = strlen(m_inputBuf);
                    InvalidateRect(m_hWnd, nullptr, TRUE);
                }
            }
            else if (wParam == VK_TAB) {
                // 命令自动补全
                std::string currentInput = m_inputBuf;
                if (!currentInput.empty()) {
                    // 查找匹配的命令
                    std::string bestMatch;
                    for (const auto& pair : m_commands) {
                        if (pair.first.size() >= currentInput.size() &&
                            _strnicmp(pair.first.c_str(), currentInput.c_str(), currentInput.size()) == 0) {
                            if (bestMatch.empty() || pair.first.size() < bestMatch.size()) {
                                bestMatch = pair.first;
                            }
                        }
                    }

                    if (!bestMatch.empty()) {
                        strcpy_s(m_inputBuf, bestMatch.c_str());
                        m_cursorPos = strlen(m_inputBuf);
                        InvalidateRect(m_hWnd, nullptr, TRUE);
                    }
                }
            }
            else if (wParam == VK_ESCAPE) {
                // 隐藏控制台
                Hide();
            }
            return 0;

        case WM_TIMER:
            if (wParam == m_timerID) {
                m_showCursor = !m_showCursor;
                InvalidateRect(m_hWnd, nullptr, TRUE);
            }
            return 0;

        case WM_MOUSEWHEEL:
            // 处理滚轮事件
            m_scrollOffset -= GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA * m_lineHeight * 3;
            m_scrollOffset = std::max(0, std::min(m_scrollOffset,
                static_cast<int>(m_items.size() * m_lineHeight - (m_windowHeight - m_inputHeight - m_toolbarHeight))));
            InvalidateRect(m_hWnd, nullptr, TRUE);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void Console::Resize(int width, int height) {
    m_windowWidth = width;
    m_windowHeight = height;
    if (m_scrollToBottom) {
        m_scrollOffset = static_cast<int>(m_items.size() * m_lineHeight - (m_windowHeight - m_inputHeight - m_toolbarHeight));
        m_scrollOffset = std::max(0, m_scrollOffset);
    }
    InvalidateRect(m_hWnd, nullptr, TRUE);
}

void Console::Draw() {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(m_hWnd, &ps);

    // 创建内存DC和位图
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP memBitmap = CreateCompatibleBitmap(hdc, m_windowWidth, m_windowHeight);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, memBitmap);

    // 填充背景
    RECT rect = { 0, 0, m_windowWidth, m_windowHeight };
    HBRUSH bgBrush = CreateSolidBrush(RGB(0, 0, 0)); // 黑色背景
    FillRect(memDC, &rect, bgBrush);
    DeleteObject(bgBrush);

    // 绘制标题栏
    RECT titleRect = { 0, 0, m_windowWidth, m_toolbarHeight };
    HBRUSH titleBrush = CreateSolidBrush(RGB(32, 32, 32)); // 深灰色标题栏
    FillRect(memDC, &titleRect, titleBrush);
    DeleteObject(titleBrush);

    // 绘制标题
    SetTextColor(memDC, RGB(255, 215, 0)); // 金色文本
    SetBkMode(memDC, TRANSPARENT);
    HFONT titleFont = CreateFont(18, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                                OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                DEFAULT_PITCH | FF_DONTCARE, "Consolas");
    HFONT oldFont = (HFONT)SelectObject(memDC, titleFont);
    TextOutA(memDC, 10, 5, "Gold Miner Console", 18);
    SelectObject(memDC, oldFont);
    DeleteObject(titleFont);

    // 设置日志文本字体和颜色
    HFONT logFont = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                              OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                              DEFAULT_PITCH | FF_DONTCARE, "Consolas");
    SelectObject(memDC, logFont);
    SetTextColor(memDC, RGB(200, 200, 200)); // 浅灰色文本

    // 绘制日志
    int y = m_toolbarHeight - m_scrollOffset;
    for (const auto& item : m_items) {
        if (y + m_lineHeight >= m_toolbarHeight && y <= m_windowHeight - m_inputHeight) {
            // 根据日志类型设置颜色
            if (item.find("Error:") == 0) {
                SetTextColor(memDC, RGB(255, 100, 100)); // 错误为红色
            } else if (item.find("Warning:") == 0) {
                SetTextColor(memDC, RGB(255, 255, 100)); // 警告为黄色
            } else if (item.find("Success:") == 0) {
                SetTextColor(memDC, RGB(100, 255, 100)); // 成功为绿色
            } else if (item.find("===") == 0) {
                SetTextColor(memDC, RGB(255, 215, 0)); // 标题为金色
            } else if (item.find("Command:") == 0) {
                SetTextColor(memDC, RGB(100, 200, 255)); // 命令为蓝色
            } else {
                SetTextColor(memDC, RGB(200, 200, 200)); // 默认为浅灰色
            }

            TextOutA(memDC, 10, y, item.c_str(), static_cast<int>(item.length()));
        }
        y += m_lineHeight;
    }

    // 绘制输入框背景
    RECT inputRect = { 0, m_windowHeight - m_inputHeight, m_windowWidth, m_windowHeight };
    HBRUSH inputBrush = CreateSolidBrush(RGB(32, 32, 32)); // 深灰色输入框
    FillRect(memDC, &inputRect, inputBrush);
    DeleteObject(inputBrush);

    // 绘制输入提示符
    SetTextColor(memDC, RGB(255, 215, 0)); // 金色提示符
    TextOutA(memDC, 10, m_windowHeight - m_inputHeight + 5, ">", 1);

    // 绘制输入文本
    SetTextColor(memDC, RGB(255, 255, 255)); // 白色输入文本
    std::string inputText = m_inputBuf;
    TextOutA(memDC, 25, m_windowHeight - m_inputHeight + 5, inputText.c_str(), static_cast<int>(inputText.length()));

    // 计算光标位置
    SIZE textSize;
    GetTextExtentPoint32A(memDC, inputText.c_str(), static_cast<int>(m_cursorPos), &textSize);

    // 绘制光标
    if (m_showCursor) {
        RECT cursorRect = {
            25 + textSize.cx,
            m_windowHeight - m_inputHeight + 5,
            25 + textSize.cx + 2,
            m_windowHeight - m_inputHeight + 21
        };
        HBRUSH cursorBrush = CreateSolidBrush(RGB(255, 255, 255)); // 白色光标
        FillRect(memDC, &cursorRect, cursorBrush);
        DeleteObject(cursorBrush);
    }

    // 清理字体
    DeleteObject(logFont);

    // 将内存DC的内容复制到窗口DC
    BitBlt(hdc, 0, 0, m_windowWidth, m_windowHeight, memDC, 0, 0, SRCCOPY);

    // 清理
    SelectObject(memDC, oldBitmap);
    DeleteObject(memBitmap);
    DeleteDC(memDC);

    EndPaint(m_hWnd, &ps);
}

void Console::Clear() {
    m_items.clear();
    m_scrollOffset = 0;
    InvalidateRect(m_hWnd, nullptr, TRUE);
}

void Console::AddLog(const std::string& log) {
    m_items.push_back(log);
    if (m_scrollToBottom) {
        m_scrollOffset = static_cast<int>(m_items.size() * m_lineHeight - (m_windowHeight - m_inputHeight - m_toolbarHeight));
        m_scrollOffset = std::max(0, m_scrollOffset);
    }
    InvalidateRect(m_hWnd, nullptr, TRUE);
}

void Console::RegisterCommand(const std::string& command, std::function<void(const std::string&)> callback) {
    m_commands[command] = callback;
}

void Console::ExecuteCommand(const std::string& commandLine) {
    AddLog("> " + commandLine);

    // 添加到历史命令
    m_commandHistory.push_back(commandLine);
    if (m_commandHistory.size() > 100) {
        m_commandHistory.erase(m_commandHistory.begin());
    }
    m_historyIndex = 0;

    // 解析命令和参数
    std::string command;
    std::string params;

    size_t spacePos = commandLine.find(' ');
    if (spacePos != std::string::npos) {
        command = commandLine.substr(0, spacePos);
        params = commandLine.substr(spacePos + 1);
    } else {
        command = commandLine;
        params = "";
    }

    // 转换为小写以进行不区分大小写的比较
    std::string lowerCommand = command;
    std::transform(lowerCommand.begin(), lowerCommand.end(), lowerCommand.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    // 执行命令
    auto it = m_commands.find(lowerCommand);
    if (it != m_commands.end()) {
        it->second(params);
    } else {
        // 查找子命令（例如"game status"中的"game"部分）
        for (const auto& pair : m_commands) {
            if (lowerCommand.find(pair.first) == 0 && lowerCommand.length() > pair.first.length()) {
                char nextChar = lowerCommand[pair.first.length()];
                if (nextChar == ' ' || nextChar == '_') {
                    it->second(lowerCommand.substr(pair.first.length() + 1) + " " + params);
                    return;
                }
            }
        }

        AddLog("Error: Unknown command: " + command);
        AddLog("Type 'help' for a list of available commands.");
    }
}

void Console::Show() {
    ShowWindow(m_hWnd, SW_SHOW);
    SetForegroundWindow(m_hWnd);
    UpdateWindow(m_hWnd);
}

void Console::Hide() {
    ShowWindow(m_hWnd, SW_HIDE);
}

void Console::Toggle() {
    if (IsWindowVisible(m_hWnd)) {
        Hide();
    } else {
        Show();
    }
}

LRESULT CALLBACK Console::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    Console* console = reinterpret_cast<Console*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    if (console)
        return console->HandleMessage(hwnd, msg, wParam, lParam);
    return DefWindowProc(hwnd, msg, wParam, lParam);
}