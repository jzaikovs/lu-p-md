/*Izveidot programmu valodâ C++.  Prasības sk. Laboratorijas darbu noteikumos.
H8. Uzrakstīt programmu,
kas ïauj izveidot un papildinât binâru failu,
kura ieraksta struktûra ir sekojoða: gads (int), mçnesis (int), diena (int), nâkoðâ ieraksta numurs (int).
Programmai katrs jauns ieraksts jâieliek faila beigâs,
modelçjot saistîtu sarakstu, kura ieraksti sakârtoti datumu pieaugðanas secîbâ.
Paredzçt iespçju izdrukât faila ierakstus pçc fiziskâ un pçc loìiskâ sakârtojuma.*/


#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct ieraksts
{
    int gads, menesis, diena, nakosais;

public:
    int value()
    {
        return gads * 10000 + menesis * 100 + diena; // f-ja, kas vajadziiga lai vareetu saliidzinaat ierakstus
    };
};

class Fails
{
    fstream file;//binârais fails

    int N()//funkcija kas saskaita cik ierakstu ir failâ
    {
        file.seekg(0, ios::end);//novieto pozîciju beigâs

        return file.tellg() / sizeof(ieraksts); //pajautaa, kur atrodas seekg poziicija
    };

    void write(ieraksts * r, int idx)//raksta failâ vârdu idx pozîcija
    {
        file.seekp(idx * sizeof(ieraksts));	//ja idx lielâs par varad skaitu pozicija lçc uz beigâm
        file.write((char*)r, sizeof(ieraksts));
    };

    ieraksts * read(int index) //ielasa i-to vardu no saraksta
    {
        if (index >= N() || index < 0) return NULL; //ja idx lielak atgrieþ tukðu vârdu

        ieraksts * r = new ieraksts();
        file.seekg(index * sizeof(ieraksts));	//novietojam lasîðanas pozîciju
        file.read((char*)r,sizeof(ieraksts));
        return r;
    };

public:
    Fails()
    {
        //atver failu binârâ rakstîðanas mode
        file.open("f.bin", ios::in | ios::out | ios::binary | /*ios:: trunc|*/ ios::ate);

        if (file.is_open())
            cout<<"fails atverts\n";
        else
            cout<<"kluuda atverot failu\n";
    };

    ~Fails()
    {
        file.close();
    };

    void Pievienot(ieraksts a)
    {
        //pieveinojot ierakstu nakoðâ ieraksta nebûs -1 nozîmç nav ieraksta
        a.nakosais = -1;

        int n = N();//saskaitam cik ierakstu failâ

        //ja failâ ir kautkas ierakstîts
        if (n > 0)
        {
            //vērtības un pozīcijām iepriekēšējam un nakošajam elementam
            int prev_val = -1, prev_index = -1, next_val = -1, next_index = -1;


            //iterējam cauri visam sarakstam, lai atrastu vietu kur loģiski jāievieto jaunais elements
            for (int i = 0; i < n; i++)
            {
                //iegūstam ī-tā elementa vērtību
                int tmp = read(i)->value();


                if (tmp < a.value())//ja i vērtība mazaka par ieliekamo tad pārbaudam vai šis nevaretu būt iepriekšējais
                {
                    //ja nav ipriekšē vai i vertība ier lielāka par iepriekšējo i vērtību tad samainam
                    if (prev_val == -1 || tmp > prev_val)
                    {
                        prev_val = tmp;
                        prev_index = i;
                    }
                }
                else if (tmp > a.value()) //ja atrodam ierakstu kas nâk pçc ieraksta kas jaievietot
                {
                    //ja nākošais nav atrasts vai iepriekšējam
                    if (next_val == -1 || tmp < next_val)
                    {
                        next_val = tmp;
                        next_index = i;
                    }

                }
            }

            //uzliekam nakoðo elementu pievienotajam
            a.nakosais = next_index;
            if (prev_index!= -1)
            {
                //iepriekðçjais ir atrasts
                ieraksts * temp = read(prev_index);
                //uzliekam viòam nakoðos uz pievienoto
                temp->nakosais = n;// - 1;
                //saglabâjam
                write(temp,prev_index);
            }
        }

        //ierakstam faila beigâs pievienoto elementu
        write(&a,n);
    };

    void DrukatLogiski(int index = -1)
    {
        ieraksts * r = NULL;

        int n = N();

        //iterējam sarakstam cauri meklējām 1. elementu, jo neviens uz viņu nenorāda
        if (index == -1)
        {
            for (int i = 0; i < n; i++)
            {
                bool found = false;

                for (int j = 0; j < n; j++)
                {
                    ieraksts * a = read(j);

                    if (a->nakosais == i)
                    {
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    DrukatLogiski(i);
                    break;
                }
            }
        }
        else
        {
            ieraksts * a = read(index);
            cout<<a->gads<<" | "<<a->menesis<<" | "<<a->diena<<" | "<<a->nakosais<<endl;
            int next = a->nakosais;
            delete a;
            if (next >= 0)
            {
                DrukatLogiski(next);
            }

        }
    };

    void DrukatFiziski()
    {
        int n = N();

        for (int i = 0; i<n; i++)
        {
            ieraksts * a = read(i);

            cout<<a->gads<<" | "<<a->menesis<<" | "<<a->diena<<" | "<<a->nakosais<<endl;

            delete a;
        }
    };
};

int main()
{
    Fails * fails = new Fails();

    cout<<"komandas: pievienot, fdrukat, ldrukat, beigt"<<endl;

    string command = "";

    for (cin >> command; command != "beigt"; cin >> command)
    {
        if (command == "pievienot")
        {
            ieraksts a;

            cout<<"gads menesis datums!";
            cin>>a.gads>>a.menesis>>a.diena;
            cout<<"pievienots!\n";
            fails->Pievienot(a);
        }

        if (command == "fdrukat")
        {
            fails->DrukatFiziski();
        }

        if (command == "ldrukat")
        {

            fails->DrukatLogiski();
        }

        command = "";
    }

    delete fails;

    cin>>command;
};


