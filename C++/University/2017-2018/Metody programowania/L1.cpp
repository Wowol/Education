#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 100009
using namespace std;

int n;
int m;

vector<vector<int>> G(MAX);
vector<int> topoSort;
int ranks[MAX];
int group[MAX];
int lab[MAX];
bool visited[MAX];

void setFirstGroup(int q)
{
    for (int x = 0; x < n; x++)
    {
        int w = topoSort[x];
        if (lab[w] == lab[q])
            group[w] = group[q];
        else   
            group[w] = !group[q];
    }
}

int calculate(int q)
{
    int w = topoSort[0];
    group[w] = q;
    setFirstGroup(w);
    for (int x = 0; x < n; x++)
    {
        w = topoSort[x];
        for (int y = 0; y < G[w].size(); y++)
        {
            int somsiad = G[w][y];
            group[somsiad] = max(group[somsiad], group[w] + (lab[somsiad] != lab[w]));
        }
    }
    int result = -1;
    for (int x = 1; x <= n; x++)
    {
        result = max(result, group[x]);
    }
    return result;
}

void L1()
{
    queue<int> q;
    for (int x = 1; x <= n; x++)
    {
        if (ranks[x] == 0)
        {
            q.push(x);
        }
    }
    while (!q.empty())
    {
        int w = q.front();
        q.pop();
        topoSort.push_back(w);
        for (int x = 0; x < G[w].size(); x++)
        {
            int somsiad = G[w][x];
            if (ranks[somsiad] > 0)
            {
                ranks[somsiad]--;
                if (ranks[somsiad] == 0)
                {
                    q.push(somsiad);
                }
            }
        }
    }
}

void dfs(int w)
{
    for (int x = 0; x < G[w].size(); x++)
    {
        int somsiad = G[w][x];
        if (!visited[somsiad])
        {
            visited[somsiad] = true;
            dfs(somsiad);
        }
    }
    topoSort.push_back(w);
}

void L2()
{
    for (int x = 1; x <= n; x++)
    {
        if (!visited[x])
        {
            visited[x] = true;
            dfs(x);
        }
    }
    reverse(topoSort.begin(), topoSort.end());
}

void clear()
{
    for (int x = 0; x <= n + 2; x++)
    {
        G[x].clear();
        ranks[x] = 0;
        visited[x] = false;
    }
    topoSort.clear();
}

void doIt()
{
    cin >> n >> m;
    clear();
    for (int x = 1; x <= n; x++)
    {
        cin >> lab[x];
    }
    for (int x = 0; x < m; x++)
    {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        ranks[b]++;
    }
    L1();
    //L2();
    for (int x = 0; x < n; x++)
    {
        cout << topoSort[x] << " ";
    }
    cout << endl;

    cout << min(calculate(0), calculate(1)) << endl;
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