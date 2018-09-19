#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAX = (1e6)+20;
const int MAX_POTEGA = 21;

vector<vector<int> > G(MAX);
bool odwiedzeni[MAX];
int d[MAX_POTEGA][MAX];
int c = 0;
int iloscDzieciZOjcem[MAX];
int kolejnoscOdwiedzenia[MAX];
int poziom[MAX];
int gdzieJestesmy = 4;

int odl(int a, int b)
{
    return abs(poziom[a]-poziom[b]);
}

void DFS(int a, int p)
{
    odwiedzeni[a] = true;
    poziom[a] = p;
    c++;
    kolejnoscOdwiedzenia[a] = c;

    for (int x=0; x<G[a].size(); x++)
    {
        int syn = G[a][x];
        if (!odwiedzeni[syn])
        {
            d[0][syn]=a;
            DFS(syn, p+1);
        }
    }
    iloscDzieciZOjcem[a] = c+1-kolejnoscOdwiedzenia[a];

}


bool ifChild(int a, int b)
{
    if (kolejnoscOdwiedzenia[a]>=kolejnoscOdwiedzenia[b])
    {
        if (kolejnoscOdwiedzenia[a]<kolejnoscOdwiedzenia[b]+iloscDzieciZOjcem[b])
        {
            return true;
        }
    }
    return false;
}

int lca(int a, int b)
{
    if (ifChild(a, b)) return b;
    if (ifChild(b, a)) return a;

    int j = MAX_POTEGA-1;
    while(j>=0)
    {
        if (ifChild(b, d[j][a]))
        {
            j--;
        }
        else
        {
            a = d[j][a];
        }
    }
    return d[0][a];
}

int udanieSieWStrone(int syn, int ile)
{
    int szukanyPoziom = poziom[syn]-ile;
    for (int x=0; x<MAX_POTEGA; x++)
    {
        int q = poziom[d[x][syn]];
        if (q==szukanyPoziom) return d[x][syn];
        if (szukanyPoziom>q)
        {
            syn = d[x-1][syn];
            x = -1;
        }
    }
}

int zapytanie()
{
    int doKtorego, maxDlugosc;
    cin >> doKtorego >> maxDlugosc;
    if (maxDlugosc==0)
    {
        return gdzieJestesmy;
    }
    int rodzic = lca(doKtorego, gdzieJestesmy);
    int odlOdStarego = odl(rodzic, gdzieJestesmy);
    int odlOdNowego = odl(rodzic, doKtorego);
    int ileMozemyPojscPoRodzicu = 0;
    int ileZNowegoWStroneRodzicaMozemyPojsc = 0;

    if (maxDlugosc<odlOdStarego)
    {
        return udanieSieWStrone(gdzieJestesmy, maxDlugosc);
    }
    if (maxDlugosc==odlOdStarego)
    {
        return rodzic;
    }
    if (maxDlugosc>odlOdStarego)
    {
        ileMozemyPojscPoRodzicu = maxDlugosc-odlOdStarego;
        if (ileMozemyPojscPoRodzicu>=odlOdNowego)
        {
            return doKtorego;
        }
        else
        {
            ileZNowegoWStroneRodzicaMozemyPojsc = odlOdNowego-ileMozemyPojscPoRodzicu;
            return udanieSieWStrone(doKtorego, ileZNowegoWStroneRodzicaMozemyPojsc);
        }
    }

}

int doIt()
{
    int n, m, k;
    cin >> n >> m >> k;
    gdzieJestesmy = m;

    for (int x=0; x<=n+1; x++)
    {
        odwiedzeni[x] = false;
        G[x].clear();
    }

    c = 0;

    for (int x=0;x<n-1; x++)
    {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    d[0][0] = 0;

    DFS(1, 0);
    for (int i=1; i<MAX_POTEGA; i++)
    {
        for (int x=1; x<=n; x++)
        {
            d[i][x]=d[i-1][d[i-1][x]];
            if (d[i][x]==0) d[i][x]=1;
        }
    }
    d[0][1] = 1;

    for (int q=0; q<k; q++)
    {
        gdzieJestesmy = zapytanie();
        cout << gdzieJestesmy << " ";
    }
    cout << endl;


}


int main()
{
    int ww;
    cin >> ww;
    while (ww--)
    {
        doIt();
    }
}
