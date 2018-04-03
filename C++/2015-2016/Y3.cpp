#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Kolo
{
    int x;
    int y;
    int r;
};
const int MAX = 10005;
vector< vector<int> > G(MAX);

pair<int, int> vv[MAX];
bool clockOrNot[MAX];
bool visited[MAX];
vector<Kolo> V;

void DFS(int n, pair<int, int> velo, bool clock)
{
    Kolo stare = V[n];
    if (velo.first==0 || velo.second == 0)
    {
        cout << "ASD";
        exit(0);
    }
    int nwd = __gcd(velo.first, velo.second);
    velo.first /= nwd;
    velo.second /= nwd;
    vv[n] = velo;
    clockOrNot[n] = clock;
    int s = G[n].size();
    for (int x=0; x<s; x++)
    {
        int sasiad = G[n][x];
        if (!visited[sasiad])
        {
            visited[sasiad] = true;
            Kolo noweKolo = V[sasiad];
            pair<int, int> noweVelo;
            noweVelo.first = velo.first*stare.r;
            noweVelo.second = velo.second*noweKolo.r;
            DFS(sasiad, noweVelo, !clock);
        }
    }
}


int ccc(int n)
{
    for (int x=0; x<=n; x++)
    {
        G[x].clear();
        vv[x].first = 0;
        vv[x].second = 0;
        visited[x] = false;

    }
    V.clear();
}



void doIt()
{
    int n;
    cin >> n;

    ccc(n);


    for (int x=0; x<n; x++)
    {
        visited[x] = false;
        Kolo k;
        cin >> k.x >> k.y >> k.r;
        V.push_back(k);
    }

    for (int x=0; x<n; x++)
    {
        for (int y=x+1; y<n; y++)
        {
            if ((V[x].x-V[y].x)*(V[x].x-V[y].x)+(V[x].y-V[y].y)*(V[x].y-V[y].y)==(V[x].r+V[y].r)*(V[x].r+V[y].r))
            {
                G[x].push_back(y);
                G[y].push_back(x);
            }
        }
    }

    DFS(0, make_pair(1, 1), true);

    for (int x=0; x<n; x++)
    {
        string c;
        if (clockOrNot[x]==true)
        {
            c = " clockwise";
        }
        else
        {
            c = " counterclockwise";
        }
        if (vv[x].second==1)
        {
            cout << vv[x].first << c << endl;
            continue;
        }
        if (vv[x].second!=0)
        {
            cout << vv[x].first << "/" << vv[x].second << c << endl;
            continue;
        }
        cout << "not moving" << endl;
    }


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
