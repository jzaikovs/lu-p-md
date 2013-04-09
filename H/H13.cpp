/*
autors: @jzaikovs

H13.
Uzrakstīt programmu, kas realizē sakārtotu sarakstu ar tabulas palоdzību.
Sarakstā glabājas patvaļīgi vārdi. Jābūt iespējai sarakstu papildināt un izdrukāt.
Vārdu garums nepārsniedz 20 simbolus.
Tabulas lielums – 100 ieraksti.

Tabulu realizēt kā tieрšās pieejas failu.

*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class SortedList
{
    int wordSize; //vārda maksimālālais

    fstream table;

    int count()//funkcija kas saskaita cik vārdu ir failā
    {
        table.seekg(0, ios::end);
        int n = table.tellg() / wordSize;

        table.seekg(0);

        return n;
    };

    void write(string s, int idx)//raksta failā vārdu idx pozīcija
    {
        idx >= count() ? table.seekp(0, ios::end) : table.seekp(idx * wordSize);	//ja idx lielās par varad skaitu pozicija lēc uz beigām

        for(int i = 0; i < wordSize; i++)
        {
            char c = '\0';

            if (i < (int)s.length()) c = s[i];

            table.write(&c, sizeof(char));
        }
    };

    string read(int index) //ielasa i-to vardu no saraksta
    {
        string result  = "";

        int n = count();//vardu skaits

        if (index >= n)	return result; //ja idx lielak atgriež tukšu vārdu

        table.seekg(index * wordSize);	//novietojam lasīšanas pozīciju

        for (int i = 0; i < wordSize; i++)
        {
            char c;
            table.read((char*)&c,sizeof(char));

            if (c != '\0') result += c;
        }

        return result;
    };

    void addName(string v, int l, int r);

public:
    SortedList();
    ~SortedList()
    {
        table.close();
    };
    void AddName(string value);
    void Print();
};

int main()
{
    int ok = 0;
    do
    {
        SortedList * list = new SortedList();

        string command = "";

        for (cin >> command; command != "end"; cin >> command)
        {
            if (command == "add")
            {
                string vards;
                cin>>vards;
                list->AddName(vards);
            }
            if (command == "print")
            {
                list->Print();
            }
        }

        delete list;

        cout << "Vai turpinat (1) vai beigt (0)?\n" << endl;
        cin >> ok;
    }
    while (ok == 1);

    return 0;
}

SortedList::SortedList()
{
    wordSize = 20;

    table.open("tabula.bin", ios::in | ios::out | ios::binary | ios::ate | ios::trunc);//izveidojama jaunu tabulu failā

    if (table.is_open())
        cout<<"tabula atverta"<<endl;
    else
        cout<<"neizdevas atvert tabulu";
};

void SortedList::AddName(string value)
{
    addName(value, 0, count()); //izsaucam pievienošanu rekursīvo funkciju
};

void SortedList::addName(string v, int l, int r)
{
    int p = l + (r - l) / 2; //vidējā elementa indeks

    if (v == read(p))
    {
        cout<<"Tads vards jau eksistee!\n";
        return;
    }

    if (l == r) //ja gan labā, gan kreisā robeža sakrоt tad ir atrasta vieta kur ielikt jauno vārdu
    {
        for (int i = count(); i > l; i--) //pārbīdam visu vārdu nakošo vārdus par vienu vietu uz priekšu
            write(read(i-1), i);

        write(v, l);		//ieraksta jauno vārdu
    }
    else
    {
        if (v > read(p)) //labā puse
            addName(v, p + 1, r);
        else if (v < read(p)) // kreisā puse
            addName(v, l, p);
    }
};

void SortedList::Print() //saraksta izvadīšanas funckija
{
    int size = count(); //esošais vārdu skaits

    cout<<"------------\n";

    for (int i = 0; i < size; i++)
    {
        cout<< read(i) <<endl; //ielasasa izmantojot ielasīšanas funkciju

        if (!table.good())
        {
            cout<<"kljuda ielasot failu!!!\n";
            break;
        }
    }
    cout<<"------------\n";
};

/*
//TEST PIEMERI

add ziema janis juris liiga   print janis juris liiga ziema
add liiga janis juris         print janis, juris liiga
add j arturs zemene           print arturs j zemene				add janis			print arturs j janis zemene








*/
