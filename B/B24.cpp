/******************************************************************************
B24. Dota veselu skaitļu virkne a(1), a(2),  , a(n). Ja dotajā virknē nav neviena pāra skaitļa,
kas sekotu pēc nepāra skaitļa, tad izdrukāt visus virknes negatīvos skaitļus, citādi – pozitīvos.
Abos gadījumos skaitīi jāizdrukā apgrieztā secībā nekā dots.

Pogramma izveidota: 07/11/2010

*******************************************************************************/

#include <iostream>
using namespace std;

int main()
{
    int ok;
    do
    {
        int n = 0;
        cout << "Ievadi skaitlju skaitu" << endl;
        cin >> n;

        //skaitļju masīvs
        int * arr = new int[n];

        cout << "Ievadiet veselu skaitlu virkni : " << endl;
        for(int i = 0; i < n; i++)
        {
            cin >> arr[i];
        } //ievades beigas

        bool hasPair = false;

        for(int i = 0; i < n - 1; i++)
        {
            if(arr[i] % 2 == 1 && arr[i+1] % 2 == 0)
            {
                hasPair = true;
            }
        } //nosaciijuma parbaude

        for(int i = n - 1; i >= 0; i--)
        {
            if(hasPair)
            {
                if(arr[i] < 0)
                    cout << arr[i] << " ";
            }
            else
            {
                if(arr[i] > 0)
                    cout << arr[i] << " ";
            }
        }

        cout << "Vai turpinat (1) vai beigt (0)?" << endl;
        cin >> ok;
    }
    while(ok == 1);

    return 0;
}
