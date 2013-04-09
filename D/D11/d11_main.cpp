/*
D11. Izveidot klasi "Trīsstūris", kurā tiek glabāti trīs skaitļi - trīsstūra malu garumi.
Klasei izveidot šādas metodes:
(1) konstruktors, ar kuru tiek padotas sākotnējās vērtības,
(2) destruktors, kurš paziņo par objekta likvidēšanu,
(3) metode "Mainīt" ar 3 parametriem, kas izmaina malu garumu vērtības par attiecīgo daudzumu (nevis nomaina),
(4) metode "Drukāt", kas izdrukā uz ekrāna malu garumus,
(5) metode "Aprēķins", kas izdrukā trīsstūra mediānu garumus un noskaidro trīsstūra tipu: šaurleņķa, taisnleņķa vai platleņķa.
*/

#include <iostream>
#include "d11_triangle.h"
#include <string>

using namespace std;

int main()
{
    int ok;

    do
    {
        double a,b,c;

        cout<<"Trijstura malas?\n";
        cin>>a>>b>>c; //malu ievade

        //TODO:logic test of data

        double m  = max(a,max(b,c));
        double n = min(a, min(b,c));
        double k = a + b + c - m - n;

        //parbauda vai trijstūris ir iespējams

        if (n+k > m)
        {
            Triangle* triangle = new Triangle(a, b, c); //jauna trijstūra veidošana

            while(true)
            {
                string funkcija; //darbību izsaukšanai

                cout<<"Ko dariit dzest, mainit, drukat, rekinat? ";
                cin>>funkcija;

                if (funkcija =="dzest") break;

                if (funkcija == "drukat") triangle->Drukat();

                if (funkcija == "rekinat") triangle->Aprekins();

                if (funkcija == "mainit")
                {
                    cout<<"Par cik mainiit malas [a b c]?\n";

                    int m,n,k;

                    cint>>m>>n>>k;

                    triangle->Mainit(m,n,k);

                    //TODO: change parameters, logic test, implementation
                }

            }

            delete triangle;

        }
        else
        {
            cout<<"Neeksiste trijsturis ar shadaam malaam!!!\n";
        }
        cout << "Vai turpinat (1) vai beigt (0)? ";
        cin >> ok;
    }
    while (ok == 1);

    return 0;
}
