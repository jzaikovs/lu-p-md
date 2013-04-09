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
21.06.2010
*/

#include <iostream>
#include <fstream>

using namespace std;

struct record                 // ieraksts
{
    char key[30], value[30];  // atslēga ar vērtību
    int prev, next;           // norādes uz nākamajiem ierakstiem
};

class manager
{
    fstream file; // fails, kurā rakstām un no kura lasām

    int count() // cik ierakstu ir failā
    {
        file.seekg(0, ios::end);              // aiziet līdz faila beigām
        return file.tellg() / sizeof(record); // tā kā esam faila beigās, tad pašreizējā pozīcija ir faila izmērs, to izdalot ar viena ieraksta izmēru, varam iegūt skaitu
    }

    void write(record *r, int index) // ieraksta ierakstu r failā index-ajā pozīcijā (sākot no nulles)
    {
        file.seekp(index * sizeof(record));   // aiziet uz index-o pozīciju
        file.write((char*)r, sizeof(record)); // ieraksta
    }

    record *read(int index) // nolasa ierakstu no pozīcijas index
    {
        if (index < 0 || index >= count())   // pārbaudām vai pozīcija ir derīga
            return NULL;                     // ja nav, tad atgriežam tukšuma norādi

        record *r = new record;               // izveido jaunu ierakstu
        file.seekg(index * sizeof(record));   // aiziet uz index-o pozīciju
        file.read((char*)r, sizeof(record));  // nolasa ierakstu
        return r;
    }

    record *first(bool asc, int &pos) // atrod pirmo (asc = true) vai pēdējo (asc = false) ierakstu
    {
        for (int i = 0, cnt = count(); i < cnt; i++)     // jāatrod ieraksts
        {
            record *r = read(i);                         // nolasām ierakstu
            if (r != NULL)
            {
                if ((asc && r->prev == -1) || (!asc && r->next == -1))   // ja kreisajā pusē nav norādes, tas ir pirmais, ja labajā pusē nav norādes tas ir pēdējais elements
                {
                    pos = i;
                    return r;
                }
                else
                {
                    delete r;
                }
            }
        }
    }

public:
    manager() // kad izveido jaunu šo klasi
    {
        file.open("fails.bin", ios::in | ios::out | ios::binary | ios:: trunc| ios::ate); // atveram failu, to pirms tam notīrot
    }

    ~manager() // kad atbrīvojas no klases
    {
        file.close(); // aizveram failu
    }

    void add(char *key, char *value) // pievieno faila beigās atslēgu ar tās vērtību
    {
        record *n = new record;   // izveido jaunu ierakstu
        strcpy(n->key, key);      // pārkopē atslēgu
        strcpy(n->value, value);  // pārkopē vērtību

        int rpos;                        // ieraksta pozīcija (index)
        record *r = first(true, rpos);   // nolasa pirmo ierakstu

        if (r == NULL)            // ja pirmā ieraksta nav, tad
        {
            n->prev = -1;         // nākamā ieraksta un
            n->next = -1;         // iepriekšējā ieraksta nav
            write(n, 0);          // ierakstām ierakstu kā pirmo (jeb sākot no nulles skaitīt, tas ir nulltais)
        }
        else
        {
            while (r != NULL && strcmp(r->key, n->key) < 0)   // ja tomēr ir ieraksts un tā atslēga ir mazāka alfabētiskā secībā
            {
                int next = r->next;                           // noskaidrojam nākamo ierakstu
                if (next != -1) rpos = next;
                delete r;                                     // atbrīvojam atmiņu no tikko nolasītā
                r = read(next);                               // lasām nākamo, kamēr ir beigas vai atslēga ir lielāka, kas nozīmē, tā ies pirms šī ieraksta
            }
            if (r == NULL)                           // liksim beigās
            {
                r = read(rpos);                      // pēdējāis ieraksts, kas tagad būs pirmspēdējais
                n->prev = rpos;                      // iepriekšējais būs pirmspēdējais ieraksts
                n->next = -1;                        // nākamā ieraksta nav
                int npos = count();              // būs beigās
                write(n, npos);                  // ierakstām jauno ierakstu
                r->next = npos;                  // pirmspēdējā ieraksta nākamais ieraksts būs jaunais ieraksts
                write(r, rpos);                  // atjauninām pēdējo tagad jau pirmspēdējo ierakstu
                delete r;
            }
            else
            {
                n->prev = r->prev;              // iepriekšējais ieraksts būs nākamā ieraksta iepriekšējais
                n->next = rpos;                 // nākamais ieraksts būs nākamais ieraksts, pirms kura mēs ieliekam
                int npos = count();             // būs beigās
                write(n, npos);                 // ieraksta jauno ierakstu
                record *prev = read(r->prev);   // atrod iepriekšējo
                if (prev != NULL)               // ja tāds iepriekšējais vispār ir
                {
                    prev->next = npos;          // to atjaunina
                    write(prev, r->prev);
                    delete prev;
                }
                r->prev = npos;                // atjaunina nākamo ierakstu
                write(r, rpos);
                delete r;
            }
        }

        delete n;
    }

    void print(bool asc) // parāda visus ierakstus alfabētiskā (asc = true) vai pretējā (asc = false) secībā kārtotus pēc atslēgas
    {
        int rpos;
        record *r = first(asc, rpos);            // atrod pirmo ierakstu
        while (r != NULL)                        // ja ieraksts ir nolasīts
        {
            // cout << "(" << r->prev << ") " << r->key << " = " << r->value << " (" << r->next << ") -> ";
            cout << r->key << " = " << r->value << " -> ";
            int next = asc ? r->next : r->prev;  // nākamais ieraksts atrodas next (vai prev) pozīcijā (t.i. next un prev ir norāde uz nākamo ierakstu, jo tas ir sakārtots saraksts)
            delete r;                            // izdzēšam tikko nolasīto, lai varētu ielasīt nākamo
            r = read(next);                      // nolasām nākamo ierakstu
        }
        cout << "." << endl;                     // ar punktu parādām, ka tas ir viss
    }
};


int main()
{
    manager mgr;          // jauna klase

    mgr.add("c", "1");
    mgr.add("b", "1");
    mgr.add("a", "1");

    /* mgr.add("a", "1");
    mgr.add("b", "1");
    mgr.add("c", "1"); */


    /*	mgr.add("b", "1");    // pievieno atslēgu ar vērtību (vērtībām nav pilnīgi nekādas nozīmes)
    	mgr.add("e", "2");
    	mgr.add("g", "3");
    	mgr.add("d", "4");
    	mgr.add("a", "4");
    	mgr.add("c", "4");
    	mgr.add("f", "4");
    	mgr.add("h", "4");
    */
    mgr.print(true);      // alfabētiski
    mgr.print(false);     // pretēji

    system("pause");

    return 0;
}
