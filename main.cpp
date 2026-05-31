#include <windows.h>
#include <tchar.h>
#include <string>
#include <cstdio>

// 原程序的快捷键检测宏
#define p(k) (GetAsyncKeyState(k) & 0x8000)

// 按钮ID定义
#define BTN_HIDE_JIYU 101
#define BTN_SHOW_JIYU 102
#define BTN_HIDE_SELF 103
#define BTN_SHOW_SELF 104
#define BTN_KILL_JIYU 105
#define BTN_START_JIYU 106
#define BTN_TASKMGR 107
#define BTN_KILL_JIZHI 108
#define BTN_ABOUT 109
#define BTN_EXIT 110


HWND g_hMainWnd = NULL;
bool g_bHideJiyu = false;
const TCHAR* g_szAppTitle = _T("信息课工具箱 V2.0");
const TCHAR* g_szDisclaimer = 
    _T("免责声明：\n")
    _T("本程序仅供参考学习，您利用本程序进行的任何行为(包括但不限于:\n")
    _T("扰乱课堂纪律、考试作弊、违反学校规章制度等)均需由自己承担所有后果！\n\n")
    _T("使用协议：\n")
    _T("您可以无偿使用本程序，但您不得将本程序进行出售，也不得修改本程序的任何部分！\n\n")
    _T("如果您无法遵守以上内容，请自行删除本程序！\n")
    _T("点“取消”表示你不同意协议，将退出程序；\n点“确定”代表你通义协议，进入程序。\n\n") 
    _T("By 公鸡集团 2026/5/25");

// 杀集智函数
void KILLjizhi() {
    // 第一遍杀进程
    system("taskkill /f /im bacdbootcopy.exe >nul 2>&1");
    system("taskkill /f /im DeploymentAgent.exe >nul 2>&1");
    system("taskkill /f /im certmgr.exe >nul 2>&1");
    system("taskkill /f /im PortControl64.exe >nul 2>&1");
    system("taskkill /f /im refreship.exe >nul 2>&1");
    system("taskkill /f /im tvnserver.exe >nul 2>&1");
    system("taskkill /f /im tvnserver32.exe >nul 2>&1");
    system("taskkill /f /im vncviewer.exe >nul 2>&1");
    system("taskkill /f /im WFBSMlogon.exe >nul 2>&1");
    system("taskkill /f /im WFBSMon.exe >nul 2>&1");
    system("taskkill /f /im WfbsPnpInstall.exe >nul 2>&1");
    system("taskkill /f /im XYNTService.exe >nul 2>&1");
    
    // 第二遍杀进程（确保彻底）
    system("taskkill /f /im bcdbootcopy.exe >nul 2>&1");
    system("taskkill /f /im DeploymentAgent.exe >nul 2>&1");
    system("taskkill /f /im certmgr.exe >nul 2>&1");
    system("taskkill /f /im PortControl64.exe >nul 2>&1");
    system("taskkill /f /im refreship.exe >nul 2>&1");
    system("taskkill /f /im tvnserver.exe >nul 2>&1");
    system("taskkill /f /im tvnserver32.exe >nul 2>&1");
    system("taskkill /f /im vncviewer.exe >nul 2>&1");
    system("taskkill /f /im WFBSMlogon.exe >nul 2>&1");
    system("taskkill /f /im WFBSMon.exe >nul 2>&1");
    system("taskkill /f /im WfbsPnpInstall.exe >nul 2>&1");
    system("taskkill /f /im XYNTService.exe >nul 2>&1");
    
    MessageBox(g_hMainWnd, _T("杀集智操作已完成\n您现在可以随意插入U盘了"), _T("操作成功"), MB_OK | MB_ICONINFORMATION);
}

// 窗口过程函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            // 创建按钮
            int x = 20, y = 20, btnWidth = 180, btnHeight = 30, spacing = 15;
            
            // 极域操作组
            CreateWindow(_T("BUTTON"), _T("隐藏极域 (Alt+↓)"), 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                x, y, btnWidth, btnHeight, hWnd, (HMENU)BTN_HIDE_JIYU, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            
            CreateWindow(_T("BUTTON"), _T("显示极域 (Alt+↑)"), 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                x + btnWidth + spacing, y, btnWidth, btnHeight, hWnd, (HMENU)BTN_SHOW_JIYU, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            
            y += btnHeight + spacing;
            
            CreateWindow(_T("BUTTON"), _T("隐藏本程序 (Alt+PgDn)"), 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                x, y, btnWidth, btnHeight, hWnd, (HMENU)BTN_HIDE_SELF, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            
            CreateWindow(_T("BUTTON"), _T("显示本程序 (Alt+PgUp)"), 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                x + btnWidth + spacing, y, btnWidth, btnHeight, hWnd, (HMENU)BTN_SHOW_SELF, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            
            y += btnHeight + spacing + 20; // 分组间距
            
            // 核心功能组
            CreateWindow(_T("BUTTON"), _T("强制关闭极域 (Alt+F2)"), 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                x, y, btnWidth, btnHeight, hWnd, (HMENU)BTN_KILL_JIYU, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            
            CreateWindow(_T("BUTTON"), _T("启动极域 (Alt+F3)"), 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                x + btnWidth + spacing, y, btnWidth, btnHeight, hWnd, (HMENU)BTN_START_JIYU, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            
            y += btnHeight + spacing;
            
            CreateWindow(_T("BUTTON"), _T("打开任务管理器 (Alt+F7)"), 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                x, y, btnWidth, btnHeight, hWnd, (HMENU)BTN_TASKMGR, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            
            CreateWindow(_T("BUTTON"), _T("杀集智 (Alt+F8)"), 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                x + btnWidth + spacing, y, btnWidth, btnHeight, hWnd, (HMENU)BTN_KILL_JIZHI, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            
            y += btnHeight + spacing + 20; // 分组间距
            
            // 其他功能组
            CreateWindow(_T("BUTTON"), _T("使用协议 (Alt+F9)"), 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                x, y, btnWidth, btnHeight, hWnd, (HMENU)BTN_ABOUT, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            
            CreateWindow(_T("BUTTON"), _T("退出程序 (Alt+Del)"), 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                x + btnWidth + spacing, y, btnWidth, btnHeight, hWnd, (HMENU)BTN_EXIT, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            
            return 0;
        }
        
        case WM_COMMAND: {
            int btnId = LOWORD(wParam);
            switch (btnId) {
                case BTN_HIDE_JIYU:
                    g_bHideJiyu = true;
                    break;
                    
                case BTN_SHOW_JIYU:
                    g_bHideJiyu = false;
                    break;
                    
                case BTN_HIDE_SELF:
                    ShowWindow(hWnd, SW_HIDE);
                    break;
                    
                case BTN_SHOW_SELF:
                    ShowWindow(hWnd, SW_SHOW);
                    break;
                    
                case BTN_KILL_JIYU:
                    system("taskkill /f /im StudentMain.exe /t >nul 2>&1");
                    MessageBox(hWnd, _T("极域学生端已强制关闭"), _T("操作完成"), MB_OK | MB_ICONINFORMATION);
                    break;
                    
                case BTN_START_JIYU:
                    system("start \"\" \"C:\\Program Files (x86)\\Mythware\\极域课堂管理系统软件V6.0 2016 豪华版\\studentmain.exe\"");
                    MessageBox(hWnd, _T("已尝试启动极域学生端"), _T("操作完成"), MB_OK | MB_ICONINFORMATION);
                    break;
                    
                case BTN_TASKMGR:
                    system("taskmgr");
                    break;
                    
                case BTN_KILL_JIZHI:
                    SetWindowText(hWnd, _T("正在杀集智 - 信息课工具箱"));
                    KILLjizhi();
                    SetWindowText(hWnd, g_szAppTitle);
                    break;
                    
                case BTN_ABOUT:
                    MessageBox(hWnd, g_szDisclaimer, _T("使用协议与免责声明"), MB_OK | MB_ICONINFORMATION);
                    break;
                    
                case BTN_EXIT:
                    PostQuitMessage(0);
                    break;
            }
            return 0;
        }
        
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
            
        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
    }
}

// 注册窗口类
ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEX wcex = {0};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = _T("InfoClassToolbox");
    return RegisterClassEx(&wcex);
}

// 创建主窗口
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
    g_hMainWnd = CreateWindow(
        _T("InfoClassToolbox"),
        g_szAppTitle,
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // 固定大小，不可最大化
        CW_USEDEFAULT, CW_USEDEFAULT, 420, 350,
        NULL, NULL, hInstance, NULL);
    
    if (!g_hMainWnd) return FALSE;
    
    ShowWindow(g_hMainWnd, nCmdShow);
    UpdateWindow(g_hMainWnd);
    
    return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    system("title ITSH控制台"); 
    printf("信息课摸鱼小助手");
    
    int result = MessageBox(NULL, g_szDisclaimer, _T("重要声明"), MB_OKCANCEL | MB_ICONWARNING);
    if (result != IDOK) {
        return 0;
    }
    
    // 注册窗口类并创建窗口
    MyRegisterClass(hInstance);
    if (!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }
    
    // 消息循环 - 同时处理窗口消息和快捷键
    MSG msg;
    while (TRUE) {
        // 检查是否有窗口消息
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        
        // 处理原有的快捷键逻辑
        HWND jy = FindWindow(NULL, _T("屏幕广播"));
        if (p(VK_MENU)) { // Alt键按下
            if (p(VK_UP)) g_bHideJiyu = false;
            if (p(VK_DOWN)) g_bHideJiyu = true;
            if (p(VK_NEXT)) ShowWindow(g_hMainWnd, SW_HIDE); // Alt+PgDn隐藏
            if (p(VK_PRIOR)) ShowWindow(g_hMainWnd, SW_SHOW); // Alt+PgUp显示
            if (p(VK_F2)) {
                system("taskkill /f /im StudentMain.exe /t >nul 2>&1");
                MessageBox(g_hMainWnd, _T("极域学生端已强制关闭"), _T("操作完成"), MB_OK | MB_ICONINFORMATION);
            }
            if (p(VK_F3)) {
                system("start \"\" \"C:\\Program Files (x86)\\Mythware\\极域课堂管理系统软件V6.0 2016 豪华版\\studentmain.exe\"");
                MessageBox(g_hMainWnd, _T("已尝试启动极域学生端"), _T("操作完成"), MB_OK | MB_ICONINFORMATION);
            }
            if (p(VK_F7)) system("taskmgr");
            if (p(VK_F8)) {
                SetWindowText(g_hMainWnd, _T("正在杀集智 - 信息课工具箱"));
                KILLjizhi();
                SetWindowText(g_hMainWnd, g_szAppTitle);
            }
            if (p(VK_F9)) {
                MessageBox(g_hMainWnd, g_szDisclaimer, _T("使用协议与免责声明"), MB_OK | MB_ICONINFORMATION);
            }
            if (p(VK_DELETE)) {
                PostQuitMessage(0);
            }
            
            // 防止按键重复触发
            Sleep(100);
        }
        
        // 自动隐藏/显示极域窗口
        if (jy != NULL) {
            if (g_bHideJiyu) {
                ShowWindow(jy, SW_HIDE);
            } else {
                ShowWindow(jy, SW_SHOW);
            }
        }
        
        // 降低CPU占用
        Sleep(10);
    }
    
    return (int)msg.wParam;
}
