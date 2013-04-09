/*******************************************
A19. Doti n veseli skaitļi. Atrast otro mazāko no šiem skaitļiem.
Programma izveidota: 2010/10/16
*******************************************/
#include <iostream>
using namespace std;

int main()
{
    int ok;
    do
    {
        int m1, m2, x, n, s;
        cout << "Ievadi veertiibu skaitu! " << endl;
        cin >> s;//skaitļu skaits

        if(s < 2) //ir jābūt vismaz 2 skaitļiem
            cout << "Ievadiits nekorekts veertiibu skaits! " << endl;
        else
        {
            cout << "Ievadi veertiibas! " << endl;
            cin >> m1 >> m2; //pieprasam pirmos 2 skaitļus

            if(m1 > m2) //samainam vietām ja 1. lielāks par 2.
            {
                n = m1;
                m1 = m2;
                m2 = n;
            }

            for(int i = 2; i < s; i++) //i sakumvērtība ir 2, jo pirmie divi skaitļi jau ir ievadīti.
            {
                cin >> x; //ievada nakošo skaitli

                if(m2 > x)//ja tika ievadīts skaitlis kas mazāks par 2. mazāko
                {
                    m2 = x;//2. mazākais tagad ir jaunais

                    if(m1 > m2) //saimainam vietām ja 1. mazākais ir lielāks par 2. mazāko
                    {
                        n = m1;
                        m1 = m2;
                        m2 = n;
                    }
                }
            }

            cout << "Otraa mazaakaa veertiiba ir " << m2 << endl;//izvads
        }
        cout << " Vai turpinaat (1) vai beigt (0)? " << endl;
        cin >> ok;
    }
    while(ok == 1);

    return 0;
}

/* TESTA PIEMĒRI

Ievads		          Programmas vēlamā reakcija      Rezultāts
2   2; 4              4                                +
4   6; 5; 9; 1        5                                +
1   -                 Ievadiits nekorekts             Izdod paziņojumu
                      veertiibu skaits!               "Nekorekts skaits"

*/
