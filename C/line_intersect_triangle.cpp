#include <iostream>
#include <math.h>

using namespace std;

struct punkts
{
    double x,y;
};

struct line
{
    double a,b,c;
};

line createLineByPoint(punkts A, punkts B);
bool interact(line v1, line v2);
punkts getInteraction(line v1, line v2);
double dist(punkts A, punkts B);
double triangleSize(double a, double b, double c);

int main()
{
    punkts A = {-4,1};
    punkts B = {1,4};
    punkts C = {6,1};

    cout<<"Ievadi trijstura punkt koardinates!"<<endl;
    ///.....

    line a,b,c;

    a = createLineByPoint(A,B);
    b = createLineByPoint(B,C);
    c = createLineByPoint(A,C);

    //test�jam vai ir pareizas l�nijas
    cout<<"line_a: "<<a.a<<" "<<a.b<<" "<<a.c<<endl;
    cout<<"line_b: "<<b.a<<" "<<b.b<<" "<<b.c<<endl;
    cout<<"line_c: "<<c.a<<" "<<c.b<<" "<<c.c<<endl;

    //pie�emot to ka vienm�r veidosies trijst�ris

    line t = {0,-5,-12.5};//japievieno sakumi��

    //atrast vietas kur taisne t krusto k�du trijst�ra malu

    double S=0.0, S1 = 0.0, S2 = 0.0;

    S = triangleSize(dist(A,B), dist(B,C), dist(C,A));

    punkts kA,kB,kC;

    punkts P,Q;//shie buus kurus izmantos re�inot

    int skaits = 0;
    //1. uzzin�t punktus kuros tiek trijsturis saskelts!!
    if (interact(a,t))
    {
        kA = getInteraction(a,t);
        skaits++;
        cout<<"A:("<<kA.x<<";"<<kA.y<<")\n";
    }
    if (interact(b,t))
    {
        kB = getInteraction(b,t);
        skaits++;
        cout<<"B:("<<kB.x<<";"<<kB.y<<")\n";
    }
    if (interact(c,t))
    {
        kC = getInteraction(c,t);
        skaits++;
        cout<<"C:("<<kC.x<<";"<<kC.y<<")\n";
    }

    if (skaits==3)
    {
        //noz�me ka linija iet caur vienu virsotni
        if (kA.x == kB.x && kA.y == kB.y)
        {
            P=kA;
            Q=kC;
        }
        else
        {
            P=kA;
            Q=kB;
        }

        //linija sadal�s trijst�ri 2 trijst�ros
        double s1,s2,s3; //laukums visiem trijst�ra punktiem attiec�ba pret l�niju;
        s1 = triangleSize(dist(A,P), dist(P,Q), dist(Q,A));
        s2 = triangleSize(dist(B,P), dist(P,Q), dist(Q,B));
        s3 = triangleSize(dist(C,P), dist(P,Q), dist(Q,C));

        S1 = max(s1,max(s2,s3));

        S2 = S - S1;

        cout<<"Attieciba: "<<S1<<"/"<<S2<<"="<<S1/S2<<endl;
    }
    else if (skaits==2)
    {
        //linija neiet caur nevienu trijst�ra punktu

        if (interact(a,t) && interact(c,t))
            S1 = triangleSize(dist(A,kA), dist(kA,kC), dist(kC,A));

        if (interact(a,t) && interact(b,t))
            S1 = triangleSize(dist(kA,B), dist(B,kB), dist(kB,kA));

        if (interact(b,t) && interact(c,t))
            S1 = triangleSize(dist(kB,C), dist(C,kC), dist(kC,kB));

        S2 = S - S1;

        cout<<"Attieciba: "<<S1<<"/"<<S2<<"="<<S1/S2<<endl;
    }
    else
    {
        //linija ne���rso trijst�ri
    }

    system("pause");
    return 0;
}

//ieg�t l�nijas vien�dojumu (ax+by=c) p�c dieviem punktiem
line createLineByPoint(punkts A, punkts B)
{
    line resultLine;

    double d = A.x*B.y - B.x*A.y;
    double d1 = B.y - A.y;
    double d2 = A.x - B.x;

    if (d != 0)
    {
        resultLine.a = d1;
        resultLine.b = d2;
        resultLine.c = d;
    }

    return resultLine;
}

bool interact(line v1, line v2)
{
    //determinantas
    int d = v1.a * v2.b - v1.b * v2.a;

    //ja determinanta v�rt�ba ir 0 tad var neb�t neviena atrsiin�juma(paral�las taisnes) vai bezgala daudz atrisin�jumu(vien�das taisnes)
    if (d == 0) return false;

    return true;
}

//ieg�t kordin�tes kur divas taisnes krustoj�s, pirms lieto�anas j�p�rbauda vai taisnes krustoj�s
punkts getInteraction(line v1, line v2)
{
    punkts a;
    double d = v1.a * v2.b - v1.b * v2.a;
    double d2 = v1.c * v2.b - v1.b * v2.c;
    double d3 = v1.a * v2.c -  v1.c * v2.a;

    a.x = d2 / d;
    a.y = d3 / d;

    return a;
}

//att�lums starp diviem punktiem
double dist(punkts A, punkts B)
{
    return  (double)sqrt(pow(B.x-A.x,2.0)+pow(B.y-B.x,2.0));
}

//tijst�ra laukuma apre�in��ana
double triangleSize(double a, double b, double c)
{
    double p = (a+b+c)/2;

    return (double)sqrt(p * (p-a) * (p-b) * (p-c));
}
