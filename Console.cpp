#include "Console.h"
#include <windowsx.h>
#include <algorithm>

// 窗口类名
static const wchar_t* WINDOW_CLASS = L"ConsoleWindow";

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
    wc.lpszClassName = WINDOW_CLASS;
    RegisterClassExW(&wc);

    // 创建窗口
    m_hWnd = CreateWindowExW(
        0,
        WINDOW_CLASS,
        L"Console",
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

    // 显示窗口
    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);
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
                    memmove(m_inputBuf + m_cursorPos + 1, m_inputBuf + m_cursorPos, len - m_cursorPos);
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
            else if (wParam == VK_LEFT && m_cursorPos > 0) {
                m_cursorPos--;
                InvalidateRect(m_hWnd, nullptr, TRUE);
            }
            else if (wParam == VK_RIGHT && m_cursorPos < strlen(m_inputBuf)) {
                m_cursorPos++;
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
            return 0;

        case WM_TIMER:
            if (wParam == m_timerID) {
                m_showCursor = !m_showCursor;
                InvalidateRect(m_hWnd, nullptr, TRUE);
            }
            return 0;

        case WM_MOUSEWHEEL:
            // 处理滚轮事件
            m_scrollOffset += GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA * m_lineHeight;
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
    FillRect(memDC, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));

    // 设置文本颜色和背景模式
    SetTextColor(memDC, RGB(255, 255, 255));
    SetBkMode(memDC, TRANSPARENT);

    // 绘制日志
    int y = m_toolbarHeight - m_scrollOffset;
    for (const auto& item : m_items) {
        if (y + m_lineHeight >= m_toolbarHeight && y <= m_windowHeight - m_inputHeight) {
            TextOutA(memDC, 10, y, item.c_str(), static_cast<int>(item.length()));
        }
        y += m_lineHeight;
    }

    // 绘制输入框背景
    RECT inputRect = { 0, m_windowHeight - m_inputHeight, m_windowWidth, m_windowHeight };
    HBRUSH lightGrayBrush = CreateSolidBrush(RGB(230, 230, 230));
    FillRect(memDC, &inputRect, lightGrayBrush);
    DeleteObject(lightGrayBrush);

    // 设置输入文本颜色为黑色
    SetTextColor(memDC, RGB(0, 0, 0));
    
    // 绘制输入文本和光标
    std::string inputText = m_inputBuf;
    TextOutA(memDC, 10, m_windowHeight - m_inputHeight + 5, inputText.c_str(), static_cast<int>(inputText.length()));
    
    // 计算光标位置
    SIZE textSize;
    GetTextExtentPoint32A(memDC, inputText.c_str(), static_cast<int>(m_cursorPos), &textSize);
    
    // 绘制光标
    if (m_showCursor) {
        RECT cursorRect = {
            10 + textSize.cx,
            m_windowHeight - m_inputHeight + 18,
            10 + textSize.cx + 8,
            m_windowHeight - m_inputHeight + 20
        };
        FillRect(memDC, &cursorRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
    }

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

void Console::ExecuteCommand(const std::string& command) {
    AddLog("> " + command);
    // 添加到历史命令
    m_commandHistory.push_back(command);
    m_historyIndex = 0;
    
    auto it = m_commands.find(command);
    if (it != m_commands.end()) {
        it->second(command);
    } else {
        AddLog("Unknown command: " + command);
    }
    // 重置光标位置
    m_cursorPos = 0;
}

void Console::Show() {
    ShowWindow(m_hWnd, SW_SHOW);
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