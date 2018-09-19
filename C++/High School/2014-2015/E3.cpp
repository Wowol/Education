#include <iostream>
#include <vector>
#define MAX 10005

using namespace std;
vector< vector< pair<int,int> > > G(MAX);
int d[MAX];
int p[MAX];
int m = MAX-3;
int n = MAX-3;


bool sprawdz(int x, int pocz)
{
    if (p[x]==pocz)
    {
        return true;
    }
    if (p[x]==-1)
    {
        return false;
    }
    else
    {
        return sprawdz(p[x], pocz);
    }
}

void bellman(int startowy, int n, int koncowy)
{
    bool wynik = true;
   /* for(int x=0; x<MAX; x++)
    {
        d[x]=1000000;
        p[x] = -1;
    }*/

    d[startowy] = 0;

    for (int i=1; i<n; i++)
    {
        for (int x=1; x<=n; x++)
        {
            for (int y=0; y<G[x].size(); y++)
            {
                int ktory = G[x][y].first;
                int cena = G[x][y].second;
                if (d[ktory]>d[x] + cena)
                {
                    d[ktory] = d[x] + cena;
                    p[ktory] = x;
                }

            }
        }
    }


    for (int x=1; x<=n; x++)
    {
        for (int y=0; y<G[x].size(); y++)
        {
            int ktory = G[x][y].first;
            int cena = G[x][y].second;
            if (d[ktory]>d[x] + cena)
            {
                cout << "Luka w systemie bankowym!" << endl;
                return;
            }
        }
    }

    if (sprawdz(koncowy, startowy))
    {
        cout << "Minimalny koszt: " << d[koncowy] << endl;
    }
    else
    {
        cout << "Bank niedostepny!" << endl;
    }



}


void doIt()
{
    int a, b, c;
    int z, d;
    cin >> n >> m;
    for (int i=0; i<m; i++)
    {
        cin >> a >> b >> c;
        G[a].push_back(make_pair(b,c));
    }

    cin >> z >> d;

    bellman(z, n, d);
}


int main()
{
    int l;
    cin >> l;
    while (l--)
    {
        for (int x=0; x<n+1; x++)
        {
            p[x]=-1;
            d[x]=1000000;
            G[x].clear();
        }
        doIt();
    }
}
