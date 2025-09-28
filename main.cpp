#include <ctime>
#include <cmath>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <iostream>

#include "menu.h"
#include "field.h"
#include "ending.h"
#include "directed.h"

using namespace std;

bool is_AFK = true;

bool playing = true;

string dino_choice = "1";
string octopus_choice = "1";
string gift_choice = "1";

// Задержка таймера:
int timer_Delay = 300; 

// Жертва тёмного леса:
Directed player("sprites/dino/" + dino_choice, 4, 1, 2);
// Подарочек:
Sprite gift("sprites/gift/" + gift_choice + "/left/1", 25, 10);
// Снеговик:
 Animated snowman("sprites/snowman", 2, 50, 15);
// Гриб:
Sprite mushroom("sprites/mushroom", 15, 15);

Directed* oct_ref;
Animated* snowman_ref;

int get_random_int(int max, int min = 1) { return min + random() % max; }

// Постоянная отрисовка бедолаги зелёного:
void cursor_reseter() {
  this_thread::sleep_for(chrono::milliseconds(200));
  while (true)
    if (is_AFK) {
      this_thread::sleep_for(chrono::milliseconds(10));
      player.draw_frame(player.direction);
    }
}

// Эта дурашка выводит вреднющий счёт:
void print_score(int score) {
  Decorator::go_to_coordinates(50, 1);
  Decorator::set_color(Decorator::white, Decorator::red);
  printf("Score: %3d", score);
}

// А эта перемещает подарок:
void relocate_gift() {
  int x = Field::get_width() - 10;
  int y = Field::get_height() - 10;
  int r = 20;

  gift.clear();
  
  //спавн подарка в радиусе r от осьминоГА 
  do {
  gift.relocate(get_random_int(x), get_random_int(y));
  } while (gift.is_in_radius(*oct_ref, r));

  gift.draw();
}

//увеличивает задержку основного таймера в multiplier раз
void increase_timer_delay(double multiplier) {
  if (timer_Delay < 800) timer_Delay *= multiplier;
  else timer_Delay = 800;
}

//уменьшает задержку таймера в divider раз
void decrease_timer_delay(double divider) {
  if (timer_Delay > 300 / 3) timer_Delay /= divider;
  else timer_Delay = 150;   
}

void relocate_shroom(){
  int x = Field::get_width() - 10;
  int y = Field::get_height() - 10;
  int r = 20;
  mushroom.clear();
  
  //спавн подарка в радиусе r от игрока 
  do {
  mushroom.relocate(get_random_int(x), get_random_int(y));
  } while (!mushroom.is_in_radius(*oct_ref, r));

  mushroom.draw();
}

void Timer(int *score) {
  // Очищаем терминал:
  Decorator::clear_screen();
  // Милая восьмилапая жадина:
  Directed octopus("sprites/octopus/" + octopus_choice, 2, 50, 3);

  do {
     mushroom.relocate(get_random_int(Field::get_width()-10), Field::get_height()-10);   
  } while (mushroom.has_collision_with(player));
  
  mushroom.draw();

  oct_ref = &octopus;
  snowman_ref = &snowman;

  Field::draw_border();
  gift.draw();

  // Рождественские заросли:
  vector<Animated> tree;
  for (int f = 0; f < 5; f++) {
    Animated tmp_tree("sprites/tree", 4, get_random_int(50, 2), get_random_int(15, 2));

    bool in_octopus = tmp_tree.has_collision_with(octopus);
    bool in_snowman = tmp_tree.has_collision_with(snowman);
    bool in_gift = tmp_tree.has_collision_with(gift);
    bool in_mushroom = tmp_tree.has_collision_with(mushroom);

    while (in_octopus || in_snowman || in_gift || in_mushroom) {
      tmp_tree.relocate(get_random_int(Field::get_width()-10, 2), get_random_int(Field::get_height()-10, 2));

      in_gift = tmp_tree.has_collision_with(gift);
      in_octopus = tmp_tree.has_collision_with(octopus);
      in_snowman = tmp_tree.has_collision_with(snowman);
      in_mushroom = tmp_tree.has_collision_with(mushroom);
    }
      tree.push_back(tmp_tree);
  }
  
  this_thread::sleep_for(chrono::milliseconds(200));
  thread reseter(cursor_reseter);
  reseter.detach();
  int prev_action = 0;

  while (playing) {
    this_thread::sleep_for(chrono::milliseconds(timer_Delay));
    for (Animated &tr : tree) tr.draw_next();
    
    snowman.draw_next();
    
    // Охота за подарком:
    if (octopus.get_x() < gift.get_x()) octopus.go_right();
    else if (octopus.get_x() > gift.get_x()) octopus.go_left();
    if (octopus.get_y() < gift.get_y()) octopus.go_down();
    else if (octopus.get_y() > gift.get_y()) octopus.go_up();
    octopus.draw_next();

    oct_ref = &octopus;

    // Если был собран подарок:
    if (octopus.has_collision_with(gift)) {
    // Перемещаем подарок:
    relocate_gift();

    // Печатаем на экран новый счёт: 
    *score-=1; 
    print_score(*score);
    }

    if (octopus.has_collision_with(player)) {
        *score -= 2;
        print_score(*score);
        
        int new_x, new_y;

        /****************\
        |1 - влево/вверх |
        |2 - вправо/вниз |
        \****************/

        #pragma region Перемещение осьминожки при съедании игрока

        int random_left_right = get_random_int(2);

        if (random_left_right == 1) { // смещение влево
          int rnd = get_random_int(20, 10);

          if (player.get_x() - rnd <=1) new_x = 2;
          else  new_x = player.get_x() - rnd;
        }
        else { //смещение вправо
          int rnd = get_random_int(20, 10);

          if (player.get_x() + rnd >= Field::get_width()) new_x = Field::get_width() - 10;
          else  new_x = player.get_x() + rnd;
        }
        int random_up_down = get_random_int(2);

        if (random_up_down == 1) { // смещение вверх
          int rnd = get_random_int(20, 10);

          if (player.get_y() - rnd <= 1) new_y = 2;
          else new_y = player.get_y() - rnd;
        }
        else { //смещение вниз
          int rnd = get_random_int(20, 10);

          if (player.get_y() + rnd >= Field::get_height()) new_y = Field::get_height() - 10;
          else new_y = player.get_y() + rnd;
        }
        #pragma endregion
        
        octopus.relocate(new_x, new_y);
    }
    if (octopus.has_collision_with(mushroom)) {
      decrease_timer_delay(1.2);
      relocate_shroom();
    }
  }  
}

int main() {
  srand(time(0)); 
  // Счётчик собранных подарочков:
  int score = 0; 
  // Ввод W, A, S, D:
  char key = 0; 

  // Очищаем терминал:
  Decorator::clear_screen();
  // Отключаем видимость вводимых символов:
  Decorator::set_echo(false);
  // Позволяем читать символы без нажатия Enter:
  Decorator::set_need_enter(false);
  
  // Запуск игрового меню:
  Menu menu;
  menu.start();
  dino_choice = menu.get_dino();
  if (dino_choice != "1") {
    Directed tmp_dino("sprites/dino/" + dino_choice, 4, 1, 2);
    player = tmp_dino;
  }
  gift_choice = menu.get_gift();
  if (gift_choice != "1") {
    Sprite tmp_gift("sprites/gift/" + gift_choice + "/left/1", 25, 10);
    gift = tmp_gift;
  }
  octopus_choice = menu.get_octopus();
  
  // Запускаем второй поток:
  this_thread::sleep_for(chrono::milliseconds(100));
  thread timer(Timer, &score);
  timer.detach();
  
  while (cin >> key) {

    is_AFK = false;
    // Перемещаемся:
    if (tolower(key) == 'w' || key == -122 || key == -90) { player.go_up(); }
    if (tolower(key) == 's' || key == -85 || key == -117) { player.go_down(); }
    if (tolower(key) == 'a' || key == -92 || key == -124) { player.go_left(); player.set_direction("left"); }
    if (tolower(key) == 'd' || key == -78 || key == -110) { player.go_right(); player.set_direction("right"); }
    player.draw_next();

    // Если был собран подарок:
    if (player.has_collision_with(gift)) {
      // Перемещаем подарок:
      relocate_gift();
      // Печатаем на экран новый счёт:
      score+=1; 
      print_score(score);
    }
    // Если миссия выполнена:
    if (player.has_collision_with(snowman) && score >= 15) {
      Ending fin;
      playing = false;
      for (int i = 0; i < 100; i++)
        for (int j = 0; j < 300; j++) 
          Decorator::clear_screen();
      fin.good_end();
      Decorator::set_need_enter(true);
      Decorator::set_echo(true);
      Decorator::clear_screen();
      Decorator::go_home();
      return 0;
    }
    // Если миссия провалена:
    if (score <= -15) {
      Ending fin;
      playing = false;
      for (int i = 0; i < 100; i++)
        for (int j = 0; j < 300; j++) 
          Decorator::clear_screen();
      fin.bad_end();
      Decorator::set_need_enter(true);
      Decorator::set_echo(true);
      Decorator::clear_screen();
      Decorator::go_home();
      return 0;
    }
    // Если собран гриб:
    if (player.has_collision_with(mushroom)) {
      relocate_shroom();
      increase_timer_delay(1.2);     
    }
    is_AFK = true;
  }
}