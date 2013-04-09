/*
autors: @jzaikovs
izveidots: 20.09.2012

A2.
Dots naturāls skaitlis n.
Noskaidrot, vai šī skaitļa pirmais cipars ir vienāds ar pēdējo ciparu (piemēram, 18961).
Skaitļa dalīšana ciparos jāveic skaitliski.

*/

#include <iostream>

using namespace std;

bool is_first_equal_last(int number)
{
    if (number< 10)
        return false;

    int last = number % 10;

    while (number > 10)
    {
        number /= 10;
    }

    return last == number;
}

int main()
{
    int input[] = {123,456,1,99, 909, 54445, 1234321};

    for(int i = 0; i < sizeof(input)/sizeof(int); i++)
    {
        if (is_first_equal_last(input[i]))
            cout<<input[i]<<" TRUE "<<endl;
        else
            cout<<input[i]<<" FALSE "<<endl;
    }

    int key = 0;
    cin>>key;
    return 0;
}