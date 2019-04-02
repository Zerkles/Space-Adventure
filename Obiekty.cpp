#include "Obiekty.h"
#include "Pomocnicze.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>

using namespace sf; using namespace std;

Music Moneta::S_coin;
Music Gracz::S_blaster;
Music Przeszkoda::S_crash;
unsigned int Strzal::counter=0;
unsigned int Moneta::counter=0;
unsigned int Przeszkoda::counter=0;


void Obiekt::setTexture(const string &nazwa)
{
    text.loadFromFile("Zawartosc\\Tekstury\\"+nazwa);
    sprajt.setTexture(text); FloatRect sprajtR=sprajt.getGlobalBounds();
    sprajt.setOrigin(sprajtR.left + sprajtR.width/2.0f, sprajtR.top  + sprajtR.height/2.0f);
}

void Gracz::update(const Event &zdarzenie, Vector2u winSize)
{
    Vector2f velocity{0,0};

    if(Keyboard::isKeyPressed(Keyboard::Left)&&getEdges(sprajt).left>0)
    {
        if(getEdges(sprajt).left-getSpeed()<0) {velocity.x=getEdges(sprajt).left*(-1);}
        else {velocity.x=-1*getSpeed();}
    }
    if(Keyboard::isKeyPressed(Keyboard::Right)&&getEdges(sprajt).right<winSize.x)
    {
        if(getEdges(sprajt).right+getSpeed()>winSize.x) {velocity.x=winSize.x-getEdges(sprajt).right;}
        else
            {
                velocity.x=getSpeed();
            }
    }
    if(Keyboard::isKeyPressed(Keyboard::Up)&&getEdges(sprajt).up>0)
    {
        if (getEdges(sprajt).up - getSpeed() < 0) { velocity.y = getEdges(sprajt).up*(-1); }
        else { velocity.y = -1*getSpeed(); }
    }
    if(Keyboard::isKeyPressed(Keyboard::Down)&&getEdges(sprajt).down<winSize.y)
    {
        if (getEdges(sprajt).down + getSpeed() > winSize.y) { velocity.y = winSize.y-getEdges(sprajt).down; }
        else { velocity.y = getSpeed(); }
    }
    sprajt.move(velocity.x, velocity.y);
}

vector<Moneta*> Moneta::generujMonety(unsigned int ile,float speed,Vector2f pos,const RenderWindow &okno)
{
    vector<Moneta*> wek; ile;
    for(int i=0;i<ile;i++)
    {
        auto ptr=new Moneta(okno.getSize()); (*ptr).setSpeed(speed); ptr->setPosition(pos);
        wek.push_back(ptr);
        pos.y-=ptr->getSprite().getGlobalBounds().height*1.5;
        ptr=nullptr;
    }
    return wek;
}

vector<int>Moneta::indeksowanieMonet(unsigned int ile)
{
    vector<int> wek; int sum=0; int i=0;

    while(sum<=ile)
    {
        wek.push_back(losuj(1,5));
        sum+=wek[i];
        i++;
    }
    return wek;
}

void Moneta::update(Vector2u winSize,Gracz &g)
{
    if(getEdges(sprajt).down>=winSize.y)
    {cout<<"Moneta, Dola Krawedz!\n"; toDestroy=true;}

    else if(czyZderzenie(*this,g))
    {
        cout<<"Moneta Zderzenie!\n"; toDestroy=true; g.setScore(1);
        S_coin.play();
    }

    //if (getEdges(sprajt).down + getSpeed() > winSize.y) {sprajt.move({0,winSize.y-getEdges(sprajt).down});}
    sprajt.move({0,getSpeed()});
}

void Przeszkoda::update(Vector2u winSize,Gracz &g) {
    if (getEdges(sprajt).down >= winSize.y) {
        cout << "Przeszkoda, Dola Krawedz!\n";
        toDestroy = true;
    }
    else if (czyZderzenie(*this, g)) {
        cout << "Przeszkoda Zderzenie!\n";
        toDestroy = true;
        g.setHp(-25);
        S_crash.play();
    }
    else {sprajt.move({0,getSpeed()});}
}

Sprite background(const string &nazwa,Sprite& sprajt,Texture &txt,const RenderWindow &okno)
{
    txt.loadFromFile("Zawartosc\\Tekstury\\"+nazwa);
    sprajt.setTexture(txt); sprajt.setPosition(0,0);
    double x;

    if(txt.getSize().x>okno.getSize().x) {x=1.0/txt.getSize().x; x*=okno.getSize().x;}
    else{x=1.0/okno.getSize().x; x*=txt.getSize().x;}

    //float skala=(okno.getSize().x)/txt.getSize().x;
    //sprajt.setScale(skala,skala);

    sprajt.setScale(x,x);
    return sprajt;
}

template<class G,class M,class P>void  Strzal::update(RenderWindow &okno, G &g, vector<M*> &monety, vector<P*> &przeszkody)
{
    if(getEdges(sprajt).up<=0)
    {cout<<"Strzal, Gorna Krawedz Zderzenie!\n"; toDestroy=true;}

    else if(czyZderzenie(*this,g))
    { cout<<"Strzal Gracz Zderzenie!\n"; toDestroy=true; g.setHp(-25); }

    for (auto el:monety)
    { if(czyZderzenie(*el,*this)){cout<<"Strzal Moneta Zderzenie!\n"; toDestroy=true; el->setDestroy(true);}}

    for (auto el:przeszkody)
    { if(czyZderzenie(*el,*this)){cout<<"Strzal Przeszkoda Zderzenie!\n"; toDestroy=true; el->setDestroy(true);}}

    sprajt.move({0,(-1)*getSpeed()});
}

template<class G> void Strzal::update(RenderWindow &okno, G &g, G &g2)
{
    if(getEdges(sprajt).up<=0)
    {cout<<"Strzal, Gorna Krawedz Zderzenie!\n"; toDestroy=true;}

    else if(czyZderzenie(*this,g))
    { cout<<"Strzal Gracz1 Zderzenie!\n"; toDestroy=true; g.setHp(-25); }

    else if(czyZderzenie(*this,g2))
    { cout<<"Strzal Gracz1 Zderzenie!\n"; toDestroy=true; g2.setHp(-25); }

    sprajt.move({0,(-1)*getSpeed()});
}

void Postac::shot(vector<Strzal*> &strzaly, const Vector2u &winSize)
{
Strzal* s=new Strzal(winSize); s->setPosition({this->getPosition().x,getEdges(sprajt).up-1}); s->setOwner("Gracz"); strzaly.push_back(s);
}

void ObslugaObiektow(RenderWindow &okno, Gracz &g, vector<Moneta*> &monety, vector<Przeszkoda*> &przeszkody, vector<Strzal*> &wek)
{
    if(!wek.empty())
    {
        auto ptr=wek.begin();
        for(auto el:wek) {
            if((*el).getDestroy()){wek.erase(ptr); delete el;}
            else
            {
                (*el).update(okno,g,monety,przeszkody);
                if((*el).getPosition().y>=0){okno.draw((*el).getSprite());}
            }
            ptr++;
        }
    }
}