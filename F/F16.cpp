/****
F16. Dots teksta fails, kurā atrodas sintaktiski pareizs C++ programmas
teksts. Saskaitīt , cik if operatoru un cik cikla operatoru (for, while)
satur dotā programma. Drīkst uzskatīt, ka programmas tekstā nav
komentāru un ka attiecīgie simboli neparādīsies teksta literāļos.

datums: 24.02.2010.
*****/


#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    int ok;

    do
    {
        ifstream fails("kods.txt");

        if (fails.is_open())
        {
            const int N = 3; //vardu skaits
            string *vardi = new string[N]; //vaardi, kurus meklee kaa dinamisks string masiivs

            vardi[0] = "if";
            vardi[1] = "for";
            vardi[2] = "while";

            int *skaits = new int[N];	//mekleeto vaardu skaits dinamiskaa masivaa
            for (int i = 0; i < N; i++) skaits[i] = 0; //saakuma veertiiba

            string vards = ""; //deklaree tukshu mainiigo ar tipu strings, kuraa tiks glabaats jaunieguutais vaards no faila

            char c;
            for (fails.get(c); fails.good(); fails.get(c)) //cikls, kas ieguust simbolu, paarbauda vai simbols nav beigu simbols, "sagatavo naakosho simbolu"
            {
                int ci = (int)c; //ci tiek glabaata ieguutaa simbola skaitliskaa veertiiba

                if ((ci >= (int)'A' && ci <= (int)'Z') || ( ci >= (int)'a' && ci <= (int)'z')) //ci skaitlisko veertiibu paarbauda, vai simbols ir burts
                    vards += c; //ja ci ir burts, tad vaardam, kuru salidzina pievieno sho burtu, lidz atstarpei vai kaadam citam simbolam
                else
                {
                    if (vards.length() > 0) // paarbauda, vai vaarda garums ir lielaaks par 0
                    {
                        for (int i = 0; i < N; i++) //tik, cik ir saliidzinaamo vaardu, tik reizes saliidzina atrasto vaardu ar nepiecieshamajiem, ja ir atrasta atbilstiiba, pieskaita attiecigajam skaitam +1
                        {
                            if (vardi[i] == vards)
                            {
                                skaits[i]++; //attiecigaa vaarda skaits
                                break;
                            }
                        }
                    }
                    vards = ""; // ieguuto vaardu nonullee
                }
            }

            for (int i = 0; i < N; i++) //izvade
            {
                cout<<vardi[i]<<": "<<skaits[i]<<endl;
            }
        }

        fails.close();

        cout << "Vai turpinat (1) vai beigt (0)?"<< endl;
        cin >> ok;
    }
    while (ok == 1);

    return 0;

}
