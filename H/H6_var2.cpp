/*
=== H6 =======================================
Izveidot programmu valodā C++. Prasības sk. Laboratorijas darbu noteikumos.

H6. Uzrakstīt programmu, kas ļauj izveidot un labot bināru failu, kura
ieraksta struktūra ir sekojoša:
vārds – atslēga (30 simboli),
vārds – vērtība (30 simboli),
ieraksta statuss (0 vai 1).

Programmai katrs jauns ieraksts jāieliek faila beigās.

Jāparedz iespēja
(1) izmest faila komponenti (loģiski atzīmējot kā izmestu),
(2) izdrukāt faila esošās komponentes uz ekrāna,
(3) izmest loģiski izmestas komponentes fiziski.


datums: 31.05.2010.

*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Ieraksts
{
    char atslega[30];
    char vertiba[30];
    bool status;

public:
    Ieraksts(string atslega = "", string vertiba = "", bool status = false)
    {
        for (int i = 0; i < 30; i++)
        {
            this->atslega[i]='\0';
            this->vertiba[i]='\0';

            if (i < atslega.length())
                this->atslega[i] = atslega[i];

            if (i<vertiba.length())
                this->vertiba[i] = vertiba[i];
        }

        this->status = status;
    }
};

class Fails
{
    fstream file;//binārais fails

    int count()//funkcija kas saskaita cik vārdu ir failā
    {
        file.seekg(0, ios::end);//novieto pozīciju beigās

        int n = (int)(file.tellg() / sizeof(Ieraksts)); //pajautaa, kur atrodas seekg poziicija

        file.seekg(0);

        return n;
    };

public:
    Fails();//konstruktors
    ~Fails();//dekonstruktors

    void Pievienot(Ieraksts a);
    void Drukat();
    void DzestLogiski(int index);
    void DzestFiziski();
};

int main()
{
    Fails * fails = new Fails();

    cout<<"komandas: pievienot, drukat, dzest(i), fdzest un beigt"<<endl;

    string command = "";

    for (cin >> command; command != "beigt"; cin >> command)
    {
        if (command == "pievienot")
        {
            cout<<"atslega:";
            string key;
            cin>>key;
            cout<<"vertiba:";
            string value;
            cin>>value;

            Ieraksts a(key,value);

            fails->Pievienot(a);
        }

        if (command == "drukat")
        {
            fails->Drukat();
        }

        if (command == "dzest")
        {
            int i = 0;
            cin>>i;
            fails->DzestLogiski(i);
        }

        if (command == "fdzest")
        {
            fails->DzestFiziski();
        }
    }

    delete fails;
};

Fails::Fails()
{
    file.open("f.bin", ios::in | ios::out | ios::binary | ios:: trunc| ios::ate);

    if (file.is_open())
        cout<<"--fails atverts\n";
    else
        cout<<"--kluuda atverot failu\n";
};

Fails::~Fails()
{
    file.close();
};

void Fails::Pievienot(Ieraksts a)
{
    file.seekp(0, ios::end);
    file.write((char*)&a, sizeof(Ieraksts));
};

void Fails::Drukat()
{
    file.seekg(0);

    int i = 0;
    int size = count();

    while(i < size && file.good())
    {
        Ieraksts a;
        file.read((char*)&a, sizeof(Ieraksts));

        cout<<a.atslega<<" | "<<a.vertiba<<" | "<<a.status<<endl;

        i++;
    }

    file.clear();
    file.seekg(0);
};

void Fails::DzestLogiski(int index)
{
    file.seekp( index * sizeof(Ieraksts) + 60 );
    bool dzests = true;
    file.write( (char*)&dzests, sizeof(bool));
};

void Fails::DzestFiziski()
{
    int n = count();

    Ieraksts * temp = new Ieraksts[n]; //

    file.seekg(0);//lasīšanas pozicija uz 0

    int idx = 0;

    do
    {
        Ieraksts a;
        file.read((char*)&a, sizeof(Ieraksts));

        if (!a.status)
        {
            temp[idx] = a;
            idx++;
        }
    }
    while(file.good());

    file.close();

    file.open("f.bin", ios::in | ios::out | ios::binary | ios::trunc | ios::ate);

    file.write((char*)&temp[0], sizeof(Ieraksts) * (idx-1));

    delete temp;
};


/**
testa piemeers:
pievienot k1 k1
pievienot k6 k6
pievienot k4 k4

drukat // izdrukaa visus pievienotos, atdalot ar |

dzest 1 // izdzeesh logjiski pirmo ierakstu, skaitishana saakas no 0, logjiski dzeest noziimee, samainiit status uz frue, true apziimee, ka ir dzests logjiski

drukat //otraa rindinja izdrukaajas ar statusu 1

fdzest // tiek dzeests no faila fiziski attieciigais ieraksts

drukat // izdrukaa tikai pirmo un peedeejo ierakstu

pievienot k2 k2

drukat // izdrukaa ar jauno pievienoto ierakstu

dzest 3 // tiek izveidots jauns ieraksts, bet pilniigi tuksh un atziimeets, kaa logjiski izdzeests

fdzest // tika izdzesti abi ieraksti, kas logjiski tika pirms tam atzimeti kaa izdzeesti

drukat // izdrukaa tikai divus ierakstus, kas nebija atziimeeti logjiski izdzeesti
**/