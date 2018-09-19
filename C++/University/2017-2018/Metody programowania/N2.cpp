#include <iostream>
#include <vector>
#define MAX 100005
#include <stack>

using namespace std;

vector<vector<int>> G(MAX);
vector<vector<int>> T(MAX);
stack<int> s;
bool visited[MAX];
int scc[MAX];
int sizesScc[MAX];
//vector<vector<int>> test(MAX);
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
  //  test[number].push_back(w);
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
    for (int x = 0; x < 2 * n + 3; x++)
    {
        visited[x] = false;
    }
}

void clear()
{
    clearVisited();
    while (!s.empty())
        s.pop();
    for (int x = 0; x < 2 * n + 3; x++)
    {
   //     test[x].clear();
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
        if (k == 0)
        {
            G[b].push_back(a);
            G[a + n].push_back(b + n);

            T[a].push_back(b);
            T[b + n].push_back(a + n);
        }
        else
        {
            G[b].push_back(a + n);
            G[a + n].push_back(b);

            T[a + n].push_back(b);
            T[b].push_back(a + n);
        }
    }
    for (int x = 1; x <= 2 * n; x++)
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
    // for (int x = 1; x <= 2 * n; x++)
    // {
    //     if (test[x].empty())
    //     {
    //         break;
    //     }
    //     cout << x << ": ";
    //     for (int y = 0; y < test[x].size(); y++)
    //     {
    //         cout << test[x][y] << " ";
    //     }
    //     cout << endl;
    // }

    for (int x=1; x<=n; x++)
    {
        if (scc[x]==scc[x+n]) {
            sizesScc[scc[x]]--;
        }
    }
    for (int x = 1; x <= n; x++)
    {
        cout << sizesScc[scc[x]] - 1 << " ";
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