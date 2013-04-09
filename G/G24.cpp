/* === G24 =======================================
Izveidot programmu valodā C++, kas ļauj izveidot vienvirziena saistīto
sarakstu (izmantojot dinamiskās datu struktūras), kurā glabājas veseli
skaitļi. Jābūt paredzētai iespējai sarakstu papildināt ar jaunu elementu
(pielikt elementu saraksta galā), izdrukāt sarakstu, iznīcināt sarakstu.
Bez tam jāuzraksta funkcija, kura aprakstīta zemāk. Iznīcinot saraksta
elementus, korekti jāatbrīvo izdalītā atmiņa. Galvenajā programmā:
a) jābūt iespējai ievadīt saraksta elementus (izveidot patvaļīgu sarakstu),
b) jāpielieto uzrakstītā funkcija sarakstam,
c) jāizdrukā saraksts pēc funkcijas darbības.
d) beigās jāiznīcina saraksts (lietojot delete).

G24. Uzrakstīt funkciju, kas izmet no saraksta tos elementus, kuriem
vērtība vienāda ar to kārtas numuru.

darbs veidots: 15.04.2010.
*/

#include <iostream>
#include <string>

using namespace std;

class saistitaisSaraksts
{
    struct elements
    {
        int skaitlis;
        elements * next;
    };

    elements * start, * beigas;

public:
    saistitaisSaraksts();
    ~saistitaisSaraksts();

    void pievienot(int a);
    void izdrukat();
    void specialaFunkcija();
};



int main()
{
    int ok;
    do
    {
        string komanda;

        saistitaisSaraksts *saraksts = new saistitaisSaraksts();

        do
        {
            cout << "kaadu komandu izpildiit? (add, print, function, end) \n";
            cin>> komanda;

            if (komanda == "add")
            {
                int i;
                cin >> i;
                saraksts->pievienot(i);
            }

            if (komanda == "function") saraksts->specialaFunkcija();


            if (komanda == "print") saraksts->izdrukat();

        }
        while (komanda != "end");

        cout << "Vai turpinat (1) vai beigt (0)?"<< endl;
        cin >> ok;
    }
    while (ok == 1);

    return 0;
}

saistitaisSaraksts::saistitaisSaraksts()
{
    start = NULL;
    beigas = NULL;
};

saistitaisSaraksts::~saistitaisSaraksts() //kameer pirmais elements nav null,
//tiek dzeesti citi elementi kjeediitee, saakot no pirmaa
{
    while (start != NULL)
    {
        elements *p = start->next;
        delete start;
        start = p;
    }
};

void saistitaisSaraksts::izdrukat()
{
    elements * p = start;

    while (p != NULL)
    {
        cout << p->skaitlis << " ";
        p = p-> next;
    }

    cout<<endl;
};

void saistitaisSaraksts::pievienot(int a)
{
    elements * p = new elements();  //izveido jaunu elementu, kuram pieshkjir skaitli
    p->skaitlis = a;
    p->next = NULL;

    if (start == NULL)	//paarbauda vai ir ievadiits vel kaads skaitlis ieprieksh, ja nav, tad p veertiibu pieshkjir saakumam
        start = p;
    else
        beigas->next = p;	//ja ir, tad p veertiiba tiek pieshkjirta elementam, kursh shobriid ir arii beigu elements

    beigas = p; //katrs ievadiitais skaitlis ir beigu elements
};

void saistitaisSaraksts::specialaFunkcija()
{
    int i = 0;

    elements *p = start, *last = start;	//saakuma defineeshana, kur saakuma un beigu elements ir pirmais elements

    while(p != NULL)
    {
        elements *q = p->next; //q noraada uz nakosho elementu, saglabaajas naakoshaa elementa noraade

        if (p->skaitlis == i)
        {
            delete p;

            if (p == start) //ja pirms izdzeeshanas p bija pirmais elements, tad saakuma veertiiba paariet uz naakosho elementu, kas ir q
                start = q;
            else
                last->next = q;	//ja p nebija saakuma elements un netika izdzeests, tad q paariet uz naakosho elementu
        }
        else
            last = p; 	//

        p = q; //ja nesakriit ar kaartas numuru un netika izdzeests, paariet uz naakosho elemetu
        i++;
    }
    beigas = last; //lai beigu elements peec funkcijas veikshanas nezaudeetu savu vietu un programma zinaatu,
    //kura vietaa pievienot naakosho elementu
};


// ievada          izvada peec funkcijas izmantoshanas
// 0 1 1 4 2 5     1 4 2
// 1 0 1 3         1 0 1
// 1 1 7 4 4 9     1 7 4 9
// -1               -1, jo funkcija nenostraadaa, jo neeksistee kaartas skaitlji ar negatiivaam veertiibaam
// 1 0 1 3         1 0 1 , pievieno atkal elementus 4 4 4, izvada 1 0 1 4 4
