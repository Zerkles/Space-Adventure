#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include "Pomocnicze.h"

using namespace sf; using namespace std;

int main()
{
    Vector2u winSize={1280,720}; Music muzyka; muzyka.openFromFile("Zawartosc\\Dzwieki\\theme.ogg");
    muzyka.play();

    reDraw:
    Text tytul,single,multi,rdz,wyjdz;

    RenderWindow okno;
    okno.create(VideoMode(winSize.x, winSize.y, 32), "Space Adventure");

    Image Icon; Icon.loadFromFile("Zawartosc\\Tekstury\\logo.bmp");
    okno.setIcon(125,125,Icon.getPixelsPtr());

    Texture bck_txt; Sprite bck; background("menuG.jpg",bck,bck_txt,okno);

    okno.clear();
    okno.draw(bck);
    generujTekst(tytul, "Space Adventure", okno, "New Athletic M54.ttf", 0.2, Color::White, 1, 0);
    generujTekst(single, "Singleplayer", okno, "Quicksand-Bold.otf", 0.1, Color::White, 0, 0);
    generujTekst(multi, "Multiplayer", okno, "Quicksand-Bold.otf", 0.1, Color::White, 0, 0.8);
    generujTekst(rdz, "Ustawienia Rozdzielczosci", okno, "Quicksand-Bold.otf", 0.1, Color::White, 0, 2);
    generujTekst(wyjdz, "Wyjdz", okno, "Quicksand-Bold.otf", 0.1, Color::White, 0, 3);
    okno.display();

    cout<<"---RESET---MENUG---\n";

    while( okno.isOpen() )
    {
        Event event;
        while (okno.pollEvent(event))
        {
            if (event.type == Event::Closed) { okno.close(); }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) { okno.close(); }
            else if (event.type == Event::MouseButtonPressed&&czywPolu(single,Mouse::getPosition(okno))) {muzyka.stop(); okno.close(); gra(okno); muzyka.play(); goto reDraw; }
            //else if (event.type == Event::MouseButtonPressed&&czywPolu(multi,Mouse::getPosition(okno))) {muzyka.stop(); okno.close(); menuMulti(okno); muzyka.play(); goto reDraw; }
            else if (event.type == Event::MouseButtonPressed&&czywPolu(rdz,Mouse::getPosition(okno))) {okno.close(); winSize=menuRdz(okno); goto reDraw;}
            else if (event.type == Event::MouseButtonPressed&&czywPolu(wyjdz,Mouse::getPosition(okno))){okno.close();}
        }
    }
    return 0;
}