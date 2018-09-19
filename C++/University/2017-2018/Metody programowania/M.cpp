#include <iostream>
#include <vector>
#include <set>
#define MAX 50009

using namespace std;

struct Edge
{
    int node;
    bool used = false;
    int theOtherOne;
};

int n, m;
vector<vector<Edge>> G(MAX);
int degree[MAX];
vector<int> result;
vector<vector<int>> temp(MAX);

void clear()
{
    for (int x = 0; x < n + 3; x++)
    {
        degree[x] = 0;
        G[x].clear();
        temp[x].clear();
    }
    result.clear();
}

void dfs(int w)
{
    while (!G[w].empty())
    {
        int x = G[w].size() - 1;
        Edge somsiadEdge = G[w][x];
        G[w].pop_back();

        if (!somsiadEdge.used)
        {
            int somsiad = somsiadEdge.node;
            if (G[somsiad].size() > somsiadEdge.theOtherOne)
            {
                G[somsiad][somsiadEdge.theOtherOne].used = true;
            }
            dfs(somsiad);
        }
    }

    result.push_back(w);
}

void doIt()
{
    cin >> n >> m;
    clear();
    for (int x = 0; x < m; x++)
    {
        int a, b;
        cin >> a >> b;
        Edge edge;
        edge.node = b;
        edge.theOtherOne = G[b].size();
        edge.used = false;

        G[a].push_back(edge);

        edge.node = a;
        edge.theOtherOne = G[a].size() - 1;
        edge.used = false;

        G[b].push_back(edge);

        degree[a]++;
        degree[b]++;
    }
    for (int x = 1; x <= n; x++)
    {
        if (degree[x] % 2 == 1)
        {
            Edge edge;
            edge.node = x;
            edge.theOtherOne = G[x].size();
            edge.used = false;
            G[0].push_back(edge);

            edge.node = 0;
            edge.theOtherOne = G[0].size() - 1;
            edge.used = false;
            G[x].push_back(edge);
        }
    }
    if (G[0].size() > 0)
    {
        dfs(0);
    }
    else
    {
        dfs(1);
        result.push_back(0);
    }

    int i = 1;
    int x = 0;
    if (result[0]==0) {
        x = 1;
    }
    for (; x < result.size()-1; x++) // 0 na koncu nie bierzemy
    {
        if (result[x] != 0)
        {
            temp[i].push_back(result[x]);
        }
        else
        {
            i++;
        }
    }

    cout << i << endl;

    for (int x = 1; x <= i; x++)
    {
        if (temp[x].size() == 0)
            continue;
        cout << temp[x].size() << " ";
        for (int y = 0; y < temp[x].size(); y++)
        {
            cout << temp[x][y] << " ";
        }
        cout << endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    int z;
    cin >> z;
    while (z--)
    {
        doIt();
    }
}