#include <iostream>

using namespace std;

int tab[100000];
int t[100000];  // Tablica pomocnicza

void Sortowanie(int left, int srodkowy, int prawy)
{
    for (int z=left; z<=prawy; z++) t[z] = tab[z];
    int i = left;
    int j = srodkowy+1;
    int o = left;


    while(i<=srodkowy && j<=prawy)
    {
        if (t[i]<=t[j])
        {
            tab[o]=t[i];
            i++;
        }
        else
        {
            tab[o]=t[j];
            j++;
        }

        o++;

    }
    while (i<=srodkowy) tab[o++]=t[i++];
}



void mergesort(int a, int b)
{
    int srodek = (a+b)/2;
    if (a!=b)
    {
        mergesort(a,srodek);
        mergesort(srodek+1, b);
        Sortowanie(a,srodek,b);
    }
}

int main()
{
    int ilosc = 0;
    int n,h;
    cin >> n  >> h;
    for (int i=0; i<n; i++)
    {
        cin >> tab[i];
    }

    mergesort(0, n-1);
    int a = 0;

    for (int i=n-1; i>=0; i--)
    {
         if (i<=a)
         {
            break;
         }

         if (tab[i]+tab[a]<=h)
         {
             a++;
         }
    }
    cout << n-a;

}

