#include <iostream>
using namespace std;

int main ()
{
    int n = 0, a, max=0, max2=0, max3=0; //mainigo definesana
    int ok;

    do
    {
        cout<<"Ievadiet naturalu skaitli (masiva garumu):"<<endl;
        cin>>n; //ievada masiva elementu skaitu
        cout<<endl;

        int* arr = new int[n]; //define masivu

        if (n<3)
            cout<<"Kluda, ievadits nenaturals skaitlis!"<<endl<<endl; //parbauda vai ievadits naturals skaitlis
        else
        {

            for (int i=0; i<n; i++)
            {
                cout<<"Ievadiet masiva elementu:"<<endl;
                cin>>arr[i]; //ievada masiva elementus



                if (arr[i]>max)
                {
                    max3 =  max2;
                    max2 = max;
                    max=arr[i];
                }
                //if ((arr[i]<max) && (arr[i]>max2)) {max2=max, max2=arr[i];}
                //if (arr[i]<max2 && arr[i]>max3) {max3=max2, max3=arr[i];}
            }

            cout<<endl;
            cout<<"3. lielakais masiva elements ir:"<<" "<<max3<<endl<<endl;
        } //izvada 3. lielako masiva elementu
        cout<<"Vai turpināt (1) vai beigt (0)?"<<endl; //piedava turpinat vai beigt programmu
        cin>>ok;
    }
    while (ok==1);
}
