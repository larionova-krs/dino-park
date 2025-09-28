#pragma once

#include "animated.h"

using namespace std;

/************************************************************\
| Направленный спрайт.                                       |
|                                                            |
| Это разновиднойсть анимированного спрайта, который может   |
| контролировать направление движения и выводить кадр из     |
| коллекции именно этого направления движения.               |
\************************************************************/

class Directed : public Animated {
  private:
    // Для хранения всех кадров:
    vector<Picture> right_frames;
    vector<Picture> left_frames;
    // Для стирания предыдущего кадра:
    Picture previous_frame;
    int prev_x, prev_y;

  public:
    // Куда смотрит персонаж:
    string direction;
    
    Directed() { direction = "right"; }
    Directed(string sprite_src, int frame_count, int x = 0, int y = 0, string direction = "right") {
      this -> x = x; this -> y = y; this -> direction = direction;

      // Сохраняем в вектор все кадры движения вправо:
      right_frames.resize(frame_count);
      for (int i = 0; i < frame_count; i++) {
        char num = i + 1 + '0';
        right_frames[i] = Picture(sprite_src + "/right/" + num); }

      // Сохраняем в вектор все кадры движения влево:
      left_frames.resize(frame_count);
      for (int i = 0; i < frame_count; i++) {
        char num = i + 1 + '0';
        left_frames[i] = Picture(sprite_src + "/left/" + num); }

      // Сразу рисуем нового персонажа:
      draw_frame(direction, current_frame);
    }

    // Рисовка нынешнего кадра:
    void draw_frame(string direction, int n = 0) {
      if (n == 0) n = current_frame;
      if (direction == "right") { right_frames[n - 1].draw(x, y); previous_frame = right_frames[n - 1]; }
      else if (direction == "left") { left_frames[n - 1].draw(x, y); previous_frame = left_frames[n - 1]; }
      prev_x = x; prev_y = y;
      current_frame = n;
    }
    // Рисовка следующего кадра:
    void draw_next() {
      current_frame++;
      if (current_frame > get_frames_count()) current_frame = 1;
      previous_frame.clear(prev_x, prev_y);
      draw_frame(direction, current_frame); 
    }
    // Смена стороны, в которую персонаж смотрит:
    void set_direction(string direction) {
      if (direction == "right" || direction == "left") 
        this -> direction = direction; 
    }

    int get_frames_count() { return right_frames.size(); }
    int get_width() {
      if (direction == "right") return right_frames[current_frame - 1].get_width();
      if (direction == "left") return left_frames[current_frame - 1].get_width(); 
    }
    int get_height() {
      if (direction == "right") return right_frames[current_frame - 1].get_height();
      if (direction == "left") return left_frames[current_frame - 1].get_height(); 
    }
};