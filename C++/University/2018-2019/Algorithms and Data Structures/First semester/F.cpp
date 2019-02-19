#include <iostream>
#include <vector>

#define MAX 5000006

using namespace std;

vector<vector<int>> graph(MAX);
vector<vector<int>> reversed(MAX);

int maxPathToVertex[MAX];
int maxPathFromVertex[MAX];

int n;

void clear()
{
    for (int x = 0; x < n + 2; x++)
    {
        maxPathFromVertex[x] = 0;
        maxPathToVertex[x] = 0;
        graph[x].clear();
        reversed[x].clear();
    }
}

int calculateMaxPathToVertex(int w)
{
    if (maxPathToVertex[w] != 0)
    {
        return maxPathToVertex[w];
    }
    for (int x = 0; x < graph[w].size(); x++)
    {
        int neighbour = graph[w][x];
        maxPathToVertex[w] = max(maxPathToVertex[w], calculateMaxPathToVertex(neighbour));
    }
    maxPathToVertex[w]++;
    return maxPathToVertex[w];
}

int calculateMaxPathFromVertex(int w)
{
    if (maxPathFromVertex[w] != 0)
    {
        return maxPathFromVertex[w];
    }
    for (int x = 0; x < reversed[w].size(); x++)
    {
        int neighbour = reversed[w][x];
        maxPathFromVertex[w] = max(maxPathFromVertex[w], calculateMaxPathFromVertex(neighbour));
    }
    maxPathFromVertex[w]++;
    return maxPathFromVertex[w];
}

void doIt()
{
    int m;
    cin >> n >> m;

    clear();

    for (int x = 0; x < m; x++)
    {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        reversed[b].push_back(a);
    }

    for (int x = 1; x <= n; x++)
    {
        if (maxPathFromVertex[x] == 0)
        {
            calculateMaxPathFromVertex(x);
        }

        if (maxPathToVertex[x] == 0)
        {
            calculateMaxPathToVertex(x);
        }
    }

    for (int x = 1; x <= n; x++)
    {
        cout << maxPathToVertex[x] + maxPathFromVertex[x] - 1 << " ";
    }
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