#pragma once

#include <iostream>

#include "drawer.h"
#include "decorator.h"

/*********************************************\
| Класс игрового поля.                        |
\*********************************************/

class Field {
public:
    static int height, width;

    static int get_height() { return height; }
    static int get_width() { return width; }

    // Изменение размера поля:
    static void set_size(int _height, int _width) {
      height = _height;
      width = _width;
    }
    
    // Рисование чудно́й снежной рамочки:
    static void draw_border() {
      // Нижняя граница:
      for (int i = 0; i <= width + 6; i++) { Drawer::print(i, height + 6); }
      // Правая граница:
      for (int i = 0; i <= height + 6; i++) { Drawer::print(width + 7, i); }
    }
};

int Field::height = 25;
int Field::width = 60;