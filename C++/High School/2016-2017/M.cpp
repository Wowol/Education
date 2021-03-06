// Skojarzenia.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <limits>

const int MAX = 2000;

using namespace std;
map<pair<char, char>, int> mapka;
vector<vector<pair<int, double>>> G(MAX);
vector<vector<pair<int, double>>> oryg(MAX);
int currentId = 0;
int n;
int sizeOfAll = 0;
int q;
double distancea[MAX];

void Clear()
{
	currentId = 0;
	sizeOfAll = 0;
	mapka.clear();
	for (int x = 0; x < n + 5; x++)
	{
		G[x].clear();
		oryg[x].clear();
	}
}

int GetId(char a, char b)
{
	pair<char, char> temp = make_pair(a, b);
	if (mapka.find(temp) != mapka.end())
	{
		return mapka[temp];
	}
	else
	{
		mapka[temp] = ++currentId;
		return currentId;
	}
}

bool Bellman()
{
	for (int x = 1; x <= n; x++)
	{
		distancea[x] = 0;
	}

	for (int z = 1; z <= n; z++)
	{
		for (int x = 1; x <= n; x++)
		{
			for (int y = 0; y < G[x].size(); y++)
			{
				double waga = G[x][y].second;
				int sasiad = G[x][y].first;
				if (distancea[x] + waga < distancea[sasiad])
				{
					distancea[sasiad] = distancea[x] + waga;
				}
			}
		}
	}
	

	for (int x = 1; x <= n; x++)
	{
		for (int y = 0; y < G[x].size(); y++)
		{
			double waga = G[x][y].second;
			int sasiad = G[x][y].first;
			if (distancea[x] + waga < distancea[sasiad])
			{
				return true;
			}
		}
	}
	return false;
}



void CreateGraph()
{
	for (int x = 0; x < q; x++)
	{
		string temp;
		cin >> temp;
		int stringSize = temp.length();
		sizeOfAll += stringSize;
		int idFirst = GetId(temp[0], temp[1]);
		int idLast = GetId(temp[stringSize - 2], temp[stringSize - 1]);
		bool found = false;
		for (int y = 0; y < G[idLast].size(); y++)
		{
			pair<int, int> wierzcholek = G[idLast][y];
			if (wierzcholek.first == idFirst)
			{
				found = true;
				G[idLast][y].second = max(G[idLast][y].second, (double)stringSize);
				oryg[idLast][y].second = G[idLast][y].second;
			}
		}
		if (!found)
		{
			G[idLast].push_back(make_pair(idFirst, stringSize));
			oryg[idLast].push_back(make_pair(idFirst, stringSize));
		}
	}

	n = mapka.size();
	
}

bool porownaj(double a, double b)
{
	return abs(a - b) < 0.000000000001;
}

void doIt()
{
	cin >> q;
	CreateGraph();
	double l = 0;
	double p = double(sizeOfAll);
	while (!porownaj(l, p))
	{
		double m = (l + p) / 2;
		for (int x = 1; x <= n; x++)
		{
			for (int y = 0; y < G[x].size(); y++)
			{
				G[x][y].second = oryg[x][y].second - m;
				G[x][y].second = -1 * G[x][y].second;
			}
		}
		if (Bellman())
		{
			l = m;
		}
		else
		{
			p = m;
		}
	}
	if (p >= 2)
	{
		printf("%.6f\n", p);
		//      cout << fixed << setprecision(4) << p << endl;
	}
	else
	{
		cout << "NIE" << endl;
	}

	Clear();

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