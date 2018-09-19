#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;


unsigned long long nwd (unsigned long long a, int b)
{
    while (true)
    {

        if (a!=0 && b!=0)
        {
            if (a>b)
            {
                a = a%b;
            }


            else
            {
                b = b%a;
            }
        }

        if (a==0 || b==0)
        {
            return a+b;
        }
    }
}

int doIt()
{
    int ilosc;
    int a;
    unsigned long long suma = 0;
    double srednia;
    int tab[500001];
    ilosc = 500001;
    for (int i=-1; i<ilosc; i++)
    {
        if (i==-1)
        {
            cin >> ilosc;
        }
        else
        {
            cin >> a;
            tab[i] = a;
            suma += a;
        }

    }

    double aktualnailosc = ilosc;
    srednia = double(suma)/ilosc;
    double starasuma = suma;
    double starasriedna = srednia;
    int aktualna;

    sort(tab, tab+ilosc);



    for (int x=ilosc-1; x>0; x--)
    {
        aktualna = tab[x];
        if (tab[x]>srednia && tab[x-1]==tab[x])
        {
            aktualnailosc--;
            suma = suma-tab[x];
            srednia = suma/aktualnailosc;
        }
    }

    int dzielnik = nwd(suma,aktualnailosc);
    cout << suma/dzielnik << "/" << aktualnailosc/dzielnik << " ";


    suma = starasuma;
    srednia = starasriedna;
    aktualnailosc = ilosc;

    for (int x=0; x<ilosc; x++)
    {
        if (tab[x]<srednia && tab[x+1]==tab[x])
        {
            aktualnailosc--;
            suma = suma-tab[x];
            srednia = suma/aktualnailosc;
        }
    }

    dzielnik = nwd(suma,aktualnailosc);
    cout << suma/dzielnik << "/" << aktualnailosc/dzielnik << " " << endl;
}



int main()
{
    int q;
    cin >> q;
    while (q--)
    {
        doIt();
    }
}


