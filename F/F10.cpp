/**
autors: @jzaikovs
izveidots: 10.02.2010.

F10. Doti divi faili f1 un f2.
Failā f1 ir patvaļīgs teksts, failā f2 ir ne vairāk kā 40 vārdu pārīšu, kas atdalīti ar komatiem.
Izdrukāt failā tekstu no ieejas faila f1, kurā visi vārdi, kas ir sastopami failā f2 kā pirmā komponente no pārīša,
tiek aizstāti ar tam atbilstošo failā f2 norādīto vārdu.
Drīkst uzskatīt, ka vārda garums failā nepārsniedz 40 simbolus.
Par vārdu uzskatīt patvaļīgu simbolu virkni, kas atdalīta ar tukšumiem vai pieturas zīmēm (punkts, komats, apaļās iekavas, izsaukuma zīme, jautājuma zīme).

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void output(char filePath[], vector<string*> pairs);

int main()
{
    int ok;
    do
    {
        ifstream file2("f2.txt"); //atveram failu lasīšanai

        if (file2.is_open())
        {
            vector<string*> pairs; //masīvs kurā glabāsies parīši

            int part = 0; //parīša daļa -> 0 - pirmā daļa, 1 - otrā daļa

            bool ignoreWS = true;

            string* arr = new string[2]; //masīvs kurā glabasies pārītis

            char c;

            //IELASA FAILU F2
            file2.get(c);
            while (file2.good())
            {
                if (c != ' ')//ja simbols nav atstarpe tatad simbols ir daļa no pārīša
                {
                    if (c != ',')// ja simbols nav komantas pievieno parišu tekstam
                    {
                        ignoreWS = false;//lidzko atrodam kādu parīša daļu vairs neignorējam atstarpes
                        arr[part] += c; //pievieno attiecīgajai paritiša daļai
                    }
                    else//ja simbols ir komats
                    {
                        ignoreWS = true;//turpmak ignorēsim atstarpes līdz sāksies pārītis
                        pairs.push_back(arr);//pievienojam gatavo pārīti parīšu masīvam
                        arr = new string[2];
                        part = 0; //atstatam parīša daļu
                    }
                }
                else if (ignoreWS == false) part=1; //ja simbols ir atstarpe un ja neignorējam atstarpes tad parslēdzamies uz parīša otro daļu

                file2.get(c); //ielasam nākošo simbolu
            }

            if (arr[0].length() > 0) pairs.push_back(arr);//ieliekam pedeja pariti ja vinjs nebija beidzies ar komanu

            file2.close(); //aiveram failu f2

            output("f1.txt", pairs); //izvadam redziģētu faila f1 textu

        }
        else
        {
            //paziņojam par kļūdu
            cout<<"\nNeizdevas atvert failu f2!!!\n";
        }

        cout << "Vai atkartot (1) vai beigt (0)?" << endl;
        cin >> ok;
    }
    while (ok == 1);


    return 0;
}

void output(char file1[], vector<string*> pairs)
{
    ifstream input(file1);

    if (input.is_open())//ja f1 ir atvērts
    {
        ofstream fOutput("output.txt");//izvades fails

        string word = "";//apstrādājamais vārds

        char c;
        do
        {
            input.get(c);//nolasa nākošo simbolu

            if (!input.eof() && !input.good())
            {
                cout<<"\nRadaas neparedzeta kljuda ielasot failu!!\n";
                break;
            }

            if ((( (int)c >= (int)'A' && (int)c <= (int)'Z') || ( (int)c >= (int)'a' && (int)c <= (int)'z')) && !input.eof())
                word += c;//ja simbols ir burts pievieno to vārdam
            else
            {

                //atrasts simbols kas nav burts taatad vaards ir biedzies
                bool replaced = false;

                //meklējam vai vārds nav atrodāms parīšos

                if (word.length() > 0) //tikai tad ja viņa garums parsniedz vienu simbolu
                    for (int i = 0; i < (int)pairs.size(); i++)
                    {
                        if (pairs[i][0] == word)
                        {
                            //ja vārds ir atrasts parīti tad izvadam parīšā otro dāļu vārda vientā
                            fOutput << pairs[i][1];

                            replaced = true;
                            break;
                        }
                    }

                if (replaced == false) //ja netika vārds aizvietots izvadam to pašu vārdu
                {
                    fOutput << word;
                }

                if (!input.eof()) fOutput << c;
                word = "";
            }


        }
        while (input.good());

        //aizveram failus f1 un izvades failu
        input.close();
        fOutput.close();
    }
    else
    {
        //kļūdas paziņojums
        cout<<"\nNeizdevas atvert failu f1";
    }
}



/*
    Testa piemēri

    f1                                                      f2                                               output
ziema visi zveri, kas negulj, vazaajaas apkart.         vazaajaas klainjo, visi dalja,      ziema dalja zveri, kas negulj, klainjo apkart.

suns, kakis! kakis. (gotinja) pele?                     kakis kaza, gotinja govs            suns, kaza! kaza. (govs) pele?

suns Suns suns suns                                     Suns suns, suns Suns                Suns suns Suns Suns

suns kakis pele govs                                    suns kakis, pele suns,
                                                                govs pele, kakis govs       kakis govs suns pele

*/


