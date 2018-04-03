#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

void doIt()
{
    int n,k,l;
    int element,wieksza,mniejsza;
    bool czyzrobione = false;
    int ostatnia;
    int pierwsza;
    int tab[100000];
    set <int> s;
    cin >> n;
    while(n--)
    {
        cin >> l;
        s.insert(l);
    }


    k = 23002321;
    for (int i=-1; i<k; i++)
    {
        if (i==-1)
        {
            cin >> k;
        }
        else
        {
            cin >> tab[i];
        }

    }


    for (int i=0; i<k; i++)
    {
        set<int>::iterator x = s.lower_bound(tab[i]);
        set<int>::iterator q = s.begin();
        set<int>::iterator w = s.end();
        wieksza = *x;
        mniejsza = *(--x);
        pierwsza = *q;
        ostatnia = *(--w);
      //  set<int>::iterator itBegin = s.begin(tab[i]);
     //   poczatek = *itBegin;

        if (wieksza==pierwsza)
        {
            cout << wieksza << " ";
        }

        if (mniejsza==ostatnia)
        {
            cout << mniejsza << " ";
        }


        if (mniejsza!=ostatnia && wieksza!=pierwsza)
        {
            if (wieksza-tab[i]<tab[i]-mniejsza)
            {
                cout << wieksza << " ";
            }

            if (wieksza-tab[i]>=tab[i]-mniejsza)
            {
                cout << mniejsza << " ";
            }
        }

}
}



int main ()
{
    int z;
    cin >> z;
    while (z--)
    {
        doIt();
        cout << endl;
    }
}



