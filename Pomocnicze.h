//
// Created by Wojtek-Laptop on 11.03.2018.
//

#ifndef PROJEKTCPP_POMOCNICZE_H
#define PROJEKTCPP_POMOCNICZE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Obiekty.h"

using namespace sf; using namespace std;

int losuj(int a,int b);
float losujF(float a,float b);

template <class t>bool czywPolu(t testowany, Vector2i pozycja)
{
    FloatRect testowanyR=testowany.getGlobalBounds();

    auto prawa=testowanyR.left+testowanyR.width; auto lewa=testowanyR.left;
    auto gora=testowanyR.top; auto dol=testowanyR.top+testowanyR.height;

    if(pozycja.x>=lewa&& pozycja.x<=prawa&& pozycja.y>=gora && pozycja.y<=dol)
    { return true; }

    else return false;
};

void generujTekst(Text &txt,string nazwa,RenderWindow &okno,string font,float wlk,Color c,char Typ,float pozycja);

template <class t> bool czyCzescWspolna(t a1,t a2,t b1,t b2)
{
    if((a1<=b1&&a1<=b2)&&(b1>=a1&&b1<=a2)&&(a2>=b1&&a2<=b2)&&(b2>=a1&&b2>=a2))
    { return true; }

    else if((b1<=a1&&b1<=a2)&&(a1>=b1&&a1<=b2)&&(b2>=a1&&b2<=a2)&&(a2>=b1&&a2>=b2))
    { return true; }

    else if((a1<=b1&&a1<=b2)&&(b1>=a1&&b1<=a2)&&(b2>=a1&&b2<=a2)&&(a2>=b1&&a2>=b2))
    { return true; }

    else if((b1<=a1&&b1<=a2)&&(a1>=b1&&a1<=b2)&&(a2>=b1&&a2<=b2)&&(b2>=a1&&b2>=a2))
    { return true; }

    else return false;
}

template <class t,class m>
bool czyZderzenie(t &obj1,m &obj2)
{
    Sprite sprite1=obj1.getSprite(),sprite2=obj2.getSprite();
    if(czyCzescWspolna(getEdges(sprite1).left,getEdges(sprite1).right,getEdges(sprite2).left,getEdges(sprite2).right))
    {
        if(czyCzescWspolna(getEdges(sprite1).up,getEdges(sprite1).down,getEdges(sprite2).up,getEdges(sprite2).down)) {return true;}
        else return false;
    }
    else if(czyCzescWspolna(getEdges(sprite1).up,getEdges(sprite1).down,getEdges(sprite2).up,getEdges(sprite2).down))
    {
        if(czyCzescWspolna(getEdges(sprite1).left,getEdges(sprite1).right,getEdges(sprite2).left,getEdges(sprite2).right)){return true;}
        else return false;
    }
    else {return false;}
};

#endif //PROJEKTCPP_POMOCNICZE_H
