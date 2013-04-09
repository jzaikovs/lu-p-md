#include <iostream>
#include <math.h>
#include "d11_triangle.h"
using namespace std;

Triangle::Triangle(double a,double b, double c)
{
    //piešķir lokālajiem mainīgajiem vērtību
    this->a = a;
    this->b = b;
    this->c = c;
};

Triangle::~Triangle()//dekonstruktors
{
    cout<<"Trijstuuris izdzeests!!!";
};

void Triangle::Aprekins()
{
    double aa = a*a;
    double bb = b*b;
    double cc = c*c;

    //mediānas
    cout<<sqrt((2*(bb+cc)-aa)/4)<<endl;
    cout<<sqrt((2*(aa+bb)-cc)/4)<<endl;
    cout<<sqrt((2*(aa+cc)-bb)/4)<<endl;

    double m  = max(a, max(b, c));
    double n = min(a, min(b, c));
    double k = a + b + c - m - n;

    double d = sqrt(n*n+k*k); //kvadrātsakne no īsāko malu kvadrātu summas

    if (d==m)
    {
        cout<<"Trijsturis ir taisnlenkja.\n";
    }
    else
    {
        if (d>m)cout<<"Trijsturis ir shaurlenkja\n";
        else cout<<"Trijsturis ir platlenkja";
    }
};

void Triangle::Drukat()
{
    //tiek izdrukaatas trijsturas malas
    std::cout<<"malas: "<<a<<" "<<b<<" "<<c<<endl;
};

void Triangle::Mainit(double change_a, double change_b, double change_c)
{
    //trijstūra parametru maiņa
    this->a += change_a;
    this->b += change_b;
    this->c += change_c;

    double m  = max(a,max(b,c));
    double n = min(a, min(b,c));
    double k = a + b + c - m - n;

    //parbauda vai trijstūris ir iespējams

    if (n+k <= m)
    {
        cout<<"Shadi izmainiit nevar\n";
        this->a -= change_a;
        this->b -= change_b;
        this->c -= change_c;
    }
};
