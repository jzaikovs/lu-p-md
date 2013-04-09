/*
Izveidot programmu valodā C++.  Prasības sk. Laboratorijas darbu noteikumos.
H9. Uzrakstīt programmu, kas ļauj izveidot un papildināt bināru failu,
kura ieraksta struktūra ir sekojoša:
vārds – atslēga (nepārsniedz 30simbolus),
vārds – vērtība  (nepārsniedz 30 simbolus),
iepriekšējās atslēgas numurs (int),
nākošās atslēgas numurs (int).

Programmai katrs jauns ieraksts jāieliek faila beigās,
modelējot divpusēji saistītu sarakstu, kura ieraksti sakārtoti alfabētiski pēc atslēgas – t.i.,
katram  ierakstam iepriekšējās atslēgas numurs norāda uz ierakstu
(ieraksta numurs pēc kārtas), kuram ir atslēga  mazāka, nākošās atslēgas
numurs – uz ierakstu, kuram atslēga ir lielāka. Paredzēt iespēju
izdrukāt faila saturu alfabētiskā un apgrieztā secībā.
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct record
{
    char key[30];
    char value[30];
    int prev;
    int next;

    record(string key = "", string value = "", int prev = -1, int next = -1)
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

        this->prev = prev;
        this->next = next;
    }
};

class manager
{
    fstream file;
    int count()
    {
        file.seekg(0, ios::end);//novieto pozīciju beigās

        int n = (int)(file.tellg() / sizeof(record)); //pajautaa, kur atrodas seekg poziicija

        file.seekg(0);

        return n;
    }

    int compair(char a[], char b[])
    {
        int i = 0;
        for (i = 0; a[i]!='\0' || b[i]!='\0'; i++)
        {
            if (a[i] < b[i]) return -1;
            if (a[i] > b[i]) return 1;
        }

        if (i>=30)return 0;

        if (a[i+1]=='\0' && b[i+1]=='\0') return 0;

        if (a[i+1]=='\0')
            return -1;
        else
            return 1;

    }

    void write(record * r, int idx)//raksta failā vārdu idx pozīcija
    {
        idx >= count() ? file.seekp(0, ios::end) : file.seekp(idx * sizeof(record));	//ja idx lielās par varad skaitu pozicija lēc uz beigām

        file.write((char*)r,sizeof(record));
    };

    record * read(int index) //ielasa i-to vardu no saraksta
    {

        if (index >= count()) return NULL; //ja idx lielak atgriež tukšu vārdu

        file.seekg(index * sizeof(record));	//novietojam lasīšanas pozīciju

        record * r = new record();

        file.read((char*)r,sizeof(record));

        return r;
    };
public:
    manager()
    {
        file.open("fails.bin", ios::in | ios::out | ios::binary | ios:: trunc| ios::ate);

        if (file.is_open())
            cout<<"fails atverts\n";
        else
            cout<<"kluuda atverot failu\n";
    };

    ~manager()
    {
        file.close();
    }

    void add(record * r)
    {
        for (int i = 0; i < count(); i++)
        {
            if (i == 0)
            {
                if (compair(read(i)->key,r->key)!=1)
                {
                    r->next = i;
                    record * temp = read(i);
                    temp->prev = count();
                    write(temp,i);
                    delete temp;
                    break;
                }
            }

            if (i == count() - 1)
            {
                if (compair(read(i)->key,r->key)!=-1)
                {
                    r->prev = i;
                    record * temp = read(i);
                    temp->next = count();
                    write(temp,i);
                    delete temp;
                    break;
                }
            }
            else if (compair(read(i)->key,r->key)!=-1)
            {
                if (compair(read(i+1)->key,r->key)!=1)
                {
                    r->prev = i;
                    r->next = i+1;

                    record * temp = read(i);
                    temp->next = count();
                    write(temp,i);
                    delete temp;

                    temp = read(i+1);
                    temp->prev = count();
                    write(temp,i+1);
                    delete temp;
                    break;
                }
            }
        }

        write(r,count());
        delete r;
    };

    void print(int idx = -1)
    {
        record * r = NULL;

        for (int i = 0; i < count(); i++)
        {
            if (read(i)->prev == idx)
                r = read(i);
        }

        if (r!=NULL)
        {

            cout << r->key << " | " << r->value << " | " << r->prev << " | " << r->next << endl;
            int next = r->next - 1;
            delete r;
            print(next);

        }
    };

    void reverse(int idx = -1)
    {
        record * r = NULL;

        for (int i = 0; i < count(); i++)
        {
            if (read(i)->next == idx)
                r = read(i);
        }

        if (r!=NULL)
        {

            cout << r->key << " | " << r->value << " | " << r->prev << " | " << r->next << endl;
            int prev = r->prev+1;
            delete r;
            reverse(prev);
        }
    };
};


int main()
{
    int ok;

    do
    {
        manager *m = new manager();
        cout<<"Komandas: add, print, reverse\n";
        while (true)
        {
            string command;//esoša komanda

            cout<<"k?: ";
            cin>>command;//ievad komandu


            if (command == "add")
            {
                cout<<"ievadi atslegu:\n";
                string key = "";
                cin>>key;
                cout<<"ievadi vertibu:\n";
                string value = "";
                cin>>value;

                record *r = new record(key, value);
                m->add(r);
            }

            if (command == "print")
            {
                m->print();

            }

            if (command == "reverse")
            {
                m->reverse();
            }
        }


        cout << "\n Vai turpinat (1) vai beigt (0)?\n" << endl;
        cin >> ok;
    }
    while (ok == 1);



    return 0;
}
