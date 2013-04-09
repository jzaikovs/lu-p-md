#include <iostream>
#include "cetrsturis_d3.h"
using namespace std;

Square::Square(double _a,double _b, double _c, double _d , int _angle)//konstruktor funkcija
{
    //piešķir lokālajiem mainīgajiem vērtību
    a = _a;
    b = _b;
    c = _c;
    d = _d;
    angle = _angle;
};

Square::~Square()//dekonstruktors
{
    cout<<"\n--Cetrstuuris izdzeests--\n\n";
};


void Square::Aprekins()//Nosaka un izdrukā četrstūra tipu
{
    if (a + b + c + d == 4*a)//visas malas ir vienadas
    {

        if (angle == 90)//kvadraatam visi lenķi 90 gradu lieli
            cout<<"\n--Cetrstuuris ir kvadraats\n\n";
        else
            cout<<"\n--Centrsuuris ir rombs\n\n";
    }
    else if ((a==b && c==d)||(a==c && b==d)||(a==d && b==c)) //ja divas malas savstarpēji vienādas un divas citas ir savstarpeji vienadas tad malas preteji pa pariem ir paraleelas un vienādas
    {
        if (angle == 90)
            cout<<"\n--Cetrstuuris ir taisnsturis\n\n";
        else
            cout<<"\n--Centrsuuris ir paralelograms\n\n";
    }
    else
    {
        cout<<"\n--Cetrsturis ir cita tipa\n\n";
    }
};

void Square::Drukat()//funkcija kas izvada četrustūra izmērus
{
    std::cout<<"\n--malas: "<<a<<" "<<b<<" "<<c<<" "<<d<<"\n--lenkis: "<<angle<<"\n\n";
};

void Square::Mainit(double _a, double _b, double _c, double _d,int _angle)//funkcija kas maina parametrus četrstūrim
{
    a += _a;
    b += _b;
    c += _c;
    d += _d;
    angle += _angle;
};

