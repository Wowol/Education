#include <iostream>
#include <vector>
#define MAX 1000005
#include <queue>
using namespace std;

int n;

vector<vector<int>> G(MAX);
int distanceOne[MAX];
int distanceTwo[MAX];
int distanceThree[MAX];
vector<pair<int, int>> chainEdges;

int bfs(int source, int dist[])
{
    bool visited[MAX];
    for (int x = 0; x <= n; x++)
    {
        visited[x] = false;
    }
    queue<int> q;
    q.push(source);
    dist[source] = 0;
    visited[source] = true;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        for (int x = 0; x < G[node].size(); x++)
        {
            int somsiad = G[node][x];
            if (visited[somsiad])
                continue;
            visited[somsiad] = true;
            dist[somsiad] = dist[node] + 1;
            q.push(somsiad);
        }
    }
}

void clear()
{
    for (int x = 0; x <= n + 1; x++)
    {
        G[x].clear();
        distanceOne[x] = -1;
        distanceTwo[x] = -1;
        distanceThree[x] = -1;
    }
    chainEdges.clear();
}

void doIt()
{
    int m, base, target2, target3;
    cin >> n >> m >> base >> target2 >> target3;
    clear();

    for (int x = 0; x < m; x++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if (c == 0)
        {
            G[a].push_back(b);
            G[b].push_back(a);
        }
        else
        {
            chainEdges.push_back(make_pair(a, b));
        }
    }
    bfs(base, distanceOne);
    bfs(target2, distanceTwo);
    bfs(target3, distanceThree);
    if (distanceOne[target2] == -1)
    {
        cout << "BRAK";
    }
    else
        cout << distanceOne[target2];
    cout << " ";

    int currentMin = INT32_MAX;
    for (int x = 0; x < chainEdges.size(); x++)
    {
        int a = chainEdges[x].first;
        int b = chainEdges[x].second;
        if (distanceOne[a] != -1 && distanceTwo[b] != -1)
        {
            currentMin = min(currentMin, distanceOne[a] + distanceTwo[b] + 1);
        }
        if (distanceOne[b] != -1 && distanceTwo[a] != -1)
        {
            currentMin = min(currentMin, distanceOne[b] + distanceTwo[a] + 1);
        }
    }

    if (currentMin == INT32_MAX)
    {
        cout << "BRAK";
    }
    else
        cout << currentMin;
    cout << endl;





    if (distanceTwo[target3] == -1)
    {
        cout << "BRAK";
    }
    else
        cout << distanceTwo[target3];
    cout << " ";

    currentMin = INT32_MAX;
    for (int x = 0; x < chainEdges.size(); x++)
    {
        int a = chainEdges[x].first;
        int b = chainEdges[x].second;
        if (distanceTwo[a] != -1 && distanceThree[b] != -1)
        {
            currentMin = min(currentMin, distanceTwo[a] + distanceThree[b] + 1);
        }
        if (distanceTwo[b] != -1 && distanceThree[a] != -1)
        {
            currentMin = min(currentMin, distanceTwo[b] + distanceThree[a] + 1);
        }
    }

      if (currentMin == INT32_MAX)
    {
        cout << "BRAK";
    }
    else
        cout << currentMin;
    cout << endl;

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