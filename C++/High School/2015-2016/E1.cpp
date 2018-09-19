#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

const long long MAX = 107;

vector< vector<long long> > G(MAX);
long long weightTab[MAX][MAX];
long long source;
long long destination;
long long p[MAX];
long long n;
bool robic = false;
bool visited[MAX];

bool BFS(long long source, long long destination)
{
    for (long long x=0; x<=n+1; x++)
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

    cin >> n >> m >> source >> destination;
    if (robic==true)
    {
   //     cout << n << " " << m << " " << source << " " << destination << endl;
    }

    for (long long x=0; x<=n+1; x++)
    {
        for (long long y=0; y<=n+1; y++)
        {
            weightTab[y][x] = 0;
        }
    }

    for (long long x=0; x<=n+1; x++)
    {
        p[x] = 0;
        G[x].clear();
    }


    for (long long x=0; x<m; x++)
    {
        long long a, b, c;
        cin >> a >> b >> c;
   //     if (robic==true)
     //       cout << a << " " << b << " " << c << endl;
        if (weightTab[a][b]==0)
        {
            G[a].push_back(b);
            G[b].push_back(a);
        }
        weightTab[a][b] += c;
    }

    if (robic)
    {
  //      exit(0);
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
    if (result == 42)
    {
        robic = true;
    }

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
