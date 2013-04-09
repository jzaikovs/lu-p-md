#include <iostream>
#include "stack.h"

using namespace std;

Stack::Stack( void )
{
    index=0;
};

Stack::~Stack( void )
{
    cout<<"Steks tiek dzeests!\n";

    if ( !IsEmpty() )
    {
        cout<<Count()<<" elementi tika izdzeesti.\n";
    }

};

void Stack::Push( int i )
{
    if ( index == SIZE )
    {
        cout<<"Steks ir pilns! sorry!\n";
    }
    else
    {
        m[index++]=i;
    }
};

int Stack::Top()
{
    if ( !IsEmpty() )
        return m[index-1];
    return 0;

};

int Stack::Pop()
{
    if ( IsEmpty() )
    {
        cout<<"steks ir tuksh!!!\n";
    }
    else
    {
        return  m[--index];
    }


    return 0;
};

int Stack::Count()
{
    return index;
};

bool Stack::IsFull()
{
    if ( index == SIZE )
        return true;

    return false;
};

bool Stack::IsEmpty()
{
    if ( index ==  0 )
        return true;

    return false;
};
