/*
Izveidot programmu valodā C++, kas ļauj izveidot vienvirziena saistīto
sarakstu (izmantojot dinamiskās datu struktūras), kurā glabājas veseli
skaitļi. Jābūt  paredzētai iespējai sarakstu papildināt ar jaunu
elementu (pielikt elementu saraksta galā), izdrukāt sarakstu, iznīcināt
sarakstu. Bez tam jāuzraksta funkcija, kura aprakstīta zemāk. Iznīcinot
saraksta elementus, korekti jāatbrīvo izdalītā atmiņa. Galvenajā programmā:
  a) jābūt iespējai ievadīt saraksta elementus (izveidot patvaļīgu sarakstu),
  b) jāpielieto uzrakstītā funkcija sarakstam,
  c) jāizdrukā saraksts pēc funkcijas darbības.
  d) beigās jāiznīcina saraksts (lietojot delete).
Citas prasības sk. Laboratorijas darbu noteikumos.

G6. Uzrakstīt funkciju, kas saraksta n-tajam elementam piešķir tā
elementa vērtību, kura numurs glabājas n-tajā elementā.
*/

#include <iostream>
using namespace std;

//Saistīta saraksta (linked list) izveidošana.
struct element
{
    int number;//dati: vesels skaitlis
    element *next;//saite uz nākamo elementu
};

element *first=NULL, *last=NULL;// first-norade uz pirmo elementu, last-norade uz pēdējo elementu
int skaits=0; //saraksta elementu skaits

void add_element(int x)  //funkcija, kas sarakstu papildina ar jaunu elementu (pieliek elementu saraksta galā)
{
    skaits++;
    element * p = new element;//p-palīgnorāde, izveido objektu
    p->number = x; // aizpilda ar nolasīto vertību
    p->next = NULL; // norade uz nakošo - tukša!
    if (first == NULL)  // ja saraksts tukšs
    {
        first = last = p;// gan pirmais, gan pedejais norada uz jauno elementu
    }
    else     // ja saraksts nav tukšs
    {
        last->next = p;// pieliek galā beidzamajam
        last = last->next; // un jaunais kļūst par beidzamo
    }
};

//Saraksta izdruka.
void print_list()
{
    cout<<endl;
    for (element *p = first; p!=NULL; p=p->next)//drukā kamēr p nav NULL
    {
        cout << p->number <<endl;
    }
    cout<<endl;
};

void funkcija (int n)   //funkcija, kas saraksta n-tajam elementam piešķir tā
{
//elementa vērtību, kura numurs glabājas n-tajā elementā.
    int i=0;
    int num; //elementa numurs, kas glabājas n-tajā elementā
    element * ntais = first; //n-tais elements
    element * norad = first; //norādītais elements
    if(n<=(skaits-1)&&(n>=0))
    {
        while(i<n)
        {
            i++; //kad sakrīt n-tais ar i-to, beidz
            ntais=ntais->next;
        }
        num=ntais->number; // num = n-tā elementa cipars

        if(num<=(skaits-1)&&(num>=0))
        {
            i=0;
            while(i<num)
            {
                i++; //kad sakrīt n-tais ar i-to, beidz
                norad=norad->next;
            }
            ntais->number=norad->number; // n-tā elementa vērtībai piešķir jauno vērību
            cout<<"Funkcija izpildita!";
        }
        else
        {
            cout<<"Kluda:"<<n<<". elements satur neatbilstosu vertibu!"<<num;
        }
    }
    else
    {
        cout<<"Kluda: Ievaditais elementa ("<<n<<") numurs ir neatbilstoss!";
    }
}

//Saraksta iznicinašana.
void delete_list()
{
    element * p = first;
    while (p!=NULL)
    {
        first = first->next;
        delete p; //izdzēš kārtējo elementu
        p = first;
    }
}

//Sākas galvenā funkcija
int main()
{
    int y;
    char q; // komandas izsaukums

    cout<<"a => pielikt elementu saraksta gala\n";
    cout<<"b => n-tajam elementam pieskir ta elementa vertibu, kura numurs glabajas n-taja elementa\n";
    cout<<"c => izdrukat sarakstu\n";
    cout<<"d => iznicinat sarakstu/iziet no programmas\n";

    do
    {
        cout<<"\nIevadiet komandu:";
        cin >> q;

        while (q=='a')  //ievadot a
        {
            cout << "Ievadiet elementu:";
            cin>>y;
            add_element(y);//pievieno elementu
            cout << "Atkartot ievadi?[a]:";
            cin>>q;
        }

        if (q=='b')  //ievadot b
        {
            if(skaits>1)
            {
                cout << "Elementi numureti no 0 lidz" << (skaits-1) << "."<<endl;
                cout << "Ievadiet elementa numuru:";
                cin>>y;
                funkcija (y);
            } //izpilda funkciju

        }

        if (q=='c')  //ievadot c
        {
            print_list(); //izvada saraksta elementus
            cout<<"Elementu skaits:"<<skaits<<endl;
        }

        if (q=='d')
        {
            if(skaits>0)
            {
                delete_list(); //iznīcina saraksta elementus
                cout<<"Saraksts iznicinats!"<<endl;
            }
            system("pause");
        }
    }
    while (q!='d');

    return 0;
}
