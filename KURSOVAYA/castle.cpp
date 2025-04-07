﻿#include <iostream>
#include <Windows.h>
#include "services.h"
#include "player.h"

using namespace std;

void print_castle(const Player& player) {
    const string castle[] = {
    "                        /\\         /\\  ",
    "                      (^<>^)     (^<>^) ",
    "             __       /^/\\^\\     /^/\\^\\      __",
    "          __:  |     / /  \\ \\   / /  \\ \\    |  :__",
    "         |  :__|     |^^^^^^|   |^^^^^^|    |__:  |",
    "         |__:  |     \\/\\/\\/\\/   \\/\\/\\/\\/    |  :__|",
    "              / \\    |  __  |   |  __  |   / \\  ",
    "             /   \\   | |__| |   | |__| |  /   \\ ",
    "            /_____\\  |      |   |      | /_____\\" ,
    "            |     |==  ==  ==  ==  ==  ==|     |",
    "            |  _  | |__||__||__||__||__| |  _  |",
    "            | | | |                      | | | |  ~",
    " ~      ~~~~| |=| |   __            __   | |=| |~~~~~   ~              ",
    "     ~~~~~~~|     |  |  |    __    |  |  |     |~~~~~~~~    ~          ",
    "~   ~~~~~   |     |  |==|   |::|   |==|  |     |   ~~~~~~~        ~    ",
    "   ~~~~~    |     |         |::|         |     |~    ~~~~~~            ",
    "   ~~~~     |_____|_________|::|_________|_____|~~    ~~~~~~   ~       ",
    "   ~~~~     ~~~~~~~~~~~~~~~~++++~~~~~~~~~~~~~~~~~      ~~~~~           ",
    "    ~~~~      ~~~~~~~~~~~~~~++++~~~~~~~~~~~~~~~       ~~~~~~           ",
    "      ~~~~       ~~~~~~~~~~~++++~~~~~~~~~~~         ~~~~~~~      ~",
    "~        ~~~~~             ++++++                 ~~~~~",
    "            ~~~ ~~  ~  ~ ~ ++++ +  ~~   ~~   ~~~ ~~~~",
    "       ~        ~  ~    ~  ++++++~ ~  ~ ~  ~~               ~",
    "            ~      ~ ~   ~ + ++++~     ~~    ~       ~",
    "               ~    ~  ~   ++++++ ~~   ~ ~",
    "   ~      ~        ~~ ~    ++++++  ~~   ~    ~",
    "                 ~      ~ ~+++ ++   ~     ~       ~",
    "          ~        ~     ~ ++++++~    ~  ~ ~",

    };

    const int player_x = player.player_x;
    const int player_y = player.player_y;

    int castle_size = 0;
    for (string s : castle) {
        castle_size++;
    }

    // Размеры консоли: x = 156, y = 45
    // Размеры замка: 24 строки, 61 символа самая длинная строка
    const int free_left_space = 45;
    for (int i{ 0 }; i < 45; i++) {
        const int empty_spaces = 8;
        if (i > empty_spaces && i < empty_spaces + castle_size + 1) {
            clear(0, i, free_left_space + 1);
            if (i - empty_spaces > 11) {
                int x_index = free_left_space;
                bool is_water = true;
                bool is_first_water = true;
                for (char symbol : castle[i - empty_spaces - 1]) {
                    x_index++;
                    if (!(i == player_y && x_index == player_x)) {
                        if (symbol == '~' && is_water) {
                            set_text_color("cyan");
                            is_first_water = false;
                        }
                        else if (symbol == '~') {
                            set_text_color("green");
                        }
                        if (symbol == '+') {
                            set_text_color("yellow");
                        }
                        if (symbol == ':') {
                            set_text_color("red");
                        }
                        if (!is_first_water && i - empty_spaces < 21 && i - empty_spaces > 15 && x_index - free_left_space < 61 &&
                            (symbol == ' ' || symbol == '|') && castle[i - empty_spaces - 1][x_index - free_left_space] == '~') {
                            is_water = !is_water;
                        }
                        cout << symbol;
                        set_color();
                    }
                    else {
                        move_cursor(x_index + 1, i);
                    }
                }
                cout << endl;
                set_color();
            }
            else {
                cout << castle[i - empty_spaces - 1] << endl;
            }
        }
        else {
            clear(0, i, 156);
            cout << endl;
        }
    }
}
