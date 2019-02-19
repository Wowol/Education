#include <iostream>
#include <vector>

#define MAX 1000006

using namespace std;

int n;
vector<vector<int>> G(MAX);
bool flagged[MAX];

struct treeData
{
    int result;
    bool haveFree;
};

treeData dfs(int w, int parent)
{
    int currentResult = 0;
    int numbersOfFree = 0;
    for (int x = 0; x < G[w].size(); x++)
    {
        int neighbor = G[w][x];
        if (neighbor != parent)
        {
            treeData childData = dfs(neighbor, w);
            currentResult += childData.result;
            numbersOfFree += childData.haveFree;
        }
    }
    if (flagged[w])
    {
        numbersOfFree++;
    }
    if (numbersOfFree >= 2)
    {
        currentResult++;
        numbersOfFree = 0;
    }
    treeData returnData = {currentResult, numbersOfFree};
    return returnData;
}

void clear()
{
    for (int x = 0; x < n + 3; x++)
    {
        G[x].clear();
        flagged[x] = false;
    }
}

void doIt()
{
    cin >> n;
    clear();
    for (int x = 0; x < n - 1; x++)
    {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    int numberfOfFlagged;
    cin >> numberfOfFlagged;
    for (int x = 0; x < numberfOfFlagged; x++)
    {
        int a;
        cin >> a;
        flagged[a] = true;
    }
    cout << dfs(1, -1).result << endl;
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