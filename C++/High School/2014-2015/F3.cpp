#include <iostream>

using namespace std;

int tab[1000000];
int poziom[1000000];
int konce[1000000];
int n;

int findMax(int pocz, int koniec)
{
    int k = -1;
    int z = 0;
    for (int x=pocz; x<=koniec; x++)
    {
        if (tab[x]>k)
        {
            k = tab[x];
            z = x;
        }
    }
    return z;

}

int findParent(int x, int stopien)
{
    int kolejnoscWSwoimPrzedziale = x-konce[stopien-1];
    int polowa = kolejnoscWSwoimPrzedziale/2;
    int koniec = konce[stopien];
    int modulo = kolejnoscWSwoimPrzedziale%2;
    return (polowa+koniec+modulo);
}

void createTree()
{
    int actuall = n;
    int stary = 0;
    int a = 1;
    int wCholereStary = 0;

    while (wCholereStary+1!=actuall)
    {
         poziom[a] = actuall-stary;
         konce[a] = actuall;
        for (int x=stary+1; x<=actuall; x++)
        {
            if ((x-stary)%2==0)
            {
                int rodzic = findParent(x, a);
                tab[rodzic] = max(tab[x], tab[x-1]);
            }

            if (x==actuall && (x-stary)%2==1)
            {
                int rodzic = findParent(x+1, a);
                tab[rodzic] = tab[x];
            }
        }


        a++;


         stary = actuall;
        actuall = actuall+(actuall-wCholereStary)/2+(actuall-wCholereStary)%2;
        wCholereStary = stary;

    }

}

bool czyLewy(int index, int stopien)
{
    if ((index-konce[stopien-1])%2==1) return true;
    return false;
}

int szukaj(int pocz, int koniec, int stopien, int liczbaPocz, int liczbaKon)
{
    int nowyStopien = stopien+1;
    int staryPocz = pocz;
    int staryKoc = koniec;

    pocz = findParent(pocz, stopien);
    koniec = findParent(koniec, stopien);

    if (pocz==koniec)
    {
        return max(liczbaPocz, liczbaKon);
    }

    bool czyPoczJestLewy = czyLewy(staryPocz, stopien);
    bool czyKoniecJestLewy = czyLewy(staryKoc, stopien);


    if (czyPoczJestLewy)
    {
        liczbaPocz = max(liczbaPocz, tab[staryPocz+1]); //tab[pocz];
    }
    if (!czyKoniecJestLewy)
    {
        liczbaKon = max(liczbaKon, tab[staryKoc-1]); //tab[koniec];
    }

    szukaj(pocz, koniec, nowyStopien, liczbaPocz, liczbaKon);

}


int domino(int poczatek, int koniec)
{
    if(poczatek>koniec)
    {
        return 0;
    }

    int mid = findMax(poczatek, koniec);
  //  int mid=szukaj(poczatek, koniec, 1, tab[poczatek], tab[koniec]);
    return min(domino(poczatek, mid-1), domino(mid+1, koniec)) + 1;

}

int doIt()
{
    cin >> n;
    poziom[0] = 0;
    konce[0] = 0;
    for (int x=1; x<=n; x++)
    {
        cin >> tab[x];
    }
    int a = n;

    createTree();
    cout << domino(1, a);

}

int main()
{
    doIt();
}
