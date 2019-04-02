#include "Menu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <afxres.h>
#include "Pomocnicze.h"
#include "Obiekty.h"
#include "AI.h"


bool wygrana(RenderWindow &okno)
{
    okno.resetGLStates();

    Music win; win.setLoop(true); win.openFromFile("Zawartosc\\Dzwieki\\win.ogg");

    Text tytul,restart,menuG,wyjdz; bool powrot=true,czyMenuG;

    generujTekst(tytul, "You Win", okno, "New Athletic M54.ttf", 0.2, Color::White, 1, 0);
    generujTekst(restart, "Restart", okno, "Quicksand-Bold.otf", 0.07, Color::White, 2, 2.5f);
    generujTekst(menuG, "Menu Glowne", okno, "Quicksand-Bold.otf", 0.07, Color::White, 2, 3.85f);
    generujTekst(wyjdz, "Wyjdz z Gry", okno, "Quicksand-Bold.otf", 0.07, Color::White, 2, 4.3f);
    okno.display();

    Sleep(1000); win.play();

    while( powrot )
    {
        Event event;
        while(okno.pollEvent( event ) )
        {
            if( event.type == Event::Closed ) {exit(0);}
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {powrot=false; czyMenuG=false; break;}
            if (event.type == Event::MouseButtonPressed&&czywPolu(restart,Mouse::getPosition(okno))) {okno.setVisible(false); win.stop(); czyMenuG=gra(okno);}
            if (event.type == Event::MouseButtonPressed&&czywPolu(menuG,Mouse::getPosition(okno))) {powrot=false; czyMenuG=false; break;}
            if (event.type == Event::MouseButtonPressed&&czywPolu(wyjdz,Mouse::getPosition(okno))) {exit(0);}
        }
    }
    cout<<"Koniec GameOver\n"; win.stop(); return czyMenuG;
}

bool gameover(RenderWindow &okno)
{
    okno.resetGLStates();

    Music lost; lost.setLoop(true); lost.openFromFile("Zawartosc\\Dzwieki\\lost.ogg");

    Text tytul,restart,menuG,wyjdz; bool powrot=true,czyMenuG;

    generujTekst(tytul, "GameOver", okno, "New Athletic M54.ttf", 0.2, Color::White, 1, 0);
    generujTekst(restart, "Restart", okno, "Quicksand-Bold.otf", 0.07, Color::White, 2, 2.5f);
    generujTekst(menuG, "Menu Glowne", okno, "Quicksand-Bold.otf", 0.07, Color::White, 2, 3.85f);
    generujTekst(wyjdz, "Wyjdz z Gry", okno, "Quicksand-Bold.otf", 0.07, Color::White, 2, 4.3f);
    okno.display();

    Sleep(1000); lost.play();

    while( powrot )
    {
        Event event;
        while(okno.pollEvent( event ) )
        {
            if( event.type == Event::Closed ) {exit(0);}
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {powrot=false; czyMenuG=false; break;}
            if (event.type == Event::MouseButtonPressed&&czywPolu(restart,Mouse::getPosition(okno))) {lost.stop(); okno.setVisible(false); czyMenuG=gra(okno);}
            if (event.type == Event::MouseButtonPressed&&czywPolu(menuG,Mouse::getPosition(okno))) {powrot=false; czyMenuG=false; break;}
            if (event.type == Event::MouseButtonPressed&&czywPolu(wyjdz,Mouse::getPosition(okno))) {exit(0);}
        }
    }
    cout<<"Koniec GameOver\n"; lost.stop(); return czyMenuG;
}

Vector2u menuMulti(RenderWindow &okno)
{
    Text tytul,multi,off,deff,opt,ai,wroc; Vector2u winSize; bool powrot=true;

    Texture bck_txt;
    Sprite bck; background("menuG.jpg",bck,bck_txt,okno);

    auto reset=[&winSize,&okno,&tytul,&multi, &off, &deff, &opt, &wroc, &ai, &bck, &bck_txt] ()
    {
        okno.create(VideoMode(okno.getSize().x, okno.getSize().y, 32), "Space Adventure"); okno.clear();
        Image Icon; Icon.loadFromFile("Zawartosc\\Tekstury\\logo.bmp"); okno.setIcon(125,125,Icon.getPixelsPtr());

        background("menuG.jpg",bck,bck_txt,okno); okno.draw(bck);
        generujTekst(tytul, "Awesome Adventure", okno, "New Athletic M54.ttf", 0.2, Color::White, 1, 0);
        generujTekst(multi, "Dwoch Graczy", okno, "Quicksand-Bold.otf", 0.07, Color::White, 0, -1);
        generujTekst(opt, "Graj z Komputerem(Algorytm Optymalny)", okno, "Quicksand-Bold.otf", 0.07, Color::White, 0, 0);
        generujTekst(off, "Graj z Komputerem(Algorytm Ofensywny)", okno, "Quicksand-Bold.otf", 0.07, Color::White, 0, 1);
        generujTekst(deff, "Graj z Komputerem(Algorytm Defensywny)", okno, "Quicksand-Bold.otf", 0.07, Color::White, 0, 2);
        generujTekst(ai, "Graj z Komputerem(AI)", okno, "Quicksand-Bold.otf", 0.07, Color::White, 0, 3);
        generujTekst(wroc, "Wroc", okno, "Quicksand-Bold.otf", 0.07, Color::White, 0, 6);
        okno.display();
    };

    reset();

    while( powrot )
    {
        Event wydarzenie;
        while (okno.pollEvent(wydarzenie))
        {
            if (wydarzenie.type == Event::Closed) { powrot=false; }
            else if (wydarzenie.type == Event::KeyPressed && wydarzenie.key.code == Keyboard::Escape) { powrot=false; }
            else if (wydarzenie.type == Event::MouseButtonPressed&&czywPolu(multi,Mouse::getPosition(okno)))
            { dwochgraczy(okno); } ///dodac gre
            else if (wydarzenie.type == Event::MouseButtonPressed&&czywPolu(off,Mouse::getPosition(okno)))
            { winSize ={1280,720}; okno.setSize(winSize); reset(); } ///dodac gre
            else if (wydarzenie.type == Event::MouseButtonPressed&&czywPolu(deff,Mouse::getPosition(okno)))
            { winSize ={1366,768}; okno.setSize(winSize); reset(); } ///dodac gre
            else if (wydarzenie.type == Event::MouseButtonPressed&&czywPolu(opt,Mouse::getPosition(okno)))
            { winSize ={1920,1080}; okno.setSize(winSize); reset(); } ///dodac gre
            else if (wydarzenie.type == Event::MouseButtonPressed&&czywPolu(ai,Mouse::getPosition(okno)))
            { winSize ={1920,1080}; okno.setSize(winSize); reset(); } ///dodac gre
            else if (wydarzenie.type == Event::MouseButtonPressed&&czywPolu(wroc,Mouse::getPosition(okno)))
            { powrot=false; }
        }
    }
    cout<<"Koniec MenuMulti\n"; return okno.getSize();
}

Vector2u menuRdz(RenderWindow &okno)
{
    Text tytul,r1024x600, r1280x720, r1366x768, r1920x1080, wroc, fullS; Vector2u winSize; bool powrot=true;

    Texture bck_txt;
    Sprite bck; background("menuG.jpg",bck,bck_txt,okno);

    auto reset=[&winSize,&okno,&tytul,&r1024x600, &r1280x720, &r1366x768, &r1920x1080, &wroc, &fullS, &bck, &bck_txt] ()
    {
    okno.create(VideoMode(okno.getSize().x, okno.getSize().y, 32), "Space Adventure"); okno.clear();
    Image Icon; Icon.loadFromFile("Zawartosc\\Tekstury\\logo.bmp"); okno.setIcon(125,125,Icon.getPixelsPtr());

    background("menuG.jpg",bck,bck_txt,okno); okno.draw(bck);
    generujTekst(tytul, "Awesome Adventure", okno, "New Athletic M54.ttf", 0.2, Color::White, 1, 0);
    generujTekst(r1024x600, "1024x600", okno, "Quicksand-Bold.otf", 0.07, Color::White, 0, 0);
    generujTekst(r1280x720, "1280x720", okno, "Quicksand-Bold.otf", 0.07, Color::White, 0, 1);
    generujTekst(r1366x768, "1366x720", okno, "Quicksand-Bold.otf", 0.07, Color::White, 0, 2);
    generujTekst(r1920x1080, "1920x1080", okno, "Quicksand-Bold.otf", 0.07, Color::White, 0, 3);
    //generujTekst(fullS, "FullScreen", okno, "Quicksand-Bold.otf", 0.07, Color::White, 0, 4);
    generujTekst(wroc, "Wroc", okno, "Quicksand-Bold.otf", 0.07, Color::White, 0, 6);
    okno.display();
    };

    reset();

    while( powrot )
    {
        Event wydarzenie;
        while (okno.pollEvent(wydarzenie))
        {
            if (wydarzenie.type == Event::Closed) { powrot=false; }
            else if (wydarzenie.type == Event::KeyPressed && wydarzenie.key.code == Keyboard::Escape) { powrot=false; }
            else if (wydarzenie.type == Event::MouseButtonPressed&&czywPolu(r1024x600,Mouse::getPosition(okno)))
            { winSize ={1024,600}; okno.setSize(winSize); reset(); }

            else if (wydarzenie.type == Event::MouseButtonPressed&&czywPolu(r1280x720,Mouse::getPosition(okno)))
            { winSize ={1280,720}; okno.setSize(winSize); reset(); }

            else if (wydarzenie.type == Event::MouseButtonPressed&&czywPolu(r1366x768,Mouse::getPosition(okno)))
            { winSize ={1366,768}; okno.setSize(winSize); reset(); }

            else if (wydarzenie.type == Event::MouseButtonPressed&&czywPolu(r1920x1080,Mouse::getPosition(okno)))
            { winSize ={1920,1080}; okno.setSize(winSize); reset(); }

            else if (wydarzenie.type == Event::MouseButtonPressed&&czywPolu(wroc,Mouse::getPosition(okno)))
            { powrot=false; }
            //else if (wydarzenie.type == Event::MouseButtonPressed&&czywPolu(fullS,Mouse::getPosition(okno)))
           //{okno.close(); okno.create(VideoMode(okno.getSize().x, okno.getSize().y, 32), "Awesome Adventure|MenuR",Style::Fullscreen); reset();}
        }
    }
    cout<<"Koniec MenuR\n"; return okno.getSize();
}

bool menuPauza(RenderWindow &okno)
{
    okno.resetGLStates();

    Text tytul,wznow,restart,menuG,wyjdz; bool powrot=true,czyMenuG;

    generujTekst(tytul, "Pause", okno, "New Athletic M54.ttf", 0.2, Color::White, 1, 0);
    generujTekst(wznow, "Wznow Gre", okno, "Quicksand-Bold.otf", 0.07, Color::White, 2, 1.0f);
    generujTekst(restart, "Restart", okno, "Quicksand-Bold.otf", 0.07, Color::White, 2, 2.5f);
    generujTekst(menuG, "Menu Glowne", okno, "Quicksand-Bold.otf", 0.07, Color::White, 2, 3.85f);
    generujTekst(wyjdz, "Wyjdz z Gry", okno, "Quicksand-Bold.otf", 0.07, Color::White, 2, 4.3f);
    okno.display();

    while( powrot )
    {
        Event event;
        while(okno.pollEvent( event ) )
        {
            if( event.type == Event::Closed ) {exit(0);}
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) { powrot=false; czyMenuG=true; break;}
            if (event.type == Event::MouseButtonPressed&&czywPolu(wznow,Mouse::getPosition(okno))) {powrot=false; czyMenuG=true; break;}
            if (event.type == Event::MouseButtonPressed&&czywPolu(restart,Mouse::getPosition(okno))) {okno.setVisible(false); czyMenuG=gra(okno);}
            if (event.type == Event::MouseButtonPressed&&czywPolu(menuG,Mouse::getPosition(okno))) {powrot=false; czyMenuG=false; break;}
            if (event.type == Event::MouseButtonPressed&&czywPolu(wyjdz,Mouse::getPosition(okno))) {exit(0);}
        }
    }
    cout<<"Koniec MenuP\n"; return czyMenuG;
}

bool gra(RenderWindow &okno)
{
    RenderWindow okno2; okno2.create(VideoMode(okno.getSize().x, okno.getSize().y, 32), "Space Adventure"); okno2.setFramerateLimit(60);

    okno2.clear();
    Sprite* Ladowanie=new Sprite; Texture* L_text=new Texture; background("L2.jpg",*Ladowanie,*L_text,okno2);
    okno2.draw(*Ladowanie); okno2.display();

    Image Icon; Icon.loadFromFile("Zawartosc\\Tekstury\\logo.bmp");
    okno2.setIcon(125,125,Icon.getPixelsPtr());

    ///-----WCZYTYWANIE------------------------------------
    bool powrot=true; float predkoscTla=3; int nrZestawu=0;

    vector<int> licznikM=Moneta::indeksowanieMonet(50); int maxpkt=0; for(auto el:licznikM){maxpkt+=el;}

    vector<Moneta*> monety; vector<Strzal*> strzaly; vector<Przeszkoda*> przeszkody;

    Music muzyka; muzyka.setVolume(15); muzyka.setLoop(true);
    muzyka.openFromFile("Zawartosc\\Dzwieki\\ShootingStars.ogg");
    Moneta::S_coin.openFromFile("Zawartosc\\Dzwieki\\coin.ogg"); Moneta::S_coin.setVolume(120);
    Gracz::S_blaster.openFromFile("Zawartosc\\Dzwieki\\blaster.ogg"); Gracz::S_blaster.setVolume(120);
    Przeszkoda::S_crash.openFromFile("Zawartosc\\Dzwieki\\crash.ogg"); Przeszkoda::S_crash.setVolume(120);

    Gracz gracz(okno2.getSize()); gracz.setSpeed(6);

    Sprite bck,bck2; Texture bck_text;
    background("space2.png",bck,bck_text,okno2);
    bck2=bck; bck2.setPosition(0,(-1)*bck.getGlobalBounds().height);

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
        if(gracz.getHp()<=0) {muzyka.stop(); powrot=gameover(okno2); }

        if(przeszkody.empty()&&monety.empty()&&nrZestawu>=licznikM.size())
        {
            if(gracz.getScore()<=maxpkt*0.66){muzyka.stop(); powrot=gameover(okno2);}
            else{ muzyka.stop(); powrot=wygrana(okno2);}
        }

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


        if(monety.empty()||monety.back()->getPosition().y>=okno2.getSize().y*0.25)
        {
            if(nrZestawu<licznikM.size()){
                Moneta *m = new Moneta(okno2.getSize()); Moneta::decreaseCounter();
                float skalaM=(0.1f*okno2.getSize().x)/m->getTexture().getSize().x;
                ///losowanko na dole
                Vector2f losujPozycje={losujF((*m).getSprite().getLocalBounds().width*skalaM/2, okno2.getSize().x - (*m).getSprite().getLocalBounds().width*skalaM/2), 0};
                m->setPosition(losujPozycje);

                auto pokrycieM=[m,przeszkody]()
                {
                    for (auto el:przeszkody)
                    {
                        if(czyZderzenie(*el,*m)){cout<<el->getPosition().x<<' '<<el->getPosition().y; return true; }
                    }return false;
                };

                while(pokrycieM())
                {
                    losujPozycje.x=losuj((*m).getSprite().getLocalBounds().width*skalaM/2, okno2.getSize().x - (*m).getSprite().getLocalBounds().width*skalaM/2);
                    m->setPosition(losujPozycje);
                }
                vector<Moneta *> monetyT = Moneta::generujMonety(licznikM[nrZestawu], predkoscTla,losujPozycje,okno2);

                for (auto el:monetyT) { monety.push_back(el); }
                nrZestawu++; delete m;
            }
        }

        if(nrZestawu<=licznikM.size()&&(przeszkody.empty()||przeszkody.back()->getPosition().y>=okno2.getSize().y*0.33)) {

            if(nrZestawu<licznikM.size()){
                Przeszkoda *p=new Przeszkoda(okno2.getSize()); (*p).setSpeed(predkoscTla);
                float skalaP=(0.1f*okno2.getSize().x)/p->getTexture().getSize().x;///losowanko na dole

                p->setPosition({losujF(0+p->getSprite().getLocalBounds().width*skalaP/2, okno2.getSize().x - p->getSprite().getLocalBounds().width*skalaP/2), 0});

                auto pokrycieP=[monety,p]()
                {
                    for (auto el:monety)
                    {
                        if(czyZderzenie(*el,*p)) { return true; }
                    }return false;
                };

                while(pokrycieP())
                {///losowanko na dole
                    p->setPosition({losujF(0+p->getSprite().getLocalBounds().width*skalaP/2, okno2.getSize().x - p->getSprite().getLocalBounds().width*skalaP/2), 0});
                }
                przeszkody.push_back(p);
            }
        }

        if(bck.getPosition().y>=okno2.getSize().y||bck2.getPosition().y>=okno2.getSize().y)
        {
            if(bck.getPosition().y>=okno2.getSize().y){bck.setPosition(0,(-1)*bck.getGlobalBounds().height);}
            else {bck2.setPosition(0,(-1)*bck.getGlobalBounds().height);}
        }

        okno2.clear();

        okno2.draw(bck); okno2.draw(bck2);
        bck.move({0,predkoscTla}); bck2.move({0,predkoscTla});

        gracz.update(event,okno2.getSize());

        ObslugaObiektow(okno2,gracz,monety); ObslugaObiektow(okno2,gracz,przeszkody); ObslugaObiektow(okno2,gracz,monety,przeszkody,strzaly);

        generujTekst(wynik, "Wynik: "+to_string(gracz.getScore()*100), okno2, "Times New Roman.ttf", 0.05f, Color::White, 4, 0);///thread???
        zycia(gracz.getHp()); ///thread???

        okno2.draw(gracz.getSprite()); okno2.display();
    }
    okno2.close(); cout<<"Koniec MenuGra\n"; return true;
}