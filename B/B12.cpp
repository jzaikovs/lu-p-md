/*******************************************
B12.
Dots naturals skaitlis n un veseli skaitli a1, a2, ... , an (n<100).
Noteikt, vai starp siem skaitliem ir tadi, kas vienadi ar citu divu dalijumu.
Izdrukat sos skaitlus formata a(k)=a(i)/a(j)

Programma izveidota: 2009/11/01
*******************************************/

#include <iostream>
using namespace std;

int main()
{
    int ok;

    do
    {
        int n;

        cout<<"Ievadiet, cik skaitlju buus (vairak par 0 un mazaak par 100): ";
        cin>>n;

        if(n > 0 && n < 100) //vai n pieder uzdevuma noteiktajam apgabalam
        {
            int a[n];

            cout<<"Ievadiet veselos skaitljus: "<<endl;

            //pieskiram vertibas masiva elementiem
            for(int i = 0; i < n; i++)
            {
                int m;
                cin>>m;

                a[i] = m;
            }

            int d=0;

            // cikli, kuros tiek mekleetas nepiecieshamaas veertiibas, lai nosacijums izpildiitos
            for(int i=0; i<n; i++)
            {
                for(int k=0; k<n; k++)
                {
                    for(int j=k+1; j<n; j++)
                    {
                        //parbaudam vai a(i)/a(j)=a(k) un a(i)/a(j) atlikums ir 0 un paarbaudam vai netiek izmantoti vieni un tie pasi masiva elementi
                        if(a[j]!=0 && a[k]==a[i]/a[j] && a[i]%a[j]==0 && i!=j && i!=k && j!=k)
                        {
                            cout<<a[k]<<"="<<a[i]<<"/"<<a[j]<<endl; // izvada rezultaatu formataa a(k)=a(i)/a(j)

                            d++;  // veic darbibu uzskaiti
                        }
                    }
                }
            }

            //ja netika atrasta neviena darbiba taatad taadu dalijumu nav!
            if (d==0) cout<< "Daliijumu nav! "<<endl;
        }
        else
        {
            cout<<"Skaitlu skaits nepieder definicijas apgabalam"<<endl;
        }

        cout << "Vai turpinat (1) vai beigt (0)?"<< endl;
        cin >> ok;
    }
    while (ok == 1);

    return 0;
}



//       testa piemeeri
// nr.    Naturaalais sk.     Veselie sk.           Rezultaats
//  1.    111, -1             -                     programma pazinjo, ka skaitlis nepieder DA 1<=n<100, atljauj atkaartot darbiibas
//  2.    2                   4, 2                  daliijuma nav, jo no 2 sk. nevar buut dalijums
//  3.    6                   1, 1, 1, 1, 1, 1      pazinjo,ka daliijumu nav, jo skaitlji ir vienaadi
//  4.    4                   0, 0, 0, 0            daliijumu nav, ar 0 daliit nevar
//  5.    4                   -2, -4, -3, -16       daliijumu nav
//  6.    6                   1, 2, 3, 5, 7, 11     daliijumu nav
//  7.    6                   2, -4, 3, -12, 6, 4   2=6/3
//                                                  -4=-12/3
//                                                  3=-12/-4
//                                                  3=6/2
//  8.    6                   0, 0, 12, 3, 4, 6     3=12/4
//                                                  4=12/3
