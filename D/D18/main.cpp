/*
Programma izveidota : 13/01/2010

D18. Izveidot klasi "Skola", kura tiek glabaati 12 skaitli - skolas klashu skoleenu skaits.
Klasei izveidot šaadas metodes: (1) konstruktors, ar kuru tiek padotas saakotneejaas veertiibas, (2) destruktors, kursh pazinjo par objekta likvideeshanu,
(3) metode "Mainiit" ar diviem parametriem - klases numurs un jaunais skoleenu skaits, (4) metode "Drukaat",
kas izdrukaa skoleenu skaitu pa klaseem un kopeejo skoleenu skaitu, (5) metode "Apreekins", kas izdrukaa skolas kopeejo skoleenu skaitu,
videejo skoleenu skaitu klasee, maksimaalo un minimaalo skoleenu skaitu klasee.
*/

#include <iostream>
#include "program.cpp"
using namespace std;

int main ()
{
    int izvelne, ok, skolSkaits, nr;
    Skola sk;
    for (int i=0; i<12; i++)
    {
        cout << "Skoleenu skaits " << i+1 << ". klasee: ";
        cin >> skolSkaits;        // ievada skoleenu skaitu katraa klasee
        sk.mainit(i+1,skolSkaits); // izmaina skoleenu skaitu kaadaa klasee
    }
    do
    {
        cout << "IZVELNE: " << endl << endl;
        cout << "(1) - Drukat" << endl;
        cout << "(2) - Aprekins" << endl;
        cout << "(3) - Mainit" << endl << endl;
        cout << "Izvele: ";
        cin >> izvelne;
        if (izvelne == 1) sk.drukat();
        else if (izvelne == 2) sk.aprekins();
        else if (izvelne == 3)
        {
            cout << "Raksturlielumu mainiisana: " << endl;
            cout << "Klases numurs: ";
            cin >> nr;                // ievadam kuraa klasee gribam mainiit skoleenu skaitu
            cout << "Jaunais skoleenu skaits: ";
            cin >> skolSkaits;        // ievadam jauno skoleenu skaitu
            sk.mainit(nr, skolSkaits);   // izmaina skoleenu skaitu kaadaa klasee
        }
        cout << "Vai turpinat (1) vai beigt (0) ?: "; // tiek piedaavaata atkaartoshana
        cin >> ok;
    }
    while (ok == 1);
    return 0;
}
