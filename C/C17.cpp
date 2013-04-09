/*******************************************
autors: @jzaikovs
izveidots: 23.11.2009

C17. Doti trīs skaitļu trijnieki a,b,c.
Katrs skaitļu trijnieks nosaka taisni, kas uzdota sekojošā veidā: ax+by=c.
Ja taišņu krustpunkti veido  trīsstūra virsotnes, tad izdrukāt šī trīsstūra laukumu, ja neveido, tad uzrādīt taisnes, kas ir paralēlas.
*******************************************/

#include <iostream>
#include <math.h>
using namespace std;

struct point
{
    double x, y;
};

struct line
{
    double a,b,c;
};

point solve(line v1, line v2);

double attalums(point A, point B);

double area(double a, double b, double c);

double d(line v1, line v2);

double d(line v1, line v2, line v3);

int main()
{
    int ok;

    do
    {

        line _a = {0,1,2};
        line _b = {1,0,2};
        line _c = {1,1,2};

        //ievade
        cout<<"taisne a:\n";
        cin>>_a.a>>_a.b>>_a.c;

        cout<<"taisne b:\n";
        cin>>_b.a>>_b.b>>_b.c;

        cout<<"taisne c:\n";
        cin>>_c.a>>_c.b>>_c.c;

        //vai ir trijstūris
        if (d(_a,_b) * d(_a,_c) * d(_b,_c) * d(_a,_b,_c) !=0)
        {
            //aprēķināt visus krustpunktus
            point A = solve(_a, _b);
            cout<<"punkts A("<<A.x<<", "<<A.y<<")\n";
            point B = solve(_a, _c);
            cout<<"punkts B("<<B.x<<", "<<B.y<<")\n";
            point C = solve(_b, _c);
            cout<<"punkts C("<<C.x<<", "<<C.y<<")\n";

            //aprēķināt attālumus starp punktiem
            double a = attalums(A,B);
            cout<<"no A lidz B ir "<<a<<" vieniibas\n";
            double b = attalums(B,C);
            cout<<"no B lidz C ir "<<b<<" vieniibas\n";
            double c = attalums(C,A);
            cout<<"no C lidz A ir "<<c<<" vieniibas\n";

            //aprēķināt trijstūra laukumu
            double tArea = area(a, b, c);

            //izvadīt laukumu
            cout<<"Trijstura laukums: "<<tArea<<endl;
        }
        else
        {
            //ja neveidojās trijstuuris paziņot par paralēlajām malām
            cout<<"taisnes neveido trijsturi\n";
            if (d(_a,_b)==0) cout<<"Paralelas taisnes: A un B\n";
            if (d(_a,_c)==0) cout<<"Paralelas taisnes: A un C\n";
            if (d(_b,_c)==0) cout<<"Paralelas taisnes: B un C\n";
        }

        cout << "Vai turpinat (1) vai beigt (0)?" << endl;
        cin >> ok;
    }
    while (ok == 1);

    return 0;
}

double d(line v1, line v2)
{
    return v1.a * v2.b - v1.b * v2.a;
}


double d(line v1, line v2, line v3)
{
    double a1 = v1.a * ((v2.b * v3.c)-(v2.c * v3.b));
    double a2 = -1 * v1.b * ((v2.a * v3.c)-(v2.c * v3.a));
    double a3 = v1.c * ((v2.a * v3.b)-(v2.b * v3.a));

    return a1+a2+a3;
}


point solve(line v1, line v2)//nosaka kruspunktu divām taisnēm, kas izteiktas vienādojumu sistēma, atrsisina ar Kramera formulu
{
    point a;

    a.x = 0;
    a.y = 0;

    double vd = d(v1,v2);//deternminats vienadojumu sistēmai
    double d2 = v1.c * v2.b - v1.b * v2.c;
    double d3 = v1.a * v2.c -  v1.c * v2.a;

    if (vd!=0)//drošībai
    {
        a.x = d2 / vd;
        a.y = d3 / vd;
    }

    return a;
}

double attalums(point A, point B)//attālums starp diviem punktiem, pitagora teorēm.
{
    double dx = A.x - B.x;
    double dy = A.y - B.y;

    return sqrt(dx*dx + dy*dy);
}

double area(double a, double b, double c)//trijstūra laukuma aprēķināšana pēc Herona formulas
{
    double p = (a + b +c)/2;//pusperimetrs

    return sqrt(p * (p-a) * (p-b) * (p-c));
}


/*	TESTA PIEMĒRI

   A		  B		     C
1  0 -2    1  0  4    1  1  2  => visas taisnes krustojās vienā vietā
0  1  3    1  0  4    0  1  1  => paralēlas A un B
0  1  2    1  0  2    1  1  2  => laukums: 2.0
0  1 -2    1  0  4   -1  2 -4  => laukums: 4.0



*/

