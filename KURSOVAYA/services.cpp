#include <iostream>
#include <windows.h>

using namespace std;


LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_LBUTTONDOWN) {
        MSLLHOOKSTRUCT* mouse = (MSLLHOOKSTRUCT*)lParam;
        std::cout << "����� ������ ������: (" << mouse->pt.x << ", " << mouse->pt.y << ")\n";
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void TrackMouseClicks() {
    HHOOK mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookProc, GetModuleHandle(NULL), 0);
    if (!mouseHook) {
        std::cerr << "������ ��������� ����\n";
        return;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(mouseHook);
}

void move_cursor(short x, short y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clear(int x, int y, int n = 1) {
    string empty(n, ' ');
    move_cursor(x, y);
    cout << empty;
}

void set_color(int text_color, int bg_color = 0) {
    //  0 - ������
    //  1 - �����
    //  2 - �������
    //  3 - �������
    //  4 - �������
    //  5 - ���������
    //  6 - ������
    //  7 - �����(�� ���������)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text_color | (bg_color << 4));
}


void end_game() {

}


void simulateF11() {
    INPUT input[2] = {};

    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = VK_F11;
    input[0].ki.dwFlags = 0;

    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = VK_F11;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(2, input, sizeof(INPUT));
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void disableMouseSelection() {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prev_mode;
    GetConsoleMode(hInput, &prev_mode);
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS |
        (prev_mode & ~ENABLE_QUICK_EDIT_MODE));
}