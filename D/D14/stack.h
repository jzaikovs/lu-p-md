
const int SIZE = 5;

class Stack
{
    int index;

    int m[SIZE];

public:
    Stack( void );
    ~Stack( void );
    void Push(int i );
    int Pop();
    int Top();
    int Count();
    bool IsFull();
    bool IsEmpty();

};
