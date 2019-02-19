// 2-SAT.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;
const int MAX = 100005 * 2;
int n;


vector< vector<int> > G(MAX);
vector< vector<int> > T(MAX);
bool visited[MAX];
vector<int> sorted;
vector< vector<int> > SSP(MAX);
int wartosci[MAX];


void clear()
{
	sorted.clear();
	for (int x = 0; x <= 2*n; x++)
	{
		G[x].clear();
		T[x].clear();
		SSP[x].clear();
		visited[x] = false;
		wartosci[x] = 0;
	}
}


int no(int a)
{
	if (a > n)
	{
		return a -= n;
	}
	return a += n;
}

void dfs(int wierzcholek)
{
	visited[wierzcholek] = true;

	for (int x = 0; x < G[wierzcholek].size(); x++)
	{
		int sasiad = G[wierzcholek][x];
		if (!visited[sasiad])
		{
			dfs(sasiad);
		}
	}
	sorted.push_back(wierzcholek);
	
}

void odwrotnyDfs(int wierzcholek, int a)
{
	visited[wierzcholek] = true;
	SSP[a].push_back(wierzcholek);
	for (int x = 0; x < T[wierzcholek].size(); x++)
	{
		int sasiad = T[wierzcholek][x];
		if (!visited[sasiad])
		{
			odwrotnyDfs(sasiad, a);
		}
	}
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
		if (a < 0)
		{
			a *= -1;
			a += n;
		}
	
		if (b < 0)
		{
			b *= -1;
			b += n;
		}
		G[no(a)].push_back(b);
		G[no(b)].push_back(a);

		T[b].push_back(no(a));
		T[a].push_back(no(b));
	}


	for (int x = 1; x <= n*2; x++)
	{
		if (!visited[x])
		{
			dfs(x);
		}
	}
	

	for (int x = 0; x <= n*2; x++)
	{
		visited[x] = false;
	}

	int a = 0;
	for (int x = sorted.size()-1; x >= 0; x--)
	{
		int temp = sorted[x];
		if (!visited[temp])
		{
			odwrotnyDfs(temp, a++);
		}	
	}
	a--;


	for (int x = 0; x <= n * 2; x++)
	{
		visited[x] = false;
	}

	for (int x = a; x >= 0; x--)
	{

		for (int y = SSP[x].size()-1; y >= 0; y--)
		{
			int temp = SSP[x][y];
			if (visited[no(temp)])
			{
				cout << "NIE" << endl;
				return;
			}
			visited[temp] = true;
			if (wartosci[temp] == 0)
			{
				wartosci[temp] = 1;
				wartosci[no(temp)] = 2;
			}
			if (y != 0 && wartosci[temp]==2)
			{
				int temp2 = SSP[x][y - 1];
				if (wartosci[temp2] == 0)
				{
					wartosci[temp2] = 2;
					wartosci[no(temp2)] = 1;
				}
				if (wartosci[temp2] == 1)
				{
					cout << "NIE" << endl;
					return;
				}
			}		
		}


		for (int y = 0; y < SSP[x].size(); y++)
		{
			int temp = SSP[x][y];
			visited[temp] = false;
		}
	}
	cout << "TAK" << endl;
	for (int x = 1; x <= n; x++)
	{
		if (wartosci[x] == 2) cout << "0 ";
		else cout << "1 ";
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
	
	system("pause");
    return 0;
}

