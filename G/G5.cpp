/*
Izveidot programmu valodā C++, kas ļauj izveidot vienvirziena saistīto sarakstu
(izmantojot dinamiskās datu struktūras), kurā glabājas veseli skaitļi.
Jābūt  paredzētai iespējai sarakstu papildināt ar jaunu elementu (pielikt elementu saraksta galā),
izdrukāt sarakstu, iznīcināt sarakstu. Bez tam jāuzraksta funkcija, kura aprakstīta zemāk.
Iznīcinot saraksta elementus, korekti jāatbrīvo izdalītā atmiņa. Galvenajā programmā:
a) jābūt iespējai ievadīt saraksta elementus (izveidot patvaļīgu sarakstu),
b) jāpielieto uzrakstītā funkcija sarakstam,
c) jāizdrukā saraksts pēc funkcijas darbības.
d) beigās jāiznīcina saraksts (lietojot delete).
Citas prasības sk. Laboratorijas darbu noteikumos.
G5. Uzrakstīt funkciju, kas no saraksta izmet tos elementus, tieši aiz kuriem sarakstā seko elementi, kuru vērtība ir pāra skaitlis.
*/

#include <iostream>
#include <string>
using namespace std;

class LinkedList
{
    struct elem
    {
        int num;
        elem * next;
    };

    elem * first, * last;
public:

    LinkedList()//konstruktors
    {
        first = NULL;
        last = first;
    };

    ~LinkedList()
    {
        elem *next;

        while( first != NULL )//iznicinam pirmo elementu un savienojam sakumu ar 2. elementu atkarto kameer vairs nav nakošā elementa
        {
            next = first->next;
            delete first;
            first = next;
        }

        cout<<"Saistitais saraksts izdzeests!\n";
    };//destruktors

    void Add( int number )
    {
        elem *p = new elem();//izveido jaunu elementu
        p->num = number;
        p->next = NULL;

        if (first == NULL)//ja nav elementu
            first = p;	//saakumu noraada uz jauno elementu
        else
            last->next = p;//aiz pedeja elementa pieliek jauno elementu

        last = p;//last noradiis uz jauno elementu kas tagad skaitās pēdejais
        cout<<"pievientos:"<<number;
    };

    void Clean()
    {
        for (elem *i = first; i!=last; i=i->next)
        {
            if (i->next->num % 2 == 0)
            {
                elem*temp = i->next->next;
                delete i->next;
                i->next = temp;
            }
        }
    };

    void Print()
    {
        elem *link = first;

        while(link != NULL)//atkartojas kamer elements eksistē
        {
            cout<<link->num;//izvada elementa vērtību

            link = link->next;

            if (link!=NULL)cout<<", ";
        }
    };
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

            cout<<"Ko dariit [add, clean, print, delete]? :";
            cin>>command;//ievad komandu

            if (command == "delete")
            {
                delete list;//izdzēš saistīto sarakstu
                break;
            }

            if (command == "add")
            {
                int i;

                cin>>i;

                list->Add(i);
            }

            if (command == "clean")
            {
                list->Clean();
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
