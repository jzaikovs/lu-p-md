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

*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//ieraksta struktūra
struct Record
{
    char key[30];//atslēga
    char value[30];//vērtība
    bool status;//status

    //defaultais konstruktors
    Record()
    {

    }

    //ieraksta konstrukturs
    Record(string key, string value, bool status)
    {
        for (int i = 0; i < 30; i++)
        {
            this->key[i]='\0';
            this->value[i]='\0';

            if (i < key.length())
                this->key[i] = key[i];

            if (i<value.length())
                this->value[i] = value[i];
        }

        this->status = status;
    }
};

class FileManager
{
    fstream file;

    int count()//funkcija kas saskaita cik vārdu ir failā
    {
        file.seekg(0, ios::end);

        int n = (int)(file.tellg() / sizeof(Record));

        file.seekg(0);

        return n;
    };

    void write(Record r, int idx)//raksta failā vārdu idx pozīcija
    {
        file.seekp(idx * sizeof(Record));

        file.write((char*)&r, sizeof(Record));
    };

    Record read(int index) //ielasa i-to vardu no saraksta
    {
        Record r;

        file.seekg(index * sizeof(Record));	//novietojam lasīšanas pozīciju

        file.read((char*)&r, sizeof(Record));

        return r;
    };

public:

    FileManager()
    {
        file.open("file.bin", ios::in | ios::out | ios::binary | ios::ate  );//izveidojama jaunu tabulu failā

        if (file.is_open())
            cout<<"#fails atverts"<<endl;
        else
            cout<<"#neizdevas atvert failu";
    }

    ~FileManager()
    {
        file.close();
    };

    void Add(Record r)
    {
        this->write(r,this->count());//ievieto ierakstu faila beigās
    };

    void Delete(int index)
    {
        file.seekp(index * sizeof(Record) + 60); //pariet uz ieraksta poziciju kurā glabājās viens baits kas nozīme vai fails dzēsts vai nee
        bool status = true;
        file.write((char*)&status,sizeof(bool)); //ieraksta ka fails ir dzēsts
    };

    void Print()
    {
        int n = count(); //elementu skaits

        for (int i = 0; i< n; i++)
        {
            Record r = read(i);//nolasa i-to ierakstu
            cout<<r.key << " | " << r.value << " | " << r.status << endl;//izvada ierakstu
        }
    };

    void Clean()
    {
        int n = count(); //saiskaita elementus

        Record * arr = new Record[n]; //vieta kur nogalābās elementus

        for (int i = 0 ; i < n; i++)
        {
            Record r = read(i);

            arr[i] = r;

            if (r.status)
            {
                for (int j = i + 1; j < n; j++)
                {
                    Record r2 = read(j);
                    write(r2, j - 1);
                    arr[j - 1] = r2;
                }
                n--;
                i--;
            }
        }

        file.close();
        file.open("file.bin", ios::in | ios::out | ios::binary | ios::ate  | ios::trunc);

        for (int i = 0; i< n; i++)
            write(arr[i],i);

        delete arr;
    }
};

int main()
{
    int ok = 0;

    do
    {
        FileManager * manager = new FileManager();

        cout<<"komandas: add, print, delete, clean"<<endl;

        string command = "";

        for (cin >> command; command != "end"; cin >> command)
        {
            if (command == "add")
            {
                cout<<"atslega:";
                string key;
                cin>>key;
                cout<<"vertiba:";
                string value;
                cin>>value;

                Record r(key,value,false);
                manager->Add(r);
            }

            if (command == "print")
            {
                manager->Print();
            }

            if (command == "delete")
            {
                int i = 0;
                cin>>i;
                manager->Delete(i);
            }

            if (command == "clean")
            {
                manager->Clean();
            }
        }

        delete manager;

        cout << "Vai turpinat (1) vai beigt (0)?\n" << endl;
        cin >> ok;
    }
    while (ok == 1);

    return 0;
}
