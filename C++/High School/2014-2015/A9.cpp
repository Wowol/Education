#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

    char x[100505];
    char y[100505];
    int a[100505];
    int b[100505];

void reversionA()
{
    int dlugosc = 0;
    for (int i=0; i<100505; i++)
    {
        if (x[i] == NULL)
        {
            dlugosc = i;
            break;
        }
        a[i] = x[i] - '0';
    }



    for (int i = 0; i<dlugosc; i++)
    {
        a[100505-i] = a[dlugosc-i-1];
        a[dlugosc-i-1] = 0;
    }

}




void reversionB()
{
    int dlugosc = 0;
    for (int i=0; i<100505; i++)
    {
        if (y[i] == NULL)
        {
            dlugosc = i;
            break;
        }
        b[i] = y[i] - '0';
    }


    for (int i = 0; i<dlugosc; i++)
    {
        b[100505-i] = b[dlugosc-i-1];
        b[dlugosc-i-1] = 0;
    }
}




void zeruj()
{
    for (int i=0; i<100505; i++)
    {
        x[i] = NULL;
        y[i] = NULL;
        a[i] = 0;
        b[i] = 0;

    }
}





void wypisz()
{
    int dlugosc;
    int calk = 0;

    int reszta = 0;
    int suma[100505];

    cin >> x;
    cin >> y;

    if (x[0]=='0' && y[0]=='0')
    {
        cout << "0" << endl;
        return;
    }

    reversionA();
    reversionB();



    for (int i = 0; i<=100505; i++)
    {
        suma[i] = 0;
    }

    for (int i = 100505; i>=0; i--)
    {
        suma[i-1] = a[i] + b[i] + calk;
        calk = suma[i-1]/10;
        reszta = suma[i-1]%10;
        suma[i-1] = reszta;
    }


    for (int i=0; i<=100505; i++)
    {
        if (suma[i]!=0)
        {
           // cout << i << endl << endl;
            for (int k=i; k<=100504; k++)
            {
                cout << suma[k];
            }
            cout << endl;
            zeruj();
            break;
        }
    }


}


int main()
{
    int n = 0;
    cin >> n;

    for (int i=0; i<n; i++)
    {
        wypisz();
    }
}
