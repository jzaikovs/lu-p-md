/**
H3. Uzrakstīt programmu, kas ļauj izveidot un labot bināru failu,
kurā glabājas datumi un kura ieraksta struktūra ir sekojoša:
gads (int), mēnesis (int), diena (int), ieraksta statuss (0 vai 1).
Programmai katrs jauns ieraksts jāieliek faila beigās.
Ja failā tāds datums jau eksistē, tas nav jāpieliek.
Jāparedz iespēja
(1) izmest faila komponenti (loģiski atzīmējot kā izmestu),
(2) izdrukāt faila esošos datumus uz ekrāna,
(3) izmest loģiski izmestas komponentes fiziski.
*/


#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct datums  //Izveido struct kā komponentes pamatu
{
    int gads;
    int menesis;
    int diena;
    int statuss;//vēlāk noteiks, vai izmest
};

datums x;//struct objekts, ko izmantos funkcijas

bool check(int g, int m, int d) //Pārbauda, vai tāds datums jau eksistē
{
//Tiks izmantots datums x;
    ifstream fin("datumi.bin", ios::in | ios::binary);//Atver datumi.bin lasīšanas režīmā
    fin.read((char *) &x, sizeof(datums)); //Nolasa pirmos sizeof(datums) baitus un ieraksta x
    while(fin)   //atkārto, kamēr nav faila beigas
    {
        if(x.gads == g && x.menesis == m && x.diena == d && x.statuss == 1)   //pārbauda, vai dati sakrīt
        {
            fin.close();
            return true;
        } //ja tāds datums atrasts
        fin.read((char *) &x, sizeof(datums));
    }
    fin.close();
    return false; //ja tāds datums nav atrasts
};

void write(int g, int m, int d, int s)   //Rakstīšana failā
{
//Tiks izmantots datums x;
    x.gads = g;
    x.menesis = m;
    x.diena = d;
    x.statuss = s; //piešķir struct elementiem vērtības
    ofstream fout("datumi.bin", ios::out | ios::app | ios::binary); //Atver datumi.bin rakstīšanas režīmā (ios::app - vecie dati netiek dzēsti)
    if(!fout)
    {
        cout << "Nevar atvert failu!\n";
        fout.close();
    }
    else
    {
        fout.write((const char *) &x, sizeof(datums)); //Ieraksta sizeof(datums) baitus no adreses x uz faila beigām
        fout.close();
        if(!fout.good())
        {
            cout << "Notikusi kluda faila rakstisana!";
        }
    }

};

void newdatums()   //Jauna datuma pievienošana
{
    int g, m, d, s;
    cout << "Ievadiet jaunu datumu (gads,menesis(1-12),diena(1-31),status(0/1)):\n";
    cin >> g;
    cin >> m;
    while(m > 12 || m < 1)
    {
        cout << "Ievadits nepareizs menesis!\nAtkartojiet ievadi:\n";
        cin >> m;
    }
    cin >> d;
    while(d > 31 || d < 1)
    {
        cout << "Ievadita nepareiza diena!\nAtkartojiet ievadi:\n";
        cin >> d;
    }
    cin >> s;
    while(s > 1 || s < 0)
    {
        cout << "Ievadits nepareizs statuss!\nAtkartojiet ievadi:\n";
        cin >> s;
    }

    if(check(g, m, d))
    {
        cout << "Tads datums jau eksiste!\n";    //Izsauc pārbaudi
    }
    else
    {
        write(g, m, d, s);    //Izsauc rakstīšanu
    }
};


void print()   //Faila datu izsaukšana uz ekrāna
{
//Tiks izmantots datums x;
    ifstream fin("datumi.bin", ios::in | ios::binary);//Atver datumi.bin lasīšanas režīmā
    if(!fin)
    {
        cout << "Nevar atvert failu!\n";
        fin.close();
    }
    else
    {
        fin.read((char *) &x, sizeof(datums)); //Nolasa pirmos sizeof(datums) baitus un ieraksta x
        while(!fin.eof())   //atkārto, kamēr nav faila beigas
        {
            cout << x.gads << "." << x.menesis << "." << x.diena << "_:" << x.statuss << endl; //Izvade
            fin.read((char *) &x, sizeof(datums));
        }
        fin.close();
    }
};

void logic_delete()   //Izmest faila komponenti (loģiski atzīmējot kā izmestu)
{
//Tiks izmantots datums x;
    char c = 0;
    int g, m, d, i = -1;
    cout << "Ievadiet datumu, kuru velaties izmest(gads,menesis(1-12),diena(1-31)):\n";
    cin >> g;
    cin >> m;
    while(m > 12 || m < 1)
    {
        cout << "Ievadits nepareizs menesis!\nAtkartojiet ievadi:\n";
    }
    cin >> d;
    while(d > 31 || d < 1)
    {
        cout << "Ievadita nepareiza diena!\nAtkartojiet ievadi:\n";
    }

    ifstream fin("datumi.bin", ios::in | ios::binary);//Atver datumi.bin lasīšanas režīmā
    while(fin)   //Kamēr nav faila beigas
    {
        fin.read((char *) &x, sizeof(datums)); //Nolasa sizeof(datums) baitus un ieraksta x
        i++;//Vēlāk norādīs, kurai komponentei jāmaina statuss
        if(!fin)
        {
            fin.close();    //Ja pārbauda visu failu un neatrod meklēto datumu
            cout << "Datums netika atrasts!";
            break;
        }
        if(x.gads == g && x.menesis == m && x.diena == d && x.statuss == 1)   //pārbauda vai tāds datums eksistē
        {
            fin.close();
            fstream f("datumi.bin", ios::in | ios::out | ios::binary);
            f.seekp(4 * 3 + sizeof(datums)*i, ios::beg); //Pārvieto put() pointeri uz attiecīgo statuss(int*3+komponente*i)
            f.put(c); //Ievieto vērtību (0)
            f.close();
            cout << "Datums tika logiski izmests!";
            break;
        }
    }
};

void fast_delete(istream &fin, ostream &fout)   //Komponenšu dzēšana
{
//Tiks izmantots datums x;
    while(!fin.eof())  //Kamēr nav faila beigas
    {
        fin.read((char *) &x, sizeof(datums));  //Nolasa
        if(x.statuss == 1)   //Ja statuss ir 1, tad komponente tiek ierakstīta temp.bin
        {
            fout.write((char *) &x, fin.gcount());
        }//gcount tiek izmantota, lai zinatu, cik karteja reize nolasiti baiti
    }
};

void real_delete()   //Komponenšu dzēšana/Failu atvēršana/aizvēršana/dzēšana
{
    ifstream fin("datumi.bin", ios::in | ios::binary);
    ofstream fout("temp.bin", ios::out | ios::binary); //izveido temp.bin
    fast_delete(fin, fout); //Pārraksta tās komponentes, kuru statuss ir 1, no datumi.bin uz temp.bin
    fin.close();
    fout.close();

    ifstream ffin("temp.bin", ios::in | ios::binary);
    ofstream ffout("datumi.bin", ios::out | ios::binary);
    fast_delete(ffin, ffout); //Pārraksta datus no temp.bin uz datumi.bin
    ffin.close();
    ffout.close();
    remove("temp.bin");//Iznīcina temp.bin
    cout << "Datumi tika izdzesti";
};


int main()//Sākas galvenā funkcija
{

    int y;
    char x;

    cout << "a => pievienot jaunu datumu faila gala\n";
    cout << "b => izdrukat datumus\n";
    cout << "c => atzimet datumu, ka logiski izmestu\n";
    cout << "d => iznicinat datumus fiziski\n";
    cout << "q => beigt darbu ar programmu\n";

    do
    {
        cout << "\nIevadiet komandu:";
        cin >> x;

        while(x == 'a')
        {
            newdatums();
            cout << "Atkartot ievadi?[a]:";
            cin >> x;
        }

        if(x == 'b')
        {
            print();
        }
        if(x == 'c')
        {
            logic_delete();
        }
        if(x == 'd')
        {
            real_delete();
        }

    }
    while(x != 'q');

    return 0;
};
