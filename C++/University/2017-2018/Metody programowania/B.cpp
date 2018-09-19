#include <iostream>
#define MAX 2005

using namespace std;

int map[MAX][MAX];
int xSize, ySize, k;
int result = 0;

void dfs(int y, int x, int oldest, bool visited[MAX][MAX])
{
    visited[y][x] = true;
    result++;
    if (result == k)
        return;

    if (y != 1 && !visited[y - 1][x] && map[y - 1][x] <= oldest)
    {
        dfs(y - 1, x, oldest, visited);
    }
    if (result == k)
        return;

    if (y != ySize && !visited[y + 1][x] && map[y + 1][x] <= oldest)
    {
        dfs(y + 1, x, oldest, visited);
    }
    if (result == k)
        return;

    if (x != 1 && !visited[y][x - 1] && map[y][x - 1] <= oldest)
    {
        dfs(y, x - 1, oldest, visited);
    }
    if (result == k)
        return;

    if (x != xSize && !visited[y][x + 1] && map[y][x + 1] <= oldest)
    {
        dfs(y, x + 1, oldest, visited);
    }
    if (result == k)
        return;
}

bool function(int oldest)
{
    bool visited[MAX][MAX];
    for (int y = 1; y <= ySize; y++)
    {
        for (int x = 1; x <= xSize; x++)
        {
            visited[y][x] = false;
        }
    }

    for (int y = 1; y <= ySize; y++)
    {
        for (int x = 1; x <= xSize; x++)
        {
            if (!visited[y][x] && map[y][x] <= oldest)
            {
                dfs(y, x, oldest, visited);
                if (result == k)
                {
                    result = 0;
                    return true;
                }
                result = 0;
            }
        }
    }
    return false;
}

void doIt()
{
    result = 0;
    cin >> ySize >> xSize >> k;
    int maks = -1;
    for (int y = 1; y <= ySize; y++)
    {
        for (int x = 1; x <= xSize; x++)
        {
            cin >> map[y][x];
            maks = max(maks, map[y][x]);
        }
    }

    int l = 0;
    int r = maks;
    while (l < r)
    {
        int m = (l + r) / 2;
        bool res = function(m);
        if (res)
        {
            r = m;
        }
        else
        {
            l = m + 1;
        }
    }
    cout << r << endl;
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