/*******************************************
A33. Doti trīs pozitīvi skaitļi.
Noteikt vai eksistē trīsstūris ar šādiem malu garumiem un vai tas ir šaurleņķa.
Programma izveidota: 2009/09/28
*******************************************/

# include <iostream>
using namespace std;

int main ()
{
    char atb;

    do
    {
        int a, b, c, max;

        //pieprasaa ievadīt datus, programma nolasa tos
        cout << "Ludzu ievadi triistuura malu garumus" << endl;
        cin >> a >> b >> c;

        //veicam ievadīto malu loģisko pārbaudi
        if (a<1 or b<1 or c<1)
            cout << "Taadas triisstuura malas nepastaav." << endl;
        else
        {
            //nosakaam lielaako veertiibu starp ievadiitajaam
            max=a;
            if (b>max) max=b;
            if (c>max) max=c;
            if (a==max) a=b, b=c;
            if (b==max) b=c;

            //parbaudam vai trijstûris pastâv
            if (max<a+b)
            {
                cout << "Taads triisstuuris pastaav" <<endl;

                //nosakam vai trijstûris ir ðaurleòía
                if ((a*a)+(b*b)> (max*max))
                    cout << "Tas ir shaurlenjkja triisstuuris" << endl;
                else
                    cout << "Tas nav shaurlenjkja triisstuuris. Meegjini veelreiz." << endl;

            }
            else
                cout << "Taads triisstuuris nepastaav." <<endl;
        }

        //piedâvajam iespeeju atkârtot programmu
        cout << "Ja gribi atkartot, ievadi J, ja negribi, ievadi simbolu N" << endl;
        cin >> atb;
    }
    while ((atb == 'J' ) or (atb == 'j' ));

    return 0;
}
