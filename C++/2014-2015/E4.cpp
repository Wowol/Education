#include <iostream>
#include <map>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <queue>
#include <vector>
#define MAX 405
#define INFINITY 2838233;
using namespace std;
vector <vector < pair<int, int> > > G(MAX);
priority_queue< pair<int, int> > kolejka;
int d[MAX];

int* dijkstra(int q)
{
    kolejka.push(make_pair(0, q));
    d[q]=0;
    while (!kolejka.empty())
    {
        int u = kolejka.top().second;
        kolejka.pop();
        int z = G[u].size();
        for (int x=0; x<z; x++)
        {
            int wierz = G[u][x].first;
            int odl = G[u][x].second;

            if (d[u]+odl<d[wierz])
            {
                d[wierz]=d[u]+odl;
                kolejka.push(make_pair(odl*-1, wierz));
            }
        }
    }

    return d;

}


int Mapa()
{
    map<string, int> mapa;
    map<int, string> odwrotnaMapa;
    int n;
    string miasto;
    cin >> n;

    for (int x=0; x<=n; x++)
    {
        d[x] = INFINITY;
        G[x].clear();
    }

    for (int x=0; x<n; x++)
    {
        cin >> miasto;
        mapa[miasto]=x;
        odwrotnaMapa[x]=miasto;
    }
    int k;
    string drugieMiasto;
    int odl;
    cin >> k;
    for (int x=0; x<k; x++)
    {
        cin >> miasto >> drugieMiasto >> odl;
        G[mapa[miasto]].push_back(pair<int, int>(mapa[drugieMiasto], odl));
        G[mapa[drugieMiasto]].push_back(pair<int, int>(mapa[miasto], odl));
    }
    cout<<setw(12)<<" ";
    for (int x=0; x<n; x++)
    {
        cout<<setw(12)<<odwrotnaMapa[x];
    }

    cout << endl;

    for (int x=0; x<n; x++)
    {
        cout <<setw(12)<<odwrotnaMapa[x];
        dijkstra(x);
        for (int i=0; i<n; i++)
        {
            cout << setw(12) << d[i];
            d[i] = INFINITY;
        }
        cout << endl;
        while (!kolejka.empty())
        {
            kolejka.pop();
        }

    }

    mapa.clear();
    odwrotnaMapa.clear();



}

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
   /*     for (int x=0; x<=; x++)
        {
            d[x] = INFINITY;
            G[x].clear();
        }*/
        Mapa();
    }
}
