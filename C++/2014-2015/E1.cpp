#include <iostream>
#include <vector>
#include <stack>
#define MAX 1000005
#define endl '\n'

using namespace std;

vector<vector <int> > graph(MAX);
bool visited[MAX] = {false};
vector<vector <int> > odwroconyGraph(MAX);
vector<int> wierzcholki;
std::stack<int> stos;
int z = 0;
int wynik[MAX];
int n = MAX;
int tab[MAX];
int numerSS = 1;
int ile = 0;

int stworzStos(int a)
{
    visited[a] = true;
    for (int x=0; x<graph[a].size(); x++)
    {
        if (visited[graph[a][x]]==false)
        {
            stworzStos(graph[a][x]);
        }
    }
    stos.push(a);
}

int licz(int a)
{
    visited[a] = false;
    ile++;
    wynik[a] = numerSS;
    for (int x=0; x<odwroconyGraph[a].size(); x++)
    {
        if (visited[odwroconyGraph[a][x]]==true)
        {
            licz(odwroconyGraph[a][x]);
        }
    }
}

int doIt()
{
    int y;
    int a, b;
    int p = 0;
    cin >> n >> y;
    for (int x=0; x<y; x++)
    {
        cin >> a >> b;
        graph[a].push_back(b);
        odwroconyGraph[b].push_back(a);
    }

    for (int x=1; x<=n; x++)
    {
        if (visited[x]==false)
        {
            stworzStos(x);
        }
    }

    while (!stos.empty())
    {
        int x = stos.top();
        stos.pop();
        if (visited[x]==true)
        {
            licz(x);
            if (ile!=0) ile--;
            tab[numerSS] = ile;
            ile = 0;
            numerSS++;
        }
    }
   for (int z=1; z<=n; z++)
   {
       cout << tab[wynik[z]] << " ";
   }

   cout << endl;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int o;
    cin >> o;
    while (o--)
    {
        doIt();
        numerSS = 1;
        for (int x=0; x<n; x++)
        {
            visited[x] = false;
        }

        while (!stos.empty())
        {
            stos.pop();
        }
        for (int x=0; x<=n; x++)
        {
            graph[x].clear();
            odwroconyGraph[x].clear();
        }
    }
}
