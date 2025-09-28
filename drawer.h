#pragma once

#include <string>
#include <iostream>

#include "decorator.h"

using namespace std;

/*******************************************************\
| Класс занимающийся рисованием в терминале.            |
| Умеет закрашивать цветом квадратики по координатам.   |
\*******************************************************/

class Drawer {
  public: 
    static void print(int x, int y, int background = Decorator::white, string text = " ", int letters = Decorator::black) {
      // Перемещаем курсор в нужную точку:
      Decorator::go_to_coordinates(x, y);
      // Выставляем черный цвет текста и нужный цвет фона:
      if (background != 13) Decorator::set_color(letters, background);
      // Печатаем пробел (получается квадратик цвета фона):
      cout << text;
      // Сбрасываем настройки:
      Decorator::reset();
    }
};