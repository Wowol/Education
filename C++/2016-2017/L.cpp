//#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;
const int MAX = 600000;
const int KLOCK_MAX = 505;

vector<vector<int>> G(MAX);
bool visited[MAX];
int m1[MAX];
int m2[MAX];
char tab[KLOCK_MAX][KLOCK_MAX];
int allNumbers = 0;

bool jestWGrafie[MAX];

int n, m;
int iloscNormalnych = 0;

bool dfs(int u)
{
	if (u == -1)
	{
		return true;
	}
	if (visited[u])
	{
		return false;
	}
	visited[u] = true;

	for (int v = 0; v<G[u].size(); v++)
	{
		int wierzcholek = G[u][v];
		if (dfs(m2[wierzcholek]))
		{
			m1[u] = wierzcholek;
			m2[wierzcholek] = u;
			return true;
		}
	}
	return false;
}

int GetId(int x, int y)
{
	return 2*(m*y + x);
}

void MakeGraph()
{
	cin >> n >> m;
	allNumbers = n*m * 2;

	for (int x = 0; x <= allNumbers; x++)
	{
		jestWGrafie[x] = false;
		m1[x] = -1;
		m2[x] = -1;
		G[x].clear();
	}

	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			cin >> tab[y][x];
			if (tab[y][x] == 'C') iloscNormalnych += 2;
			if (tab[y][x] == 'B') iloscNormalnych++;
		}
	}

	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			if (tab[y][x] == 'C')
			{
				if (x != 0)
				{
					if (tab[y][x - 1] == 'B')
					{
						G[GetId(x, y) + 1].push_back(GetId(x - 1, y));
						G[GetId(x - 1, y)].push_back(GetId(x, y) + 1);
						jestWGrafie[GetId(x, y) + 1] = true;
						jestWGrafie[GetId(x - 1, y)] = true;
					}
				}
				if (x != m-1)
				{
					if (tab[y][x + 1] == 'B')
					{
						G[GetId(x, y) + 1].push_back(GetId(x + 1, y));
						G[GetId(x + 1, y)].push_back(GetId(x, y) + 1);
						jestWGrafie[GetId(x, y) + 1] = true;
						jestWGrafie[GetId(x + 1, y)] = true;
					}
				}
				if (y != 0)
				{
					if (tab[y-1][x] == 'B')
					{
						G[GetId(x, y)].push_back(GetId(x, y-1));
						G[GetId(x, y - 1)].push_back(GetId(x, y));
						jestWGrafie[GetId(x, y)] = true;
						jestWGrafie[GetId(x, y - 1)] = true;
					}
				}
				if (y != n-1)
				{
					if (tab[y+1][x] == 'B')
					{
						G[GetId(x, y)].push_back(GetId(x, y+1));
						G[GetId(x, y + 1)].push_back(GetId(x, y));
						jestWGrafie[GetId(x, y)] = true;
						jestWGrafie[GetId(x, y + 1)] = true;
					}
				}
			}
		}
	}



}

void doIt()
{
	iloscNormalnych = 0;
	MakeGraph();
	
	for (int x = 0; x < allNumbers; x++)
	{
		if (jestWGrafie[x])
		{
		//	iloscNormalnych++;
		}
	}


	int licznik = 0;

	while (true)
	{
		for (int x = 0; x <= allNumbers; x++)
		{
			visited[x] = false;
		}
		bool ok = false;
		for (int x = 0; x < allNumbers; x++)
		{
			if (m1[x] == -1)
			{
				if (dfs(x))
				{
					ok = true;
					licznik++;
					if (licznik == iloscNormalnych)
					{
						cout << "TAK" << endl;
						return;
					}
				}
			}
		}
		if (!ok)
		{
			cout << "NIE" << endl;
			return;
		}

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
	system("pause");
}