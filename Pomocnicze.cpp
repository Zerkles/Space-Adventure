#include "Pomocnicze.h"
#include "Obiekty.h"
#include <random>

using namespace sf; using namespace std;

void generujTekst(Text &txt,string nazwa,RenderWindow &okno,string font,float wlk,Color c,char Typ,float pozycja)
{
    Font fnt; FloatRect txtR; fnt.loadFromFile("Zawartosc\\Czcionki\\"+font);

    int wielkosc=okno.getSize().x*wlk;

    txt.setString(nazwa);    txt.setFont(fnt); txt.setCharacterSize(wielkosc/2u);
    txtR=txt.getLocalBounds(); txt.setFillColor(c);
    if(Typ==0) /// origin lewy srodek, pozycja po lewej od srodka
    {
        txt.setOrigin(txt.getOrigin().x, txtR.top+txtR.height/2.0f);
        txt.setPosition(sf::Vector2f(okno.getSize().x*0.05f,(okno.getSize().y*0.5f)+(txtR.height*pozycja*1.5f)));
    }
    else if(Typ==1)/// origin srodek, pozycja gora srodek
        {
            txt.setOrigin(txtR.left + txtR.width/2.0f, txtR.top  + txtR.height/2.0f);
            txt.setPosition(sf::Vector2f(okno.getSize().x*0.5f,okno.getSize().y*0.2f+(txtR.height*pozycja*1.5f)));
        }
    else if(Typ==2)///origin srodek, pozycja srodek
    {
        txt.setOrigin(txtR.left + txtR.width/2.0f, txtR.top  + txtR.height/2.0f);
        txt.setPosition(sf::Vector2f(okno.getSize().x*0.5f,(okno.getSize().y*0.3f)+(txtR.height*pozycja*1.5f)));
    }
    else if(Typ==3)///origin prawy gora, pozycja prawa gora
    {
        txt.setOrigin(txt.getOrigin().x+txtR.width,0);
        txt.setPosition(sf::Vector2f(okno.getSize().x,(txtR.height*pozycja*1.5f)));
    }
    if(Typ==4) /// origin lewy gora, pozycja po lewej od gory
    {
        txt.setOrigin(0,0);
        txt.setPosition(sf::Vector2f(0,(txtR.height*pozycja*1.5f)-7));
    }
    else {}
    okno.draw(txt);
}

int losuj(int a,int b)
{
    static mt19937 e(time(0));
    uniform_int_distribution<int> d(a,b);
    return d(e);
}

float losujF(float a,float b)
{
    return a + (rand() / ( RAND_MAX / (b-a) )) ;
}