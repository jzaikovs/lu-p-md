/**

Izveidot programmu valodâ C++, kas apstrâdâ teksta failu secîgâ reþîmâ.
Dati no faila jânolasa pa vienam simbolam (nedrîkst nolasît uzreiz visu failu vai veselu rindiòu).
Citas prasîbas sk. Laboratorijas darbu noteikumos.

F4. Dots teksta fails f. Uzrakstît programmu, kura atrod failâ f visus vârdus,
kas ir apakðvirkne dotajai virknei m.
Izvadît šos vārdus failâ f1.
Par vârdu uzskatît patvaïîgu simbolu virkni, kas atdalîta ar tukðumiem vai pieturas zîmçm (punkts, komats, apaïâs iekavas, izsaukuma zîme, jautâjuma zîme).
Drîkst uzskatît, ka vârda garums nepârsniedz 40.
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool sfind (string in, string find);

int main ()
{
    int ok;
    do
    {
        ifstream fails("f.txt"); //ielasa failu

        if (fails.is_open())
        {
            ofstream fails2("f1.txt"); // definç izejas failu

            string m = ""; // definç mainîgo, kurâ glabâ apakðvirkni
            cout << "Ievadiet vardu m:"<<endl;
            cin >> m;

            string vards = ""; //definç mainîgo, kurâ glabâ vârdu, kas vçl nav pabeigts

            for (char c = fails.get(); fails.good(); c = fails.get())
            {
                string end = " -&.,)(!?\n"; // vârda beigu simboli

                string C = "";
                C += c;

                if (sfind(end, C)) // ja vârda sastâvâ neietilpst beigu simbols, vârdu turpina
                {

                    if (vards.length() == 0 || m.length() == 0) continue; // ja vârds vai apakðvirknes garums ir 0, tad ciklu turpina

                    if (sfind(m, vards))
                    {
                        cout<<vards<<endl;

                        for (int i = 0; i < (int)vards.length(); i++) // (int) pârveido no unsigned tipa uz int
                        {
                            fails2.put(vards[i]); // katrs vârda burts tiek ielikts citâ/jaunâ failâ no mainîgâ
                        }

                        fails2.put('\n');

                    }

                    vards = ""; // vârds tiek atstatîts
                }
                else  //ja simbols nav beigu tad uzskata, ka vârds turpinâs un tam pieliek ielasîto simbolu
                {
                    vards+=c;
                }
            }

            cout << endl << "Ieejas virkne ir parstradata un izvadita jauna faila!" << endl << endl;

            //aizver abus failus
            fails.close();
            fails2.close();
        }
        else
        {
            //Izvada kïûdas paziòojumu, ja nav faila, kuru nolasît.
            cout<< "Kluda, nav faila, kuru nolasit" <<endl;
        }


        cout << "Vai turpinat (1) vai beigt (0)?" << endl;
        cin >> ok;
    }
    while (ok == 1);

};

bool sfind (string in, string find)
{
    for (int i = 0; i < (int)in.length() - (int)find.length() + 1; i++)
    {
        bool sakrit = true

                      for (int j = 0; j < (int)find.length(); j++)
        {
            if (in[i+j] != find[j])
            {
                sakrit = false;
                break;
            }

        }

        if (sakrit) return true;
    }

    return false;
}