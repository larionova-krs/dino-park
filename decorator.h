#pragma once

#include <stdio.h>

/**********************************************************\
| Черная магия оформления терминала - не влезать!          |
| Затянет навечно и превратит тебя в черного программиста, |
| а твой терминал в цветной каламбур :)                    |
\**********************************************************/

class Decorator {
  public:
    // ЦВЕТА:
    static const int black = 0;
    static const int red = 1;
    static const int green = 2;
    static const int yellow = 3;
    static const int blue = 4;
    static const int purple = 5;
    static const int cyan = 6;
    static const int white = 7;
    static const int none = 13;

    // СТИЛИ:
    static const int bright = 1;
    static const int italic = 3;
    static const int underlined = 4;
    static const int reversed = 7;
    static const int invisible = 8;
    
    static void clear_screen() { reset(); printf("\033[2J"); }
    static void go_to_coordinates(int x, int y) { printf("\033[%d;%dH", y, x); }
    static void set_echo(bool status) { system(status ? "stty echo" : "stty -echo"); }
    static void set_need_enter(bool status) { system(status ? "stty -cbreak" : "stty cbreak"); }
    static void set_color(int font, int bg) { printf("\033[3%d;4%dm", font, bg); }
    static void set_style(int style) { printf("\033[0%dm", style); }
    static void reset() { printf("\033[00m"); }
    static void go_home() { printf("\033[H"); }
};