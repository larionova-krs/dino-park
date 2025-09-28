#pragma once

#include "field.h"
#include "picture.h"

/*******************************************************************\
| Класс игрового объекта.                                           |
| Отличается от обычной картинки тем, что знает свои координаты и   |
| умеет определять коллизии (пересечения) с другими спрайтами.      |
\*******************************************************************/

class Sprite {
  private:
    // Картинка спрайта:
    Picture pic;

  protected:
    int x, y;

  public:
    Sprite() { x = 0; y = 0; }
    // При создании объекта с параметрами вызовется конструктор Picture, принимающий путь до картинки
    Sprite(std::string sprite_src, int x = 0, int y = 0): pic(sprite_src), x(x), y(y) { draw(); }

    // Метод, отрисовывающий картинку на её месте:
    void draw() { pic.draw(x, y); }

    // Метод, стирающий картинку с её места:
    void clear() { pic.clear(x, y); }

    // Метод перемещающий картинку в новые координаты:
    void relocate(int x, int y) { this -> x = x; this -> y = y; }

    // Проверка на коллизию (пересечение с другим спрайтом):
    bool has_collision_with(Sprite other) {
      bool col_collision = false, row_collision = false;
      
      if (x + get_width() >= other.x && x <= other.x + other.get_width()) col_collision = true;
      if (y + get_height() >= other.y && y <= other.y + other.get_height())  row_collision = true;
      return col_collision && row_collision;
    }

    //Находится ли спрайт в радиусе r от другого спрайта    
    bool is_in_radius(Sprite other, int r){

      return abs(other.get_x()-x)<=r && abs(other.get_y()-y)<=r;
    }

    virtual int get_width() { return pic.get_width(); }
    virtual int get_height() { return pic.get_height(); }
    int get_x() { return x; }

    int get_y() { return y; }

    // Перемещение W, A, S, D:
    void go_left() { if (x > 1) x--; }
    void go_up() { if (y > 1) y--; }
    void go_right() { if (x<Field::get_width()) x++; }
    void go_down() {if (y<Field::get_height()) y++; }
};