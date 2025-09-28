#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "sprite.h"
#include "tutorial.h"
#include "decorator.h"
#include "customisation.h"

using namespace std;

/************************************************************\
| Наичудеснейший класс самой чудно́й менюшки. :D              |
| Предоставляет игроку широоокий выбор возможностей:         |
| 1) Начать играть                                           |
| 2) Глянуть инструктаж для дальшейшей игры                  |
| 3) Персонализировать всё, что только душеньке угодно       |
\************************************************************/

class Menu {
  private:
    short player_choice;
    Custom customisation;
    vector<string> description;

    // Эта функция печатает все надписи:
    void print_titles() {
      // Здесь будут храниться цвета соответствующих надписей:
      short color[3] = { Decorator::black, Decorator::black, Decorator::black };
      // Здесь меняем цвет нужной надписи:
      color[player_choice - 1] = Decorator::yellow;
      // Печатаем надписи:
      for (int y = 14, i = 0; i < 3; y += 2, i++) {
        Drawer::print(23, y, color[i]);
        Drawer::print(25, y, Decorator::white, description[i], color[i]);
      }
      // Возвращаем курсор на место:
      Decorator::go_home();
    }

  public:
    Menu() { 
      player_choice = 1; 
      description.push_back("Play");
      description.push_back("Tutorial");
      description.push_back("Customisation");
    }

    char get_dino() { return customisation.get_dino_choice(); }
    char get_octopus() { return customisation.get_octopus_choice(); }
    char get_gift() { return customisation.get_gift_choice(); }

    void start() {
      // Очищаем терминал:
      Decorator::clear_screen();
      // Рисуем менюшку:
      Sprite menu("sprites/menu");
      print_titles();

      char key;
      // Ждём команд от пользователя:
      while (cin.get(key)) {
        // Перемещаемся вверх по надписям:
        if (tolower(key) == 'w' || key == -122 || key == -90) { 
          player_choice--; 
          if (player_choice < 1) player_choice = 1;
          print_titles(); 
        }
        // Перемещаемся вниз по надписям:
        else if (tolower(key) == 's' || key == -85 || key == -117) { 
          player_choice++; 
          if (player_choice > 3) player_choice = 3;
          print_titles(); 
        }
        // Выбор надписи:
        else if (key == '\n') {
          if (player_choice == 1) break;
          else if (player_choice == 2) tutorial_start();
          else if (player_choice == 3) customisation.start();
        }
      }
    }
};