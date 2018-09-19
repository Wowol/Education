#include <iostream>
#include <vector>

#define MAX 25

using namespace std;

int map[MAX][MAX];
int sizeX, sizeY;
int startPositionX;
int startPositionY;
int targetPositionX;
int targetPositionY;

vector<pair<int, int>> route(5, make_pair(10, 10));

bool visited[MAX][MAX];

bool found = false;

void input()
{
    cin >> sizeY >> sizeX;
    cin >> startPositionY >> startPositionX;
    cin >> targetPositionY >> targetPositionX;

    for (int y = 1; y <= sizeY; y++)
    {
        for (int x = 1; x <= sizeX; x++)
        {
            cin >> map[y][x];
        }
    }
}

bool canGoToThatField(int x, int y, bool *hasRope)
{
    if (found)
    {
        return false;
    }

    if (x > sizeX || y > sizeY)
    {
        return false;
    }

    if (x < 1 || y < 1)
    {
        return false;
    }

    if (visited[y][x])
    {
        return false;
    }

    if (map[y][x] == 1)
    {
        return false;
    }

    if (map[y][x] == 2 && !*hasRope)
    {
        return false;
    }

    if (map[y][x] == 2)
    {
        *hasRope = false;
    }

    return true;
}

void rec(int x, int y, int right, int down, bool hasRope)
{
    visited[y][x] = true;
    bool oldRope = hasRope;
    route.push_back(make_pair(y, x));

    if (y == targetPositionY && x == targetPositionX)
    {
        found = true;
        cout << "TAK " << route.size() + 1 << endl;
        cout << startPositionY << " " << startPositionX;
        for (int x = 0; x < route.size(); x++)
        {
            cout << ", " << route[x].first << " " << route[x].second;
        }

        cout << endl;
        return;
    }

    if (canGoToThatField(x + right, y + down, &hasRope))
    {
        rec(x + right, y + down, right, down, hasRope);
        hasRope = oldRope;
        
    }


    else
    {
        if (right != 0)
        {
            right = 0;

            if (canGoToThatField(x, y + 1, &hasRope))
            {
                rec(x, y + 1, 0, 1, hasRope);
                hasRope = oldRope;
                
            }

            if (canGoToThatField(x, y - 1, &hasRope))
            {
                rec(x, y - 1, 0, -1, hasRope);
                hasRope = oldRope;
                
            }
        }

        if (down != 0)
        {
            down = 0;

            if (canGoToThatField(x + 1, y, &hasRope))
            {
                rec(x + 1, y, 1, 0, hasRope);
                hasRope = oldRope;
            }

            if (canGoToThatField(x - 1, y, &hasRope))
            {
                rec(x - 1, y, -1, 0, hasRope);
                hasRope = oldRope;
            }
        }
    }

    visited[y][x] = false;
    route.pop_back();
}

void clear()
{
    route.clear();
    for (int y = 1; y < MAX; y++)
    {
        for (int x = 1; x < MAX; x++)
        {
            visited[y][x] = false;
        }
    }

    found = false;
}

void doIt()
{
    input();
    clear();
    bool hasRope = true;

    if (startPositionX == targetPositionX && startPositionY == targetPositionY)
    {
        cout << "TAK 1" << endl;
        cout << startPositionY << " " << startPositionX << endl;
        return;
    }

    visited[startPositionY][startPositionX] = true;

    if (!found && canGoToThatField(startPositionX, startPositionY + 1, &hasRope))
    {
        rec(startPositionX, startPositionY + 1, 0, 1, hasRope);
    }
    route.clear();
    hasRope = true;

    if (!found && canGoToThatField(startPositionX, startPositionY - 1, &hasRope))
    {
        rec(startPositionX, startPositionY - 1, 0, -1, hasRope);
    }
    route.clear();
    hasRope = true;

    if (!found && canGoToThatField(startPositionX + 1, startPositionY, &hasRope))
    {
        rec(startPositionX + 1, startPositionY, 1, 0, hasRope);
    }
    route.clear();
    hasRope = true;

    if (!found && canGoToThatField(startPositionX - 1, startPositionY, &hasRope))
    {
        rec(startPositionX - 1, startPositionY, -1, 0, hasRope);
    }

    if (!found)
    {
        cout << "NIE" << endl;
    }
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