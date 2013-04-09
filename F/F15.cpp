/**
F15. Dots teksta fails.
Uzrakstīt programmu, kura pārveido doto failu tā, lai katrā rindiņā būtu ne vairāk kā n simboli (10<=n<=80).
Vienu vārdu nedrīkst sadalīt daļās, tam jāatrodas vienā rindiņā.
Vārds jāraksta jaunā rindiņā tikai tad, ja tas nesaiet iepriekšējā.
Drīkst uzskatīt, ka vārda garums failā nepārsniedz n simbolus.
Par vārdu uzskatīt patvaļīgu simbolu virkni, kas atdalīta ar tukšumiem vai
pieturas zīmēm (punkts, komats, apaļās iekavas, izsaukuma zīme, jautājuma zīme).

*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//pārbauda vai simbols ir vārda beigu simbols
bool beiguSimbols(char c)
{
    return c == ' ' || c == ',' || c == '.' || c == '!' || c == '?' || c == '(' || c == ')' ||  c == '\n';
}

int main()
{
    int ok;

    do
    {
        int n = 20; //n - rindiņas platums

        cout<<"cik burtu viena rinda?\n";
        cin>>n;

        fstream f("f.txt", ios::in | ios::out);

        string buffer = "";

        if (f.is_open())
        {
            string vards = ""; //pēdejais ielasītais vārds

            char c;		//glabajās ielaisītais simbols

            int k = 0;	//rindiņā esošo simbolu skaits

            do
            {
                f.get(c);//ielasam simbolu

                vards += c;

                if ( beiguSimbols(c) || f.eof() )
                {
                    if (k + vards.length() > n)
                    {
                        buffer+='\n';
                        k = 0;
                    }

                    buffer += vards;

                    if (c == '\n')
                        k = 0;
                    else
                        k += (int)vards.length();

                    vards = "";
                }

            }
            while(f.good());

            f.close();

            //ofstream in("f.txt");
            for (int i= 0; i<(int)buffer.length(); i++)
                cout<<buffer[i];

        }

        cout << "Vai turpinat (1) vai beigt (0)?" << endl;
        cin >> ok;
    }
    while (ok == 1);


    return 0;
}