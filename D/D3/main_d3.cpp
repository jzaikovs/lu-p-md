/*===  D3  =======================================
autors: @jzaikovs
izveidots: 12.12.2009

D3. Izveidot klasi "Četrstūris", kurā tiek glabāti četri skaitļi -
četrstūra malu garumi un vēl viens skaitlis - brīvi izvēlēts leņķis grādos (1..179).
Klasei izveidot šādas metodes:
(1) konstruktors, ar kuru tiek padotas sākotnējās vērtības,
(2) destruktors, kurš paziņo par objekta likvidēšanu,
(3) metode "Mainīt" ar 5 parametriem, kas izmaina malu garumu vērtības par attiecīgo daudzumu (nevis nomaina),
(4) metode "Drukāt", kas izdrukā malu garumus un lenķi,
(5) metode "Aprēķins", kas noskaidro un izdrukā četrstūra tipu: kvadrāts, taisnstūris, rombs, paralelograms vai cits.

*/

#include <iostream>
#include "cetrsturis_d3.h"

using namespace std;

int main()
{
    int ok;

    do
    {
        double a,b,c,d;
        int angle;

        cout<<"Ievadiet cetrstura parametrus - (a, b, c, d, lenkis):\n";
        cin>>a>>b>>c>>d>>angle; //parametru ievade

        if (angle < 1 || angle > 179)  //angle jābūt (1..179)
        {
            cout<<"\n--Tads lenkis nevar but!!!\n\n";
            ok = 1;
            continue;
        }

        if (a <= 0 || b <= 0 || c <= 0 || d <= 0) //izmēri navar būt negatīvi vai 0
        {
            cout<<"\n--Malu garumam jabuut naturaalam skaitlim!!!\n\n";
            ok = 1;
            continue;
        }

        Square* square = new Square(a, b, c, d, angle); //jauna četrstūra izveidošana


        char f; //funkcijas izsaukšanas simbosl

        do
        {
            cout<<"Ko dariit (i)zdzest, (m)ainit, (d)rukat, (a)prekinat? ";
            cin>>f;

            if (f == 'i') break;

            if (f == 'd') square->Drukat();

            if (f == 'a') square->Aprekins();

            if (f == 'm')
            {
                cout<<"Par cik mainiit parametrus (a, b, c, d, lenkis)?:\n";

                int angle2; //izmaiņas leņķim

                double a2, b2, c2, d2; //izmaiņas malām

                cin>>a2>>b2>>c2>>d2>>angle2;

                if (angle + angle2 < 1 || angle + angle2 > 179)//pēc izmaiņām leņķis nedrīks būt ārpus def. apg.
                {
                    cout<<"\n--Lenki nevar tik daudz izmainiit!!!\n\n";
                }
                else if (a + a2<=0 || b + a2 <= 0 || c + c2 <= 0 || d + d2 <= 0) //pēc izmaiņas kāda no malām būs mazāka vai vienāda ar 0
                {
                    cout<<"\n--Malas garums nevar tikt samazinats tik daudz!!!\n\n";
                }
                else
                {
                    square->Mainit(a2, b2, c2, d2, angle2);
                    cout<<"\n--Izmers veiksmiigi izmaniits\n\n";
                }
            }

        }
        while(f != 'i');

        delete square;

        cout << "Vai turpinat (1) vai beigt (0)? ";
        cin >> ok;
    }
    while (ok == 1);

    return 0;
}