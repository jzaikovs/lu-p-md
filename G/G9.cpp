/*
autors: @jzaikovs
izveidots: 16.02.2010

Izveidot programmu valodā C++, kas ļauj izveidot vienvirziena saistīto sarakstu (izmantojot dinamiskās datu struktūras), kurā glabājas veseli skaitļi.
Jābūt  paredzētai iespējai sarakstu papildināt ar jaunu elementu (pielikt elementu saraksta galā),
izdrukāt sarakstu, iznīcināt sarakstu. Bez tam jāuzraksta funkcija, kura aprakstīta zemāk. Iznīcinot saraksta elementus,
korekti jāatbrīvo izdalītā atmiņa.

Galvenajā programmā:
a) jābūt iespējai ievadīt saraksta elementus (izveidot patvaļīgu sarakstu),
b) jāpielieto uzrakstītā funkcija sarakstam,
c) jāizdrukā saraksts pēc funkcijas darbības.
d) beigās jāiznīcina saraksts (lietojot delete).

Citas prasības sk. Laboratorijas darbu noteikumos.

G9. Uzrakstīt funkciju, kas pārvieto saraksta n-to elementu uz saraksta beigām. Darbība jāveic, pārkabinot saites, nevis pārrakstot elementu vērtības.
*/

#include <iostream>
#include <string>
using namespace std;


//Saistītais saraksts
class LinkedList
{
    struct node
    {
        int number;
        node * next;
    };

    node * first, * last;
public:

    LinkedList()//konstruktors
    {
        first = NULL;
        last = first;
    }

    ~LinkedList();//destruktors

    void Add( int number );
    void PushBack( int index );
    void Print();
};

LinkedList::~LinkedList()//destruktors
{
    node *next;

    while( first != NULL )//iznicinam pirmo elementu un savienojam sakumu ar 2. elementu atkarto kameer vairs nav nakošā elementa
    {
        next = first->next;
        delete first;
        first = next;
    }

    cout<<"Saistitais saraksts izdzeests!\n";
};

void LinkedList::Add(int number)//pievienot elementus
{
    node *p = new node();//izveido jaunu elementu
    p->number = number;
    p->next = NULL;

    if (first == NULL)//ja nav elementu
        first = p;	//saakumu noraada uz jauno elementu
    else
        last->next = p;//aiz pedeja elementa pieliek jauno elementu

    last = p;//last noradiis uz jauno elementu kas tagad skaitās pēdejais
    cout<<"pievientos:"<<number;
};

void LinkedList::PushBack(int index)//funkcija, kas parvieto elementu uz pēdejo
{
    if (first==NULL)
    {
        cout<<"Nav neviena elementa!\n";    //nav neviena elementa
        return;
    }

    node *p = first, *prev=NULL, *next=first->next;

    for (int i = 0; i < index; i++)//skaitam elementus liidz noraditajam(neieskaitot)
    {
        prev = p;//glabjaas
        p = p->next;//glabājaas nakošais elements aiz i-elementa

        if (p != NULL)
            next = p->next;//glabajas aiznakoshais elements aiz i-elementa, ja p elements eksistee
        else
        {
            cout<<"Nav taada elementa!\n";
            return;
        }
    }

    if (next != NULL)//ja next pastaav tad parvietojam p uz beigaam aiz last elementa
    {
        p->next = NULL;//taka p būs pedejais viņam neseko nekas;

        if (prev == NULL)
            first = next;
        else
            prev->next = next;//savienu elementu kas atrodas pirms p ar elementu pēc p;

        last->next = p;//novieto beigās p;

        last = p;//pēdejā elementa adrese;

        this->Print();
    }
    else
    {
        cout<<"Elements jau ir peedejais!\n";
    }
}

void LinkedList::Print()//izvadīt sarakstu
{
    node *link = first;

    while(link != NULL)//atkartojas kamer elements eksistē
    {
        cout<<link->number;//izvada elementa vērtību

        link = link->next;

        if (link!=NULL)cout<<", ";
    }
};

int main()
{
    int ok;

    do
    {
        LinkedList * list = new LinkedList();//veidojam jaunu saistīto saraktu

        while (true)
        {
            string command;//esoša komanda

            cout<<"Ko dariit [add, push, print, delete]? :";
            cin>>command;//ievad komandu

            if (command == "delete")
            {
                delete list;//izdzēš saistīto sarakstu
                break;
            }

            if (command == "add" || command == "push")
            {
                int i;

                cin>>i;

                if (command == "add")//pievienot skaitli i
                    list->Add(i);
                else if (i >= 0) //parbīdiit i-elementu
                    list->PushBack(i);
                else cout<<"Indeksu noraada ar naturaaliem skaitljiem!\n";
            }

            if (command == "print")
                list->Print();//izvadiīt skaitli

            cout<<endl;
        }


        cout << "\n Vai turpinat (1) vai beigt (0)?\n" << endl;
        cin >> ok;
    }
    while (ok == 1);



    return 0;
}

/*
TESTA PIEMĒRI

add 1; add 2; print									   1, 2
add -10; add 5; add 6; add -1; push 4				   nav tāda elementa
add -10; add 5; add 6; add -1; push 3				   elements jau ir pedejais
add 1; add 2; add 3; push 0                            2, 3, 1
add 1; add 2; add 3; push 1                            1, 3, 2
push 1                                                 nav neviena elementa
add 2; add 3; add 1; push -1						   indeksu jānorāda ar naturālu skaitli
add 1; add 2; delete								   saistītais saraksts ir izdzēsts


*/
