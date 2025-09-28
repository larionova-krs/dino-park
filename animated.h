#pragma once

#include "sprite.h"

using namespace std;

/*******************************************************************\
| Класс анимированного спрайта.                                     |
|                                                                   |
| Анимированный спрайт имеет несколько кадров (отдельные картинки)  |
| и умеет отрисовывать либо определенную картинку по ее             |
| порядковому номеру, либо следующую по порядку. За счет            |
| этого и достигается эффект анимации.                              |
\*******************************************************************/

class Animated: public Sprite {
  private:
    // Вектор для хранения кадров:
    vector<Picture> frames;
    // Для стирания предыдущего кадра:
    Picture previous_frame;
    int prev_x, prev_y;
    bool tree, choice;

  protected:
    // Текущий кадр:
    int current_frame = 1;

  public:
    Animated() { }
    // sprite_src - путь к папке с пронумерованными файлами изображений
    Animated(string sprite_src, int frame_count, int x = 0, int y = 0) {

      if (sprite_src == "sprites/tree") tree = true;

      this -> x = x; this -> y = y;

      // Добавляем в вектор все кадры:
      frames.resize(frame_count);
      for (int i = 0; i < frame_count; i++) {
        char num = i + 1 + '0';
        frames[i] = Picture(sprite_src + "/" + num);
      }

      // Сразу при создании объекта отрисовываем его:
      draw_frame(current_frame);
    }
    void clear_previous() { previous_frame.clear(prev_x, prev_y); }

    // Рисовка нынешнего кадра:
    void draw_frame(int n) {
      frames[n - 1].draw(x, y);
      previous_frame = frames[n - 1];
      prev_x = x; prev_y = y;
      current_frame = n;
    }
    // Рисовка следующего кадра:
    void draw_next() {
      current_frame++;
      if (current_frame > get_frame_count()) current_frame = 1;
      clear_previous();
      draw_frame(current_frame);
    }
    // Рисовка предыдущего кадра:
    void draw_previous() {
      current_frame--;
      if (current_frame < 1) current_frame = get_frame_count();
      clear_previous();
      draw_frame(current_frame);
    }

    int get_current_frame() { return current_frame; }
    int get_frame_count() { return frames.size(); }
    int get_width() { return frames[current_frame - 1].get_width(); }
    int get_height() { return frames[current_frame - 1].get_height(); }
};