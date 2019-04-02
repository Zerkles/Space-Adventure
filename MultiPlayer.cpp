#include "MultiPlayer.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <synchapi.h>
#include "Obiekty.h"
#include "Pomocnicze.h"
#include "Menu.h"

void optymalny(){};
void ofensywny(){};
void defensywny(){};
void inteligent(){};

void dwochgraczy(RenderWindow &okno)
{
    RenderWindow okno2; okno2.create(VideoMode(okno.getSize().x, okno.getSize().y, 32), "Space Adventure"); okno2.setFramerateLimit(60);

    okno2.clear();
    Sprite* Ladowanie=new Sprite; Texture* L_text=new Texture; background("L2.jpg",*Ladowanie,*L_text,okno2);
    okno2.draw(*Ladowanie); okno2.display();

    Image Icon; Icon.loadFromFile("Zawartosc\\Tekstury\\logo.bmp");
    okno2.setIcon(125,125,Icon.getPixelsPtr());

    ///-----WCZYTYWANIE------------------------------------
    bool powrot=true; int nrZestawu=0;

    vector<Strzal*> strzaly;

    Music muzyka; muzyka.setVolume(15); muzyka.setLoop(true);
    muzyka.openFromFile("Zawartosc\\Dzwieki\\ShootingStars.ogg");

    Gracz::S_blaster.openFromFile("Zawartosc\\Dzwieki\\blaster.ogg"); Gracz::S_blaster.setVolume(120);

    Gracz gracz(okno2.getSize()),gracz2(okno2.getSize()); gracz.setSpeed(6);

    Sprite bck; Texture bck_text;
    background("space2.png",bck,bck_text,okno2);

    Sprite serce; Texture serceT; serceT.loadFromFile("Zawartosc\\Tekstury\\serce.png");
    serce.setTexture(serceT); serce.setOrigin(serce.getLocalBounds().left+serce.getLocalBounds().width,serce.getLocalBounds().top);
    float skalaS=(0.03f*okno2.getSize().x)/serceT.getSize().x;
    serce.setScale(skalaS,skalaS);    Sprite serce2=serce,serce3=serce,serce4=serce;
    serce.setPosition(okno2.getSize().x,0);
    serce2.setPosition(okno2.getSize().x-serce.getLocalBounds().width*skalaS,0);
    serce3.setPosition(okno2.getSize().x-serce.getLocalBounds().width*skalaS*2,0);
    serce4.setPosition(okno2.getSize().x-serce.getLocalBounds().width*skalaS*3,0);
    auto zycia=[&okno2,&serce,&serce2,&serce3,&serce4](unsigned int hp){
        switch(hp)
        {
            case 25:{okno2.draw(serce);} break;
            case 50:{okno2.draw(serce); okno2.draw(serce2); } break;
            case 75:{ okno2.draw(serce); okno2.draw(serce2); okno2.draw(serce3);} break;
            case 100:{ okno2.draw(serce); okno2.draw(serce2); okno2.draw(serce3); okno2.draw(serce4);} break;
        }
    };
    ///-----Koniec Wczytywania------------------------------------------------
    delete Ladowanie,L_text; muzyka.play();

    for(int i=5; i>0; i--)
    {
        Text przyg,sec; okno2.clear();
        okno2.draw(bck); okno2.draw(gracz.getSprite());
        generujTekst(przyg, "Przygotuj sie...", okno2, "New Athletic M54.ttf", 0.1, Color::White, 1, 0);
        generujTekst(sec, to_string(i), okno2, "Times New Roman.ttf", 0.1, Color::White, 1, 1.5);
        okno2.display();
        Sleep(1000);
    }

    while( powrot )
    {
        Text wynik;
//        if(gracz.getHp()<=0) {muzyka.stop(); powrot=gameover(okno2); }
//
//        if(przeszkody.empty()&&monety.empty()&&nrZestawu>=licznikM.size())
//        {
//            if(gracz.getScore()<=maxpkt*0.66){muzyka.stop(); powrot=gameover(okno2);}
//            else{ muzyka.stop(); powrot=wygrana(okno2);}
//        }

        ///warunek konca gry
        Event event;

        while(okno2.pollEvent( event ) )
        {
            if( event.type == Event::Closed ) {powrot=false; break;}
            else if( event.type == Event::KeyPressed)
            {
                if(event.key.code  == Keyboard::Escape ) { muzyka.pause(); powrot=menuPauza(okno2); muzyka.play(); }
                else if(event.key.code  == Keyboard::Space||Keyboard::isKeyPressed(Keyboard::Space)) {
                    if(strzaly.empty()||(*(*(strzaly.end()-1))).getPosition().y<=gracz.getSprite().getLocalBounds().top+strzaly[0]->getSprite().getLocalBounds().height)
                    {gracz.shot(strzaly,okno2.getSize()); Gracz::S_blaster.play();}
                }
            }
        }

        okno2.clear();

        okno2.draw(bck);

        gracz.update(event,okno2.getSize());

        if(!strzaly.empty())
        {
            auto ptr=strzaly.begin();
            for(auto el:strzaly) {
                if((*el).getDestroy()){strzaly.erase(ptr); delete el;}
                else
                {
//                    (*el).update(okno,gracz,gracz2);
                    if((*el).getPosition().y>=0){okno.draw((*el).getSprite());}
                }
                ptr++;
            }
        }

        zycia(gracz.getHp()); ///thread???

        okno2.draw(gracz.getSprite()); okno2.display();
    }
    okno2.close(); cout<<"Koniec MenuGra\n"; //return true;
}