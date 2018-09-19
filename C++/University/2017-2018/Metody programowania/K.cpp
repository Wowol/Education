#include <iostream>
#include <vector>
#include <queue>
#define MAX 1000005
#define distance first
#define node second
#define INFINITY 5000000

using namespace std;

int n;
int m;
vector<vector<pair<int, int>>> G(MAX);
int dist[MAX];


void dijkstra()
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    dist[1] = 0;    
    q.push(make_pair(0, 1));
    
    for (int x=2; x<=n; x++)
    {
        dist[x] = INFINITY;
      //  q.push(make_pair(dist[x], x));
    }

    while (!q.empty())
    {
        pair<int, int> e = q.top();
        q.pop();
        int w = e.node;
        if (e.distance > dist[w])
            continue;
        for (int x=0; x<G[w].size(); x++)
        {
            int neighbour = G[w][x].node;
            int d = G[w][x].distance;
            int a = dist[w] + d;
            if (a < dist[neighbour])
            {
                dist[neighbour] = a;
                q.push(make_pair(a, neighbour));
            }
        }
    }
}

void doIt()
{
    cin >> n >> m;
    for (int x=0; x<=n+1; x++)
    {
        G[x].clear();
    }

    for (int x=0; x<m; x++)
    {
        int a, b;
        char c;
        cin >> a >> b >> c;
        G[a].push_back(make_pair(c == '#' ? 2 : 1, b));
        G[b].push_back(make_pair(c == '#' ? 2 : 1, a));
    }
    dijkstra();
    for (int x=1; x<=n; x++)
    {
        if (dist[x] != INFINITY)
        {
            cout << dist[x];
        }
        else cout << '!';
        cout << endl;
    }

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