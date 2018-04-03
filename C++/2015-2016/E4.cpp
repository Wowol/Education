#include <iostream>
#include <vector>

using namespace std;
const int MAX = 2250003;
const int MALE_MAX = 1505;

vector< vector<int> > G(MALE_MAX);
bool visited[MALE_MAX];
int m1[MALE_MAX];
int m2[MALE_MAX];

bool dfs(int u)
{
    if (u==-1)
    {
        return true;
    }
    if (visited[u])
    {
        return false;
    }
    visited[u] = true;

    for (int v=0; v<G[u].size(); v++)
    {
        int wierzcholek = G[u][v];
        if (dfs(m2[wierzcholek]))
        {
            m1[u] = wierzcholek;
            m2[wierzcholek] = u;
            return true;
        }
    }
    return false;
}

void doIt()
{
    int n, m;
    cin >> n >> m;

    for (int x=1; x<=n; x++)
    {
        m1[x] = -1;
        m2[x] = -1;
        G[x].clear();
    }

    for (int x=0; x<m; x++)
    {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
    }

    int licznik = 0;

    while(true)
    {
        for (int x=0; x<=n; x++)
        {
            visited[x] = false;
        }
        bool ok = false;
        for (int x=1; x<=n; x++)
        {
            if (m1[x]==-1)
            {
                if (dfs(x))
                {
                    ok = true;
                    licznik++;
                    if (licznik==n)
                    {
                        cout << "TAK" << endl;
                        return;
                    }
                }
            }
        }
        if (!ok)
        {
            cout << "NIE" << endl;
            return;
        }

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
