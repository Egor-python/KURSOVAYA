﻿#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

void move_cursor(const int x = 0, const int y = 0) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clear_all() {
    system("cls");
}

void clear(const int x, const int y, const int n = 1, const char symbol = ' ') {
    string empty(n, symbol);
    move_cursor(x, y);
    cout << empty;
}

int get_color_code(const string& color) {
    if (color == "black") return 0;
    if (color == "blue") return 1;
    if (color == "green") return 2;
    if (color == "cyan") return 3;
    if (color == "red") return 4;
    if (color == "purple") return 5;
    if (color == "yellow") return 6;
    if (color == "white") return 7;
    return 7; // По умолчанию белый
}

void set_color(const string& text_color, const string& bg_color = "black") {
    int text_code = get_color_code(text_color);
    int bg_code = get_color_code(bg_color);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text_code | (bg_code << 4));
}

void set_color(const int text_color, const int bg_color) {
    //  0 - Черный
    //  1 - Синий
    //  2 - Зеленый
    //  3 - Голубой
    //  4 - Красный
    //  5 - Пурпурный
    //  6 - Желтый
    //  7 - Белый(по умолчанию)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text_color | (bg_color << 4));
}

void set_color(const int text_color) {
    set_color(text_color, 0);  // Вызываем основную версию с фоновым цветом 0
}

bool can_move_border(const int x, const int y) {
    if (x < 1 or y < 0) return false;   // Границы окна 
    if (x >= 156 or y >= 46) return false;
    return true;
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