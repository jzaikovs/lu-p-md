/*******************************************

A4. Doti divi naturāli skaitļi. Atrast abu skaitļu ciparu summu starpību. Skaitļu dalīšana ciparos jāveic skaitliski.

Izveidot programmu valodā C++. Ievadot loģiski nepareizus datus, programmai jāizdod atbilstošs paziņojums.
Jābūt iespējai programmu izpildīt atkārtoti. Atrādot programmu, jāatrāda
  a) programmas teksts,
  b) testa piemēri,
  c) programma darbībā.

Programma izveidota: 2010/10/12
*******************************************/

#include <iostream>
using namespace std;
int main()
{
    int ok;
    do
    {
        int a, b;

        cout << " Ievadiet naturaalus skaitllus A un B: " << endl;
        cin >> a >> b;

        if(a <= 0 || b <= 0)
        {
            cout << "Nav ievadiits naturaals skaitlis!" << endl;
        }
        else
        {
            int sum = 0;
            while(a > 0 || b > 0)
            {
                sum += a % 10 - b % 10;
                a /= 10;
                b /= 10;
            }
            cout << "Skaitlju A un B starpiiba ir " << sum << endl;
        }
        cout << " Vai turpināt (1) vai beigt (0)?" << endl;
        cin >> ok;
    }
    while(ok == 1);

    return 0;
}
