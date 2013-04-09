/*******************************************
autors: @jzaikovs
izveidots: 31.10.2009

B1. Dots naturāls skaitlis n.
Noskaidrot, vai doto skaitli var izteikt kā trīs naturālu skaitļu kvadrātu summu.
Izdrukāt visus  šādus naturālu skaitļu trijniekus.

*******************************************/

#include <iostream>
#include <math.h>

using namespace std;

void solve(int n)
{
    //ejam cauri viesiem funkcijai piederoshiem x
    //x nebūs lielāks par kvadrātsakni no n
    for (int x = 1; x <=  (int)sqrt((double)n); x++)
    {
        //ejam cauri viesiem funkijai piederošiem y, ja ir zināms x
        //y*y <= n-1-x*x, jo x*x+y*y <= n-1;
        for (int y = 1; y <= (int)sqrt((float)n - x*x); y++)
        {
            //z*z == n-x*x-y*y, jo x*x + y*y + z*z == n;
            int z  = (int)sqrt((double)n-x*x-y*y);

            //parbaudam vai saknes apmierina vienādojumu
            if (x * x + y * y + z * z == n)
            {
                cout<<x<<" "<<y<<" "<<z<<endl;

                return;
            }
        }
    }

    cout<<"Sim skaitlim nav tadu skaitlju!\n";
}

int main()
{
    int ok;

    do
    {
        int n;

        cin>>n;

        if (n>0)
        {
            //meklējam atrisinājumu
            solve(n);
        }
        else
        {
            cout<<"Nav naturals!\n";
        }

        cout << "Vai turpinat (1) vai beigt (0)?" << endl;
        cin >> ok;
    }
    while (ok==1);

    return 0;
}

