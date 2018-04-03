#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

const long long MAX = 210;

vector< vector<long long> > G(MAX);
long long weightTab[MAX][MAX];
long long source;
long long destination;
long long p[MAX];
long long n;
bool visited[MAX];
int pl = 0;

bool BFS(long long source, long long destination)
{
    for (long long x=0; x<=pl; x++)
    {
        visited[x] = false;
    }


    queue<long long> kolejka;
    while (!kolejka.empty())
    {
        kolejka.pop();
    }
    visited[source] = true;
    kolejka.push(source);
    while (!kolejka.empty())
    {
        long long kolejny = kolejka.front();
        kolejka.pop();
        long long wielkosc = G[kolejny].size();
        for (long long x=0; x<wielkosc; x++)
        {
            long long sasiad = G[kolejny][x];
            if (visited[sasiad]==false && weightTab[kolejny][sasiad]>0)
            {
                visited[sasiad] = true;
                p[sasiad] = kolejny;
                kolejka.push(sasiad);

                if (sasiad==destination)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

long long getMinWeight()
{
    long long last = destination;
    long long previous = -1;
    long long minn = 100000000003;
    while(previous!=source)
    {
        previous = p[last];
        minn = min(minn, weightTab[previous][last]);
        last = previous;
    }
    return minn;
}

void Flow()
{
    long long m;
    source = 0;
    destination = 1;

    cin >> n >> m;

    pl = n+m+5;

    for (long long x=0; x<=pl; x++)
    {
        for (long long y=0; y<=pl; y++)
        {
            weightTab[y][x] = 0;
        }
    }

    for (long long x=0; x<=pl; x++)
    {
        p[x] = 0;
        G[x].clear();
    }


    for (long long x=2; x<n+2; x++)
    {
        long long a;
        cin >> a;
        G[source].push_back(x);
        G[x].push_back(source);
        weightTab[source][x] += a;
    }

    for (long long x=2; x<m+2; x++)
    {
        long long a;
        cin >> a;
        G[x+n].push_back(destination);
        G[destination].push_back(x+n);
        weightTab[x+n][destination] += a;
    }

    for (int x=2; x<n+2; x++)
    {
        for (int y=2; y<m+2; y++)
        {
            int a;
            cin >> a;
            if (a==1)
            {
                G[x].push_back(y+n);
                G[y+n].push_back(x);

                weightTab[x][y+n] = 1000000000000;
            }
        }
    }


    unsigned long long result = 0;

    while (true)
    {
        bool exists = BFS(source, destination);
        if (!exists)
        {
            break;
        }
        long long previous = -1;
        long long last = destination;
        long long minWeight = getMinWeight();
        result+=minWeight;
        while(previous!=source)
        {
            previous = p[last];
            weightTab[previous][last] -= minWeight;
            weightTab[last][previous] += minWeight;
            last = previous;
        }

    }

    cout << result << endl;

}

int main()
{
    long long z;
    cin >> z;
    while (z--)
    {
        Flow();
    }

}
