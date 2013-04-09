/**
Izveidot programmu valodā C++, kas apstrādā teksta failu secīgā režīmā.
Dati no faila jānolasa pa vienam simbolam (nedrīkst nolasīt uzreiz visu
failu vai veselu rindiņu). Citas prasības sk. Laboratorijas darbu
noteikumos.
F8. Dots teksta fails f. Uzrakstīt programmu, kura atrod failā f visus
vārdus, kas sākas ar simbolu x (x- patvaļīgs simbols, kuru var uzdot
lietotājs un kas nav ne tukšums, ne pieturas zīme). Izvadīt failā f1 šos
vārdus un atbilstoši katram rindiņas numuru, kurā tas sastapts. Par
vārdu uzskatīt patvaļīgu simbolu virkni, kas atdalīta ar tukšumiem vai
pieturas zīmēm (punkts, komats, apaļās iekavas, izsaukuma zīme,
jautājuma zīme). Drīkst uzskatīt, ka vārda garums nepārsniedz 40.
*/

#include <iostream>
#include <fstream>
using namespace std;

//Sākas galvenā funkcija
int main()
{

    int ok;
    do
    {

        fstream fin ("f.txt ", ios::in);//Sākotnējā faila deklarēšana/atvēršana
        fstream fout ("f1.txt", ios::out);//Rezultāta faila deklarēšana/atvēršana

        char s;
        char x;
        int exp=0;//Stāvokļi
        int i=1;//Rindas numurs


        cout<<"Ievadiet simbolu:";
        cin>>x;

        fin.get (s);//Nolasa pirmo simbolu

        while(fin)  //Faila nolasīšana pa vienam simbolam
        {

            if (s==10) //Rindiņu numura noteikšana (pieskaitot 1, ja s == new line simbolu(pāreja uz nākamo rindu)
            {
                fout<<endl;
                i++;
            }

            if(exp==0) //Ja vēl nav sācies vārds
            {
                if(s==x)  //Norāda, ka vārds sākās ar x
                {
                    exp=1; // stāvokļa maiņa, jo vārds sākas ar x
                    fout<<" "<<i<<". ";
                }
                else  //Norāda, ka nesākas ar x
                {
                    exp=3; // stāvokļa maiņa, jo vārds nesākas ar x
                }
            }

            if (exp==1) //Ja vārds sācies ar x
            {
                if(s==' '||s=='!'||s=='?'||s=='.'||s==','||s==')'||s=='('||s==10)  //Ja parādas kāds no beigu simboliem
                {
                    exp=0;//Norāda, ka vārds ir beidzies
                }
                else  //Citādi ieraksta simbolu rezultāta failā
                {
                    fout.put (s);
                }
            }

            if (exp==3) //Ja nesākas ar x
            {
                if(s==' '||s=='!'||s=='?'||s=='.'||s==','||s==')'||s=='('||s==10)  //Ja parādas kāds no beigu simboliem
                {
                    exp=0;//Norāda, ka vārds ir beidzies
                }
            }

            fin.get (s);//Nolasa nākamo simbolu
        }

        fin.close ();//Sākotnējā faila aizvēršana
        fout.close ();//Rezultāta faila aizvēršana

        cout<<"Vardi parrakstiti!"<<endl;


        cout << " Vai turpinat (1) vai beigt (0)?" << endl;
        cin >> ok;
    }
    while (ok == 1);

} //Galvenās funkcijas beigas
