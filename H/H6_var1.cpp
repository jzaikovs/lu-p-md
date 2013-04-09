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

    //tukšais konstruktors
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

            if (i<key.length())
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

public:
    FileManager()
    {
        file.open("file.bin", ios::in | ios::out | ios::binary | ios::ate | ios::trunc );//izveidojama jaunu tabulu failā

        if (file.is_open())
            cout<<"#fails atverts"<<endl;
        else
            cout<<"#neizdevas atvert failu";
    }

    ~FileManager()
    {
        file.close();
    }

    void Add(Record r, int index = -1)
    {
        int put = file.tellp();

        if (index == -1)
            file.seekp(0, ios::end);
        else
            file.seekp(index * sizeof(Record));
        file.write((char*)&r, sizeof(Record));

        file.seekp(put);
    }

    void Delete(int index)
    {
        file.seekp(index * sizeof(Record) + 60);
        bool status = true;
        file.write((char*)&status,sizeof(bool));
    }

    void Print()
    {
        file.seekg(0);

        Record r;
        for (file.read((char*)&r,sizeof(Record)); file.good(); file.read((char*)&r,sizeof(Record)))
        {
            cout<<r.key<<"|"<<r.value<<"|"<<r.status<<endl;
        }

        file.clear();
        file.seekg(0);
    }

    void Clean()
    {
        file.seekg(0);
        int i = 0;
        Record r;
        for (file.read((char*)&r,sizeof(Record)); file.good(); file.read((char*)&r,sizeof(Record)))
        {
            if (r.status)
            {
                int get = file.tellg();

                int j = i;

                file.seekp(j * sizeof(Record));

                Record t;
                for (file.read((char*)&t,sizeof(Record)); file.good(); file.read((char*)&t,sizeof(Record)))
                {
                    this->Add(t,j);
                    j++;
                }


                file.clear();
                file.seekg(get);
            }

            i++;
        }

        file.clear();
        file.seekg(0);
    }
};

int main()
{
    int ok = 0;

    do
    {
        FileManager * manager = new FileManager();

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
                cout<<"index";
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