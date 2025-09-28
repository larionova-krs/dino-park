#include <string>
#include <vector>

#include "drawer.h"
#include "animated.h"

/************************************************************\
| Класс туториала из главной менюшки.                        |
\************************************************************/

class Tutorial {
  private:
    Animated picture;
    vector<string> discription;
    Sprite frame;

    // Эта функция печатает все надписи:
    void print_titles() {
      short disc_count;
      if (picture.get_current_frame() == 1) {
        disc_count = 0;
        // Печать букв W A S D на крестовине первого кадра:
        Drawer::print(13, 11, Decorator::red, "W", Decorator::white);
        Drawer::print(17, 13, Decorator::red, "D", Decorator::white);
        Drawer::print(13, 15, Decorator::red, "S", Decorator::white);
        Drawer::print(9, 13, Decorator::red, "A", Decorator::white);
      }
      else if (picture.get_current_frame() == 2) disc_count = 3;
      else if (picture.get_current_frame() == 3) disc_count = 6;
      else if (picture.get_current_frame() == 4) disc_count = 9;
      else if (picture.get_current_frame() == 5) disc_count = 12;

      // Печать всех надписей:
      for (int y = 6; y < 9; disc_count++, y++) {
        Drawer::print(5, y, Decorator::none, discription[disc_count]);
      }
      // Возвращаем курсор на место:
      Decorator::go_home();
    }

  public:
    Tutorial() {
      discription.push_back("                                ");
      discription.push_back("       W, A, S, D - move        ");
      discription.push_back("                                ");
      discription.push_back("    Octopus likes gifts too!    ");
      discription.push_back("   If octopus collects a gift   ");
      discription.push_back("       you lose one point       ");
      discription.push_back("            Beware!             ");
      discription.push_back("   If you run into octopus...   ");
      discription.push_back("   It will steal your 2 gifts   ");
      discription.push_back("                                ");
      discription.push_back("     When you get 15 points     ");
      discription.push_back("         come to snowman        ");
      discription.push_back("                                ");
      discription.push_back("   If your score drops to -15   ");
      discription.push_back("        the octopus wins        ");
      Decorator::clear_screen();
      Sprite tmp("sprites/tutor/frame"); 
      frame = tmp;
      Animated tmp2("sprites/tutor/pictures", 5, 5, 9);
      picture = tmp2;
    }

    void start() {
      Drawer::print(12, 3, Decorator::white, "Press Enter to exit", Decorator::yellow);
      print_titles();

      char key;
      while (cin.get(key)) {
        // Перемещаемся на предыдущую картинку:
        if (tolower(key) == 'd' || key == -78 || key == -110) {
          if (picture.get_current_frame() != picture.get_frame_count()) picture.draw_next();
          print_titles();
        }
        // Перемещаемся на следующую картинку:
        else if (tolower(key) == 'a' || key == -92 || key == -124) {
          if (picture.get_current_frame() != 1) picture.draw_previous();
          print_titles();
        }
        
        // Возвращение в меню:
        else if (key == '\n') {
          Decorator::clear_screen();
          Sprite menu("sprites/menu");
          Drawer::print(23, 14, Decorator::black);
          Drawer::print(23, 16, Decorator::yellow);
          Drawer::print(23, 18, Decorator::black);
          Drawer::print(25, 14, Decorator::white, "Play");
          Drawer::print(25, 16, Decorator::white, "Tutorial", Decorator::yellow);
          Drawer::print(25, 18, Decorator::white, "Customisation");
          Decorator::go_home();
          break;
        }
      }
    }
};

void tutorial_start() { Tutorial tutor; tutor.start(); }