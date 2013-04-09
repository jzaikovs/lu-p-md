/*
Izveidot programmu valodā C++, kas ļauj izveidot vienvirziena saistīto
sarakstu (izmantojot dinamiskās datu struktūras), kurā glabājas veseli
skaitļi. Jābūt  paredzētai iespējai sarakstu papildināt ar jaunu
elementu (pielikt elementu saraksta galā), izdrukāt sarakstu, iznīcināt
sarakstu. Bez tam jāuzraksta funkcija, kura aprakstīta zemāk. Iznīcinot
saraksta elementus, korekti jāatbrīvo izdalītā atmiņa. Galvenajā programmā:
a) jābūt iespējai ievadīt saraksta elementus (izveidot patvaļīgu
sarakstu),
b) jāpielieto uzrakstītā funkcija sarakstam,
c) jāizdrukā saraksts pēc funkcijas darbības.
d) beigās jāiznīcina saraksts (lietojot delete).
Citas prasības sk. Laboratorijas darbu noteikumos.

G10. Uzrakstīt funkciju, kas izmet no saraksta tā otro mazāko elementu,
ja tāds eksistē.

*/

#include <iostream>
#include <string>
using namespace std;

//Saistītais saraksts
class SaistitaisSaraksts
{
    struct elements
    {
        int vertiba;
        elements * nakosais;
    };

    elements * sakums, * beigas;

public:

    SaistitaisSaraksts()//konstruktors
    {
        sakums = NULL;
        beigas = NULL;
    }

    ~SaistitaisSaraksts();//destruktors

    void Pievienot( int vertiba );
    void DzestOtroMazako();
    void Print();
};

SaistitaisSaraksts::~SaistitaisSaraksts()//destruktors
{
    while( sakums != NULL )//iznicinam pirmo elementu un savienojam sakumu ar 2. elementu atkarto kameer vairs nav nakošā elementa
    {
        elements *nakosais = sakums->nakosais;
        delete sakums;
        sakums = nakosais;
    }

    cout<<"Saistitais saraksts izdzeests!\n";
};

void SaistitaisSaraksts::Pievienot(int vertiba)//pievienot elementus
{
    elements *p = new elements();//izveido jaunu elementu
    p->vertiba = vertiba;
    p->nakosais = NULL;

    if (sakums == NULL)//ja nav elementu
        sakums = p;	//saakumu noraada uz jauno elementu
    else
        beigas->nakosais = p;//aiz pedeja elementa pieliek jauno elementu

    beigas = p;//beigas noradiis uz jauno elementu kas tagad skaitās pēdejais
    cout<<"pievienots:"<<vertiba;
};

void SaistitaisSaraksts::DzestOtroMazako()//funkcija, kas parvieto elementu uz pēdejo
{
    if (sakums==NULL)
    {
        cout<<"Nav neviena elementa!\n";    //nav neviena elementa
        return;
    }

    if (sakums->nakosais==NULL)
    {
        cout<<"Nav 2. mazaka elementa, ir ievadita tikai 1 vertiba"<<endl;
        return;
    }


    elements *min = sakums, *prev_min = sakums;       //izveidot mainīgos, kuri glabās mazāko un elementu pirms mazākā
    elements *min2 = sakums->nakosais, *prev_min2 = sakums;  //mainīgais kurā glabājās 2. mazākais un elemets pirms tā

    if (sakums->vertiba > sakums->nakosais->vertiba)//ja otrā vērtība bijusi mazāka par pirmo samainam vietām
    {
        min = sakums->nakosais;
        min2 = sakums;
    }

    for (elements * i = sakums->nakosais; i->nakosais != NULL; i=i->nakosais)//cikls, kurā pārbaudīs visas vērtības
    {
        if (i->nakosais->vertiba < min->vertiba) //ja atrod kādu kas mazāks par jau esošo mazāko samainam un veco ieliek kā 2. mazāko
        {
            min2 = min;
            prev_min2 = prev_min;

            min = i->nakosais;
            prev_min = i;
        }
        else if (i->nakosais->vertiba < min2->vertiba) //ja atrod kādu kas ir mazāks par 2. mazāko un lielāks par mazāko aizvietojam!
        {
            min2 = i->nakosais;
            prev_min2 = i;
        }
    }

    if (min2 == sakums)//ja mazākais ir sākuma elements
        sakums = min2->nakosais;  //sākumu parvieto uz nakošo elementu
    else
    {
        if (min2 == beigas)beigas = prev_min2; // ja ir beigu elements tad beigas parvieto uz iepriekšējo elementu

        prev_min2->nakosais = min2->nakosais;//parliek saites nu ieprēkšāj uz aiznakamo elementu izslēdzot 2. mazaako!
    }

    delete min2; //džēš 2 mazāko
}

void SaistitaisSaraksts::Print()//izvadīt sarakstu
{
    elements *link = sakums;

    while(link != NULL)//atkartojas kamer elements eksistē
    {
        cout<<link->vertiba;//izvada elementa vērtību

        link = link -> nakosais;

        if (link != NULL) cout<<", ";
    }
};

int main()
{
    int ok;

    do
    {
        SaistitaisSaraksts * list = new SaistitaisSaraksts();//veidojam jaunu saistīto saraktu

        while (true)
        {
            string command;//esoša komanda

            cout<<"Ko dariit [add, dzest2mazako, print, delete]? :";
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
                list->Pievienot(i);
            }

            if (command == "dzest2mazako")
                list->DzestOtroMazako();//speciāla funkcija



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
