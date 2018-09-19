#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

const int MAX = 300005;
int n, m;
int ilosc;


struct punkt
{
    bool poziomy;
    bool poczatek;
    int koniec;
    int x;
    int y;
    int ID;

    bool operator<(const punkt&b) const
    {
        if (x!=b.x) return x<b.x;
        if (poziomy && !b.poziomy && poczatek) return true;
        if (!poziomy && b.poziomy && b.poczatek) return false;

        if (poziomy && !b.poziomy && !poczatek) return false;
        if (!poziomy && b.poziomy && !b.poczatek) return true;
        if (y!=b.y) return y>b.y;
        return poczatek;
    }
};

punkt tab[MAX];

bool czyJestPlus(int m)
{
    set<int> s;
    set<int> zakazane;
    for (int i=0; i<ilosc; i++)
    {
        punkt a = tab[i];

        if (a.poziomy)
        {
            if (a.poczatek)
            {
                if (!zakazane.count(a.ID))
                {
                    s.insert(a.y);
                }
            }

            else
            {
                if (s.count(a.y))
                {
                    s.erase(a.y);
                }
                else
                {
                    zakazane.insert(a.ID);
                }
            }
        }
        else
        {
            if (a.y<=a.koniec)
            {
                int y = *s.lower_bound(a.y);
                if (y>=a.y && y<=a.koniec)
                {
                    return true;
                }
            }
        }
    }

    return false;
}



void doIt()
{

    cin >> n >> m;

    ilosc = 2*m+n;

    for (int x=0; x<n; x++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        punkt p;
        p.ID = x;
        p.poziomy = false;

        p.x = a;
        p.y = b;
        p.koniec = b+c;
        tab[x] = p;
    }

    int maks = 0;

    for (int x=0; x<2*m; x++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        punkt p;
        p.ID = x+n;
        p.poziomy = true;
        p.poczatek = true;
        p.x = a;
        p.y = b;
        p.koniec = a+c;
        tab[x+n] = p;
        x++;

        p.poczatek = false;
        p.x = a+c;
        p.y = b;
        p.koniec = a;
        tab[x+n] = p;

        maks = max(maks, c);

    }

  //  cout << endl;
    sort(tab, tab+ilosc);

  /*  for (int x=0; x<ilosc; x++)
    {
        cout << tab[x].x << " ";
    }*/

    int left = 0;
    int right = maks;
    int mid = maks;

    int najwiecej = 0;

    while (true)
    {
        if (left>=right) break; // blad

        mid = (left+right)/2;
        int stary = mid;

        if (right==left+1)
        {
            mid = right;
        }

        for (int i=0; i<ilosc; i++)
        {
            punkt a = tab[i];
            if (a.poziomy)
            {
                if (tab[i].poczatek)
                {
                    tab[i].x+=mid;
                    tab[i].koniec-=mid;
                }
                else
                {
                    tab[i].x-=mid;
                    tab[i].koniec+=mid;
                }
            }
            else
            {
                tab[i].y+=mid;
                tab[i].koniec-=mid;
            }
        }
        sort(tab, tab+ilosc);

        if (czyJestPlus(mid))
        {
            left = mid;
            najwiecej = max(najwiecej, mid);
        }
        else
        {
            right = mid-1;
        }

        for (int i=0; i<ilosc; i++)
        {
            punkt a = tab[i];
            if (a.poziomy)
            {
                if (tab[i].poczatek)
                {
                    tab[i].x-=mid;
                    tab[i].koniec+=mid;
                }
                else
                {
                    tab[i].x+=mid;
                    tab[i].koniec-=mid;
                }
            }
            else
            {
                tab[i].y-=mid;
                tab[i].koniec+=mid;
            }
        }

    }

    cout << najwiecej << endl;
}


int main()
{
    doIt();
}
