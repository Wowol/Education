#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Liczba
{
    int value;
    bool poczatek;
    int indexProstej;
};


const int MAX = 1e6;
int prosta[MAX];
int stan[MAX];
int n;


bool operator <(const Liczba& x, const Liczba& y)
{
    if(x.value == y.value && x.poczatek == y.poczatek) return false;
    if (x.value==y.value)
    {
        if (x.poczatek)
        {
            return true;
        }
    }
    return x.value < y.value;
}



void doIt()
{
    cin >> n;
    int left;
    int aktualny_stan = 0;
    int right;
    int number;
    for (int x=0; x< n*2; x++)
    {
        stan[x] = 0;
        prosta[x] = 0;
    }
    vector<Liczba> V;
    for (int x=0; x<n; x++)
    {
        cin >> left >> right >> number;
        prosta[x] = number;
        Liczba l;
        l.value = left;
        l.indexProstej = x;
        l.poczatek = true;

        Liczba p;
        p.value = right;
        p.indexProstej = x;
        p.poczatek = false;

        V.push_back(l);
        V.push_back(p);
    }


    sort(V.begin(), V.end());
    for (int x=0; x<n*2; x++)
    {
        Liczba a = V[x];
        if (a.poczatek)
        {
            stan[a.indexProstej] = aktualny_stan;
        }
        else
        {
            int num = prosta[a.indexProstej];
            int z = stan[a.indexProstej];
            int ileProstychZostaloZrobionychNaTymPrzedziale = aktualny_stan-z;
            int y = num-ileProstychZostaloZrobionychNaTymPrzedziale;
            if (y>0)
            {
                aktualny_stan+=y;
            }

        }
    }
    cout << aktualny_stan << endl;

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
