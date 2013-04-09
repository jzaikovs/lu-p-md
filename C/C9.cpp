#include <iostream>

using namespace std;

int abs(int a)
{
    if(a < 0)
        return a * -1;
    else
        return a;
}

int main()
{
    int ok;
    do
    {
        int x, x1, x2, z = 0, n, size;
        cout << "Ievadi jauno virknes garumu n!" << endl;
        cin >> n;
        if(n < 1)cout << "Ievadiiti nekorekti dati!" << endl;
        else
        {
            size = 2 * n;
            int  * N = new int[size];
            int * A = new int[n];
            int * B = new int[n];
            cout << "Ievadi vecaas sadalaamaas virknes elementus!" << endl;
            for(int i = 0; i < size; i++)
            {
                cin >> N[i];
            }

            while(size > 0)
            {
                int a = N[0];
                int b = N[1];
                x = abs(a - b);
                x2 = 1;

                for(int j = 2; j < size; j++)
                {
                    x1 = abs(N[0] - N[j]);
                    if(x > x1)
                    {
                        x = x1;
                        b = N[j];
                        x2 = j;
                    }
                }

                A[z] = a;
                B[z] = b;
                z++;
                for(int m = x2; m < size - 1; m++)
                {
                    N[m] = N[m+1];
                }
                size--;
                for(int p = 0; p < size - 1; p++)
                {
                    N[p] = N[p+1];
                }
                size--;
            }
            cout << "Pirmaa virkne:" << endl;
            for(int i = 0; i < z; i++)
            {
                cout << A[i] << ";";
            }
            cout <<endl<< "Otraa virkne:" << endl;
            for(int i = 0; i < z; i++)
            {
                cout << B[i] << ";";
            }

        }


        cout <<endl<< "Vai turpinaat(1) vai beigt(0)?" << endl;
        cin >> ok;
    }
    while(ok == 1);
    return 0;
}
