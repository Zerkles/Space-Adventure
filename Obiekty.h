//
// Created by Wojtek-Laptop on 11.03.2018.
//

#ifndef PROJEKTCPP_OBIEKTY_H
#define PROJEKTCPP_OBIEKTY_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>

using namespace sf; using namespace std;

class getEdges
{
public:
    float left,right,up,down;
    getEdges()=delete;
    getEdges(const Sprite &sprt)
    {
        FloatRect sprajtR=sprt.getGlobalBounds();

        right=sprajtR.left+sprajtR.width; left=sprajtR.left;
        up=sprajtR.top; down=sprajtR.top+sprajtR.height;
    }
};
///------------------------------------------------------
class Obiekt
{
public:
    void setPosition(const Vector2f &pos){sprajt.setPosition(pos);}
    void setSpeed(const float &spd){speed=spd;}
    Sprite& setSprite(){return sprajt;}
    void setTexture(const string &nazwa);
    void setDestroy(const bool &b){toDestroy=b;};

    const Vector2f getPosition(){return sprajt.getPosition();}
    float getSpeed() {return speed;}
    Texture& getTexture(){return text;}
    const Sprite getSprite(){return sprajt;}
    const bool getDestroy(){return toDestroy;}

    virtual void update(Vector2u winSize){cout<<"Brak Spersonalizowanego Update!";}

protected:
float speed; Texture text; Sprite sprajt;  string ID;   bool toDestroy=false;
};
///------------------------------------------------------
class Strzal:public Obiekt
{
public:
    Strzal(const Vector2u &winSize)
    {
        ID="St_"+to_string(counter); counter++;

        //cout<<"Utworzono Strzal!\n";
        setTexture("laser2.png");

        float skala=(0.006f*winSize.x)/text.getSize().x;
        sprajt.setScale(skala,skala);

        speed=20;
        sprajt.setOrigin(sprajt.getLocalBounds().left + sprajt.getLocalBounds().width/2.0f, sprajt.getLocalBounds().top  + sprajt.getLocalBounds().height);
    }
    ~Strzal(){}//cout<<"Zniszczono Strzal!\n";}
    void setOwner(const string &own){owner=own;}
    const string getOwner(){return owner;}

    template<class G,class M,class P>void  update(RenderWindow &okno, G &g, vector<M*> &monety, vector<P*> &przeszkody);
    template<class G> void update(RenderWindow &okno,G &g,G &g2);

protected:
    string owner; static unsigned int counter;
};
///------------------------------------------------------
class Postac:public Obiekt
{
public:
    void setHp(const int &zmiana){hp+=zmiana;}
    int getHp(){return hp;}

    void shot(vector<Strzal*> &strzaly,const Vector2u &winSize);

protected:
    unsigned int hp;
};
///------------------------------------------------------
class Gracz:public Postac
{
public:
    Gracz(const Vector2u &winSize):score(0)
    {
        cout<<"Stworzono gracza!\n";

        setTexture("model2.png");
        setPosition({winSize.x*0.5f,winSize.y*0.75f});
        speed=5.0f; hp=100;

        float skala=(0.1f*winSize.x)/text.getSize().x;
        sprajt.setScale(skala,skala);
    }
    ~Gracz(){cout<<"Zniszczno gracza!\n";}

    void setScore(const unsigned int &zmiana){score+=zmiana;}
    unsigned int getScore(){return score;}

    void update(const Event &zdarzenie,Vector2u winSize);

    static Music S_blaster;
private:
    unsigned int score;
};

///------------------------------------------------------
class Moneta:public Obiekt
{
public:
Moneta(const Vector2u &winSize) {
    ID="M_"+to_string(counter); counter++;

    cout<<"Stworzono Monete! "+ID<<endl;
    setTexture("moneta2.png");

    float skala=(0.05f*winSize.x)/text.getSize().x;
    sprajt.setScale(skala,skala);
    }
~Moneta(){cout<<"Zniszczono Monete! "+ID<<endl;}

void update(Vector2u winSize,Gracz &g);

static vector<Moneta*> generujMonety(unsigned int ile,float speed,Vector2f pos,const RenderWindow &okno);
static vector<int>indeksowanieMonet(unsigned int ile);
static void decreaseCounter(){counter--;}

static Music S_coin;

protected:
static unsigned int counter;
};
///------------------------------------------------------
class Przeszkoda:public Obiekt
{
public:
    Przeszkoda(const Vector2u &winSize)
    {
        ID="P_"+to_string(counter); counter ++;

        cout<<"Stworzono Przeszkode! "+ID<<endl;
        setTexture("astr2.png");

        float skala=(0.1f*winSize.x)/text.getSize().x;
        sprajt.setScale(skala,skala);}

    ~Przeszkoda(){cout<<"Zniszczono Przeszkode! "+ID<<endl;}

    void update(Vector2u winSize,Gracz &g);
    static void decreaseCounter(){counter--;}

    static Music S_crash;

protected:
    static unsigned int counter;
};
///------------------------------------------------------
template<class t>
void ObslugaObiektow(RenderWindow &okno,Gracz &gracz,vector<t> &wek)
{
    if(!wek.empty())
    {
        auto ptr=wek.begin();
        for(auto el:wek) {
            if((*el).getDestroy()){wek.erase(ptr); delete el;}
            else
            {
                (*el).update(okno.getSize(), gracz);
                if((*el).getPosition().y>=0){okno.draw((*el).getSprite());}
            }
            ptr++;
        }
    }
}
///------------------------------------------------------
void ObslugaObiektow(RenderWindow &okno, Gracz &g, vector<Moneta*> &monety, vector<Przeszkoda*> &przeszkody, vector<Strzal*> &wek);
///------------------------------------------------------
Sprite background(const string &nazwa,Sprite& sprajt,Texture &txt,const RenderWindow &okno);

#endif //PROJEKTCPP_OBIEKTY_H
