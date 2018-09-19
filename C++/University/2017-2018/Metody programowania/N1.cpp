#include <iostream>
#include <vector>
#define MAX 50005
#include <stack>

using namespace std;

vector<vector<int>> G(MAX);

vector<vector<int>> T(MAX);
stack<int> s;
bool visited[MAX];
int scc[MAX];
int sizesScc[MAX];
int n, m;

void dfs(int w)
{
    visited[w] = true;
    for (unsigned int x = 0; x < G[w].size(); x++)
    {
        int somsiad = G[w][x];
        if (!visited[somsiad])
        {
            dfs(somsiad);
        }
    }
    s.push(w);
}

void sccDfs(int w, int number)
{
    visited[w] = true;
    scc[w] = number;
    sizesScc[number]++;
    for (unsigned int x = 0; x < T[w].size(); x++)
    {
        int somsiad = T[w][x];
        if (!visited[somsiad])
        {
            sccDfs(somsiad, number);
        }
    }
}

void clearVisited()
{
    for (int x = 0; x < n + 3; x++)
    {
        visited[x] = false;
    }
}

void clear()
{
    clearVisited();
    while (!s.empty())
        s.pop();
    for (int x=0; x<n+3; x++)
    {
        G[x].clear();
        T[x].clear();
        sizesScc[x] = 0;
        scc[x] = -1;
    }
}

void doIt()
{
    cin >> n >> m;
    clear();
    for (int x = 0; x < m; x++)
    {
        int a, b, k;
        cin >> a >> b >> k;
        G[b].push_back(a);
        T[a].push_back(b);
    }
    for (int x = 1; x <= n; x++)
    {
        if (!visited[x])
            dfs(x);
    }
    clearVisited();
    for (int x = 1; !s.empty();)
    {
        int w = s.top();
        s.pop();
        if (!visited[w])
        {
            sccDfs(w, x++);
        }
    }
    for (int x=1; x<=n; x++)
    {
        cout << sizesScc[scc[x]]-1 << " ";
    }
    cout << endl;
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