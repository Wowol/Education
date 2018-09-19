#include <iostream>
#define MAX 10000005
#define INFINITY 1000000005;
#include <cstdlib>

using namespace std;
int tab[MAX];
int n, k;
int szukaj(int check)
{
    int tmp = 0;
    int out = 0;
    for (int x=0; x<n; x++)
    {
        tmp+=tab[x];
        if (tmp>check)
        {
            tmp=tab[x];
            if (tmp>check)
            {
                return k+1;
            }
            out++;
        }
    }
  //  if (tmp==check) return k;
    if (tmp!=0) out++;
    return out;

}

int doIt()
{
    cin >> n >> k;
    int suma = 0;
    int a = 0;
    for (int x=0; x<n; x++)
    {
        cin >> a;
        suma += a;
        tab[x] = a;
    }

    int nowe = 0;
    int check = suma/2;
    int stare = 0;
    int dobry = INFINITY;
    int wynik = 0;
    while (stare!=check)
    {
        wynik = szukaj(check);
        if (wynik>k)
        {
            nowe = check;
            if (stare>check)
            {
                check = (stare+check)/2;
            }
            else check = check+(check-((stare+check)/2));
            stare = nowe;
        }
        if (wynik<=k)
        {
            dobry = min(dobry, check);
            nowe = check;
            if (stare>check)
            {
                check = check-((stare+check)/2-check);
                //check = stare-(stare+check)/2;
            }
            else check = (stare+check)/2;
            stare = nowe;
        }
    }
    cout << dobry << endl;
}

int main()
{
   int z;
   cin >> z;
   while (z--)
   {
       doIt();
   }
}
