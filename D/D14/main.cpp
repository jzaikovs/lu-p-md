/***********************************************
D14.
Izveidot klasi "Skaitļu steks", kurā glabājas masīvs ar skaitliskām
vērtībām (int) garumā 5 un steka elementu skaits. Klasei izveidot šādas
metodes:
         (1) konstruktors,
         (2) destruktors, kurš paziņo par objekta likvidēšanu un likvidēto
         elementu skaitu (ja likvidēšanas brīdī steks nav tukšs),
         (3) metode "Push", kas pievieno stekam elementu, ja tas nav pilns,
         (4) metode "Pop", kas izņem no steka augšējo elementu un atgriež tā vērtību,
         (5) metode "Count", kas atgriež elementu skaitu stekā,
         (6) metode "Top", kas atgriež augšējā elementa vērtību,
         (7) metode "IsEmpty", kas noskaidro, vai steks ir tukšs,
         (8) metode "IsFull", kas noskaidro, vai steks ir pilns.
Pirms uzdevuma veikšanas precīzi noskaidrot, ko nozīmē jēdziens steks (stack).

uzdevums izpildiits: 25.01.2010.
************************************************/


#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

int main ()

{
    int a;
    do
    {
        Stack stack();

        string komanda;

        do
        {

            cout << "kaadu komandu izpildiit? (push, pop, top, count, isEmpty, isFull, end) \n";
            cin >> komanda;

            if (komanda == "push")
            {
                int i;
                cin >> i;
                stack->Push(i);
            }

            if (komanda == "pop") cout << stack->Pop() << endl;

            if (komanda == "top") cout << stack->Top() << endl;

            if (komanda == "count") cout << stack->Count () << endl;

            if (komanda == "isEmpty") cout << stack->IsEmpty () << endl;

            if (komanda == "isFull") cout << stack->IsFull () << endl;

        }
        while ( komanda != "end" );

        delete stack;

        cout << "vai atkaartot? jaa-1, nee-0"<<endl;
        cin >> a;
    }
    while ( a == 1 );

    return 0;
}


/*****
Testa piemeeri

ievada : push 1  push 22  push 13  pop     count    top     isFull     isEmpty     end
izvada :                               13        2      22         0           0        Steks tiek dzeests!
                                                                                        2 elementi tikai izdeesti
ievada : end
izvada :     Steks tiek dzeests!

ievada : top    pop                   count     isEmpty                   isFull
izvada :     0      Steks ir tuksh!         0           1 (jo 1 ir true)         0 (jo 0 ir false)
                    0 (jo nav veertiibas ko atgiezt)

****/

