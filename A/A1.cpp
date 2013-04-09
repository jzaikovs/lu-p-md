#include <iostream>

using namespace std;

int reverse(int i)
{
    int rez = 0;

    while(i > 0)
    {
        rez = rez * 10 + i % 10;
        i/=10;
    }

    return rez;
}

int main()
{
    cout<<reverse(120)<<endl;
    return 0;
}