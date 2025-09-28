#pragma once

#include <vector>
#include <fstream>

#include "drawer.h"
#include "decorator.h" 

using namespace std;

/******************************************************\
| Класс, умеющий загружать изображение из файла .txt   |
|                                                      |
| Формат файлов:                                       |
| Пробел - пустой пиксель                              |
| R - красный пиксель                                  |
| G - зеленый пиксель                                  |
| B - голубой пиксель                                  |
| C - бирюзовый пиксель                                |
| D - черный пиксель                                   |
| Y - желтый пиксель                                   |
| W - белый пиксель                                    |
| P - фиолетовый пиксель                               |
\******************************************************/

class Picture {
  private:
    vector<string> pic;
    int height = 0, width = 0;

  public: 
    Picture() { }
    Picture(string path) {
      string tmp;
      // Открываем файл с картинкой в режиме чтения:
      ifstream fin(path + ".txt");
      
      // Считываем строки из файла по одной до конца:
      while (getline(fin, tmp)){
        // Кладем считанную строку в вектор:
        pic.push_back(tmp);
        // Устанавливаем как ширину картинки длину длиннейшей строки:
        if (width < tmp.length()) width = tmp.length();
      }
      // Устанавливаем как высоту картинки количество строк:
      height = pic.size();

      fin.close();
    }

    int get_width() { return width; }
    int get_height() { return height; }

    // Метод для отрисовки изображения на териминале:
    void draw(int x, int y) {
      // Обходим вектор строк:
      for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
          // Красим пиксели в нужный цвет:
          switch(pic[i][j]) {
            case 'R': Drawer::print(x + j, y + i, Decorator::red); break;
            case 'G': Drawer::print(x + j, y + i, Decorator::green); break;
            case 'B': Drawer::print(x + j, y + i, Decorator::blue); break;
            case 'C': Drawer::print(x + j, y + i, Decorator::cyan); break;
            case 'D': Drawer::print(x + j, y + i, Decorator::black); break;
            case 'Y': Drawer::print(x + j, y + i, Decorator::yellow); break;
            case 'W': Drawer::print(x + j, y + i, Decorator::white); break;
            case 'P': Drawer::print(x + j, y + i, Decorator::purple); break;
          }
        }
      }
    }
    // Метод для стирания изображения с териминала:
    void clear(int x, int y) {
      // Обходим вектор строк:
      for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
          // Красим пиксели в пустой цвет:
          if (pic[i][j] != ' ') Drawer::print(x + j, y + i, Decorator::none);
        }
      }
    }
};