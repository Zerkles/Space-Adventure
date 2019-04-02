//
// Created by Zerkles on 01.10.2018.
//

#ifndef SPACE_ADVENTURE_AI_H
#define SPACE_ADVENTURE_AI_H7

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <synchapi.h>
#include "Obiekty.h"
#include "Pomocnicze.h"
#include "Menu.h"

void dwochgraczy(RenderWindow &okno);
void optymalny(RenderWindow &okno);
void ofensywny(RenderWindow &okno);
void defensywny(RenderWindow &okno);
void inteligent(RenderWindow &okno);

#endif //SPACE_ADVENTURE_AI_H
