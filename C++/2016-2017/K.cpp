// Dywersja.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

const int MAX = 1010;
using namespace std;

vector<vector<int>> G(MAX);
vector<vector<int>> Dobry(MAX*MAX*4);
//pair<int, int> def[MAX*MAX*4];
bool visited[MAX*MAX * 4];
//map<pair<int, int>, int> mapa;
int n;

void Clean()
{
	for (int x = 0; x < n + 2; x++)
	{
		G[x].clear();
	}
	for (int x = 0; x < n*n * 4 + 2; x++)
	{
		visited[x] = false;
		Dobry[x].clear();
	}
}

int getValue(pair<int, int> p)
{
	return (p.first - 1)*n + p.second;
}

/*pair<int, int> getPair(int v)
{
	pair<int, int> temp;
	temp.first = (v-1)/n + 1;
	temp.second = v - (temp.first - 1)*n;
}*/

void doIt()
{
	cin >> n;
	Clean();
	for (int x = 1; x <= n; x++)
	{
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		G[x].push_back(a);
		G[x].push_back(b);
		G[x].push_back(c);
		G[x].push_back(d);
	}


	for (int x = 1; x <= n; x++)
	{
		for (int y = 1; y <= n; y++)
		{	
			for (int z = 0; z < 4; z++)
			{
				int a = G[x][z];
				int b = G[y][z];
				int d = getValue(make_pair(G[x][z], G[y][z]));
				Dobry[d].push_back(getValue(make_pair(x, y)));
			}
			
		}
	}

	int iloscZnalezionych = 0;
	queue<int> kolejka;
	for (int x = 1; x <= n; x++)
	{
		int a = getValue(make_pair(x, x));
		kolejka.push(a);
		visited[a] = true;
		iloscZnalezionych++;
	}
	while (!kolejka.empty())
	{
		int p = kolejka.front();
		kolejka.pop();
		for (int x = 0; x < Dobry[p].size(); x++)
		{
			int sasiad = Dobry[p][x];
			if (!visited[sasiad])
			{
				kolejka.push(sasiad);
				visited[sasiad] = true;
				iloscZnalezionych++;
			}
		}

	}
	
	if (iloscZnalezionych == n*n)
	{
		cout << "TAK" << endl;
	}
	else cout << "NIE" << endl;


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
	//system("pause");
}

