// Tango.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

const int MAX = 200010;

using namespace std;

vector<vector<int>> G(MAX);
vector<vector<int>> tree(MAX);
bool visited[MAX];
int czas = 0;
int in[MAX];
int low[MAX];
int childrenNumber[MAX];
int n;


void Clear()
{
	for (int x = 0; x <= n + 3; x++)
	{
		G[x].clear();
		tree[x].clear();
		visited[x] = false;
		czas = 0;
		in[x] = 0;
		low[x] = 0;
		childrenNumber[x] = 0;
	}
}

void DFS(int wierzcholek, int parent)
{
	czas++;
	wierzcholek[visited] = true;
	in[wierzcholek] = czas;
	low[wierzcholek] = czas;
	for (int x = 0; x < G[wierzcholek].size(); x++)
	{
		int sasiad = G[wierzcholek][x];
		if (sasiad != parent)
		{

			if (visited[sasiad])
			{
				low[wierzcholek] = min(low[wierzcholek], in[sasiad]);
			}

			else
			{
				tree[wierzcholek].push_back(sasiad);
				DFS(sasiad, wierzcholek);
				low[wierzcholek] = min(low[wierzcholek], low[sasiad]);	
			}
		}
	}

	childrenNumber[wierzcholek] = czas - in[wierzcholek];
}

void PrintResult(int wierzcholek)
{
	unsigned long long a = 0;
	unsigned long long b = 0;
	unsigned long long c = 0;
	for (int x = 0; x < tree[wierzcholek].size(); x++)
	{
		int sasiad = tree[wierzcholek][x];
		if (low[sasiad] >= in[wierzcholek])
		{
			b = childrenNumber[sasiad] + 1;
			c += b;
			a += b * (b - 1);
		}
	}
	unsigned long long rest = n - c - 1;
	a += rest*(rest - 1);
	cout << a << endl;
}

void doIt()
{
	int m;
	cin >> n >> m;
	Clear();
	for (int x = 0; x < m; x++)
	{
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	DFS(1, 1);

	for (int x = 1; x <= n; x++)
	{
		PrintResult(x);
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
//	system("pause");
}

