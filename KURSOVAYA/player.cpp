#include <iostream>
#include <windows.h>
#include "services.h"

void piy(int player_x, int player_y, char player_type) {

}

bool can_move_player(int x, int y) {
    if (x < 1 or y < 0) return false;   // ������� ���� 
    if (x >= 156 or y >= 46) return false;
    //if ((x > 56 && x < 99) && (y >= 2 && y <= 5)) return false;  // ����
    //if ((x > 59 && x < 96) && (y >= 6 && y <= 15)) return false; // �����
    //if ((x > 68 && x < 87) && (y >= 0 && y <= 2)) return false;  // ��������
    return true;
}

void player_move(int& x, int& y, char& cursor_type) {
    clear(x, y);
    if ((GetAsyncKeyState('W') & 0x8000) && (GetAsyncKeyState('A') & 0x8000) && can_move_player(x - 2, y - 1)) { // ����� � �����
        y -= 1;
        x -= 2;
    }
    else if ((GetAsyncKeyState('W') & 0x8000) && (GetAsyncKeyState('D') & 0x8000) && can_move_player(x + 2, y - 1)) { // ����� � ������
        y -= 1;
        x += 2;
    }
    else if ((GetAsyncKeyState('S') & 0x8000) && (GetAsyncKeyState('A') & 0x8000) && can_move_player(x - 2, y + 1)) { // ���� � �����
        y += 1;
        x -= 2;
    }
    else if ((GetAsyncKeyState('S') & 0x8000) && (GetAsyncKeyState('D') & 0x8000) && can_move_player(x + 2, y + 1)) { // ���� � ������
        y += 1;
        x += 2;
    }
    else if (GetAsyncKeyState('W') & 0x8000 && can_move_player(x, y - 1)) { // ������ �����
        y -= 1;
    }
    else if (GetAsyncKeyState('S') & 0x8000 && can_move_player(x, y + 1)) { // ������ ����
        y += 1;
    }
    else if (GetAsyncKeyState('A') & 0x8000 && can_move_player(x - 2, y)) { // ������ �����
        x -= 2;
    }
    else if (GetAsyncKeyState('D') & 0x8000 && can_move_player(x + 2, y)) { // ������ ������
        x += 2;
    }

    POINT p;
    HWND hwnd = GetConsoleWindow();
    GetCursorPos(&p);
    ScreenToClient(hwnd, &p);
    double x_pos = (double)p.x / 9.7;       // ��������� ������� ���� � ���������� ������� ( +-1 )
    double y_pos = (double)p.y / 17.6;

    //std::cout << "Mouse X: " << x_pos << " Y: " << y_pos << std::endl;
    //cout << x << ' ' << y;

    // ��� ��� ���������� ����� �������� � ��������� �� ��������� ��� ����������� ��������� 
    // ��������� ������� ��������� ���������� ������������ ��������
    if ((y - y_pos) * 1.9 >= abs(x - x_pos)) {
        cursor_type = '^';
    }
    else if ((y_pos - y) * 1.5 >= abs(x - x_pos)) {
        cursor_type = 'V';
    }
    else if ((x_pos - x) >= abs(y - y_pos)) {
        cursor_type = '>';
    }
    else if ((x - x_pos) >= abs(y - y_pos)) {
        cursor_type = '<';
    }

    move_cursor(x, y);
    std::cout << cursor_type;
}