#include <vector>
#include <iostream>
#define MAX 200007

using namespace std;

typedef long long ull;

int n;
int costs[MAX];
vector<vector<int>> graph(MAX);
ull result[MAX][2]; // 0 - nie zawiera sie,   1 - zawiera
int reconstructed[MAX];

ull countResult(int vertex, int withOrWithoutYou, int fromWho)
{
    if (result[vertex][withOrWithoutYou] != -1)
    {
        return result[vertex][withOrWithoutYou];
    }
    if (withOrWithoutYou == 0)
    {
        ull sum = 0;
        for (int x = 0; x < graph[vertex].size(); x++)
        {
            int somsiad = graph[vertex][x];
            if (somsiad != fromWho)
                sum += countResult(somsiad, 1, vertex);
        }
        result[vertex][0] = sum;
        return sum;
    }
    else
    {
        ull sum = costs[vertex];
        for (int x = 0; x < graph[vertex].size(); x++)
        {
            int somsiad = graph[vertex][x];
            if (somsiad != fromWho)
                sum += min(countResult(somsiad, 1, vertex), countResult(somsiad, 0, vertex));
        }
        result[vertex][1] = sum;
        return sum;
    }
}

void reconstructResult(int vertex, int fromWho)
{
    if (reconstructed[vertex] == -1)
    {
        if (result[vertex][0] < result[vertex][1])
        {
            reconstructed[vertex] = 0;
        }
        else
        {
            reconstructed[vertex] = 1;
        }
    }
    if (reconstructed[vertex] == 0)
    {
        for (int x = 0; x < graph[vertex].size(); x++)
        {
            int somsiad = graph[vertex][x];
            if (somsiad != fromWho)
            {
                reconstructed[somsiad] = 1;
                reconstructResult(somsiad, vertex);
            }
        }
    }
    else
    {
        for (int x = 0; x < graph[vertex].size(); x++)
        {
            int somsiad = graph[vertex][x];
            if (somsiad != fromWho)
            {
                reconstructResult(somsiad, vertex);
            }
        }
    }
}

void clean()
{
    for (int x = 0; x < n + 3; x++)
    {
        graph[x].clear();
        result[x][0] = -1;
        reconstructed[x] = -1;
        result[x][1] = -1;
    }
}

void doIt()
{
    cin >> n;
    clean();
    for (int x = 1; x <= n; x++)
    {
        cin >> costs[x];
    }
    for (int x = 0; x < n - 1; x++)
    {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    cout << min(countResult(1, 0, -1), countResult(1, 1, -1)) << endl;
    reconstructResult(1, -1);
    for (int x = 1; x <= n; x++)
    {
        cout << reconstructed[x];
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