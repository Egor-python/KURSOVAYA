﻿#include <iostream>
#include <windows.h>
#include "services.h"
#include "decoration.h"
#include "player.h"
#include "enemies.h"

using namespace std;


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    hideCursor();
    Sleep(70);
    simulateF11();

    int player_x = 78;
    int player_y = 25;
    char player_type = 'V';

    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }

        print_castle();
        set_color(2);
        player_move(player_x, player_y, player_type);
        move_cursor(0, 0);
        set_color(7);

        cout << R"(
       .oo'    |    oo.'
    ,.  (-'    |    -')  ,.
   '^\-' )     |     ( -'/^
      c-L'-     |     -_-)   
)";

        Sleep(80);
        move_cursor(0, 0);
        ShowCursor(TRUE);
    }

    //system("pause");
    return 0;
}