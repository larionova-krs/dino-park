#include <string>
#include <iostream>

#include "drawer.h"
#include "sprite.h"
#include "decorator.h"

using namespace std;

/******************************************************************\
| Замечательнейший класс - ネコ кастомизации.                      |
\******************************************************************/

class Custom {
  private:
    // Для кастомизируемых персонажей:
    char sprite_choice[3];
    Sprite previous_sprite;
    short y_coor[3];
    vector<string> way;
    // Для самой странички:
    short player_choice, previous_choice;
    vector<string> description;

    // Печать всех надписей:
    void print_titles() {
      short color[4] = { Decorator::black, Decorator::black, Decorator::black, Decorator::black };
      // Здесь меняем цвет нужной надписи:
      if (player_choice == 4) color[3] = Decorator::blue;
      else color[player_choice - 1] = Decorator::yellow;
      // Печатаем надписи:
      for (int y = 3, i = 0; i < 3; y += 2, i++) {
        Drawer::print(4, y, color[i]);
        Drawer::print(6, y, Decorator::white, description[i], color[i]);
      }
      print_exit(color[3]);
      // Возвращаем курсор на место:
      Decorator::go_home();
    }
    // Печать жирного такого "EXIT":
    void print_exit(short color) {
    	// "E":
      for (int i = 3; i < 8; i++) {
        if (i % 2 == 1) Drawer::print(23, i, color, "   ");
        else Drawer::print(23, i, color);
      }
      // "X":
      for (int i = 3; i < 8; i++) {
        if (i == 5) i++;
        Drawer::print(27, i, color);
      }
      Drawer::print(28, 5, color);
      for (int i = 3; i < 8; i++) {
        if (i == 5) i++;
        Drawer::print(29, i, color);
      }
      // "I":
      Drawer::print(31, 3, color, "   ");
      for (int i = 4; i < 7; i++) Drawer::print(32, i, color);
      Drawer::print(31, 7, color, "   ");
      // "T":
      Drawer::print(35, 3, color, "   ");
      for (int i = 4; i < 8; i++) Drawer::print(36, i, color);
    }
    // Печать картинки кастомизируемого персонажа:
    void print_picture() {
      if (player_choice != 4) {
        previous_sprite.clear();
        Sprite character(way[player_choice - 1] + sprite_choice[player_choice - 1] + "/left/1", 18, y_coor[player_choice - 1]);
        previous_sprite = character;
        Decorator::go_home();
      }
    }

  public:
    Custom() {
      player_choice = 1;
      previous_choice = player_choice;

      for (int i = 0; i < 3; i++) sprite_choice[i] = '1';
      y_coor[0] = 13; y_coor[1] = 11; y_coor[2] = 15;

      description.push_back("Dino (you)"); way.push_back("sprites/dino/");
      description.push_back("Octopus"); way.push_back("sprites/octopus/");
      description.push_back("Gift"); way.push_back("sprites/gift/");

      Sprite dino("sprites/dino/1/left/1", 18, 11);
      previous_sprite = dino;
    }

    char get_dino_choice() { return sprite_choice[0]; }
    char get_octopus_choice() { return sprite_choice[1]; }
    char get_gift_choice() { return sprite_choice[2]; }

    void start() {
      // Очищаем терминал:
      Decorator::clear_screen();
      // Рисуем окно кастомизации:
      Sprite customize("sprites/customize");
      print_picture(); print_titles();

      char key;
      
      // Ждём команд от пользователя:
      while (cin.get(key)) {
        if (player_choice != 4) {
          // Перемещаемся вверх по надписям:
          if (tolower(key) == 'w' || key == -122 || key == -90) { 
            player_choice--; 
            if (player_choice < 1) player_choice = 1;
            print_picture(); print_titles();
          }
          // Перемещаемся вниз по надписям:
          else if (tolower(key) == 's' || key == -85 || key == -117) {
            player_choice++; 
            if (player_choice > 3) player_choice = 3;
            print_picture(); print_titles(); 
          }
          // Перемещаемся на предыдущую картинку:
          else if (tolower(key) == 'd' || key == -78 || key == -110) {
            sprite_choice[player_choice - 1]++;
            if (sprite_choice[player_choice - 1] > '3') sprite_choice[player_choice - 1] = '3';
            print_picture();
          }
          // Перемещаемся на следующую картинку:
          else if (tolower(key) == 'a' || key == -92 || key == -124) {
            sprite_choice[player_choice - 1]--;
            if (sprite_choice[player_choice - 1] < '1') sprite_choice [player_choice - 1] = '1';
            print_picture();
          }
          // Перемещаемся на "EXIT":
          else if (tolower(key) == 'e') {
            previous_choice = player_choice;
            player_choice = 4;
            print_titles(); 
          }
        }
        // Возвращаемся с "EXIT":
        else if (tolower(key) == 'q') {
          player_choice = previous_choice;
          print_titles();
        }

        // Подтверждение выбора:
        if (key == '\n') {
          // Возвращение и отрисовка гланого меню:
          if (player_choice == 4) {
            player_choice = previous_choice;
            Decorator::clear_screen();
            Sprite menu("sprites/menu");
            Drawer::print(23, 14, Decorator::black);
            Drawer::print(23, 16, Decorator::black);
            Drawer::print(23, 18, Decorator::yellow);
            Drawer::print(25, 14, Decorator::white, "Play");
            Drawer::print(25, 16, Decorator::white, "Tutorial");
            Drawer::print(25, 18, Decorator::white, "Customisation", Decorator::yellow);
            Decorator::go_home();
            break;
          }
        }
      }
    }
};