#ifndef PROJEKTCPP_MENU_H
#define PROJEKTCPP_MENU_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf; using namespace std;

bool gameover(RenderWindow &okno);

Vector2u menuRdz(RenderWindow &okno);
Vector2u menuMulti(RenderWindow &okno);
bool menuPauza(RenderWindow &okno);
bool gra(RenderWindow &okno);



#endif //PROJEKTCPP_MENU_H
