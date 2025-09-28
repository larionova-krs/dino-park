#include <string>
#include <iostream>

#include "drawer.h"
#include "sprite.h"
#include "decorator.h"

using namespace std;

/******************************************************************\
|                                                                  |
\******************************************************************/

class Ending {
  private:
    void confirm_waiting() {
      char key;
      // Ждём команд от пользователя:
      while (cin.get(key)) if (key == '\n') break;
    }

  public:
    void bad_end() {
      // Рисуем заставку:
      Sprite fin("sprites/end/defeat");
      confirm_waiting();
    }
    void good_end() {
      // Очищаем терминал:
      Decorator::clear_screen();
      // Рисуем заставку:
      Sprite fin("sprites/end/victory");
      confirm_waiting();
    }
};