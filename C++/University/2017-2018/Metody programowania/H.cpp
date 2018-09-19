#include <iostream>
#define child first
#define sibling second

#ifdef DEBUG
#define MAX 100
#else
#define MAX 1000005
#endif

#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> G(MAX);
pair<int, int> nodes[MAX];
bool visited[MAX];
int dist[MAX];
int previous[MAX];
int n;

void clearVisited()
{
    for (int x = 0; x < n; x++)
    {
        visited[x] = false;
    }
}

void srednica()
{
    clearVisited();
    queue<int> q;
    q.push(0);
    int node;
    while (!q.empty())
    {
        node = q.front();
        visited[node] = true;
        q.pop();
        for (int x = 0; x < G[node].size(); x++)
        {
            int somsiad = G[node][x];
            if (!visited[somsiad])
                q.push(somsiad);
        }
    }

    clearVisited();

    int secondNode;
    q.push(node);
    dist[node] = 0;
    while (!q.empty())
    {
        secondNode = q.front();
        visited[secondNode] = true;

        q.pop();
        for (int x = 0; x < G[secondNode].size(); x++)
        {
            int somsiad = G[secondNode][x];
            if (!visited[somsiad])
            {
                dist[somsiad] = dist[secondNode] + 1;
                previous[somsiad] = secondNode;
                q.push(somsiad);
            }
        }
    }

    clearVisited();
    int dlugoscSrednicy = dist[secondNode];

    int currentNode = secondNode;
    vector<int> results;
    previous[node] = -1;

    while (currentNode != -1)
    {
        if ((dist[currentNode] == dlugoscSrednicy / 2) ||
            (dlugoscSrednicy % 2 == 1 && dlugoscSrednicy / 2 + 1 == dist[currentNode]))
        {
            results.push_back(currentNode);
        }
        currentNode = previous[currentNode];
    }

    if (results.size() == 2)
    {
        cout << min(results[0], results[1]) << " " << max(results[0], results[1]);
    }
    else
    {
        cout << results[0];
    }
    cout << endl;
}

void doIt()
{
    cin >> n;
    for (int x = 0; x < n; x++)
    {
        G[x].clear();
    }
    for (int x = 0; x < n; x++)
    {
        cin >> nodes[x].child >> nodes[x].sibling;
    }

    for (int x = 0; x < n; x++)
    {
        int current = nodes[x].child;
        while (current != -1)
        {
            G[x].push_back(current);
            G[current].push_back(x);
            current = nodes[current].sibling;
        }
    }
    srednica();
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