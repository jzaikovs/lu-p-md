/*
C14
*/

#include <iostream>
using namespace std;

int LKD(int a, int b)
{
    if (b == 0)
        return a;
    else
        return LKD(b, a%b);
}

int main()
{
    int n;

    cin>>n;

    int m[n];

    for (int i = 0; i<n; i++)
    {
        int a;
        cin>>a;
        if (a>0)
            m[i]=a;
        else
            cout<<"ievadiet tikai naturalus skaitljus\n";
    }

    bool p = true

             for (int i=0; i< n-1; i++)
    {
        for (int j =i+1; j<n; j++)
        {
            if (LKD(m[j],m[i])==1)
            {
                if (p)cout<<"pariishi:\n";

                cout<<<<m[i]<<" - "<<m[j]<<endl;
                p=false;
            }

        }
    }

    if (p)cout<<"nav savstarpeju pirmsaitlju!\n";

    system("pause");

    return 0;
}