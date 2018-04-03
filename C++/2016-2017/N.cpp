// NPrezydent.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdio>

const int MAX = 300006;

using namespace std;

vector<pair<int, int>> SetKrawedzie;
set<int> wierzcholki;
int n;
int visited[MAX];

bool KrawedzIstnieje(int a, int b)
{
	//if (SetKrawedzie.find(make_pair(a, b)) != SetKrawedzie.end())
	vector<pair<int, int>>::iterator it = lower_bound(SetKrawedzie.begin(), SetKrawedzie.end(), make_pair(a, b));
	if (it != SetKrawedzie.end())
	{
		if (*it== make_pair(a, b))
		{
			return false;
		}
		else return true;
	}
	return true;
	
	
}

void BFS()
{
	int first = *wierzcholki.begin();
	queue<int> kolejka;
	kolejka.push(first);
	visited[first] = true;
	wierzcholki.erase(wierzcholki.begin());
	while (!kolejka.empty())
	{
		int przetw = kolejka.front();
		kolejka.pop();
		set<int>::iterator it;
		for (it = wierzcholki.begin(); it != wierzcholki.end();)
		{
			int kolejny = *it;
			if (!visited[kolejny])
			{
				if (KrawedzIstnieje(przetw, kolejny))
				{
					wierzcholki.erase(it++);
					kolejka.push(kolejny);
					visited[kolejny] = true;
				}
				else
				{
					it++;
				}
			}
			else it++;
			
		}
		
	}
}

void DoIt()
{
	int m;
	cin >> n >> m;
	wierzcholki.clear();
	SetKrawedzie.clear();
	for (int x = 0; x <= n; x++)
	{
		visited[x] = false;
		if (x!=0) wierzcholki.insert(x);
	}
	

	for (int x = 0; x < m; x++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		SetKrawedzie.push_back(make_pair(a, b));
		SetKrawedzie.push_back(make_pair(b, a));
	}
	sort(SetKrawedzie.begin(), SetKrawedzie.end());

	vector<int> wynik;
	int current = wierzcholki.size();
	while (wierzcholki.size() != 0)
	{
		BFS();
		wynik.push_back(current - wierzcholki.size());
		current = wierzcholki.size();
	}
	
	sort(wynik.begin(), wynik.end());
	for (int x = 0; x < wynik.size(); x++)
	{
		printf("%d ", wynik[x]);
	}
	printf("\n");
	



}



int main()
{
	int z;
	cin >> z;
	while (z--)
	{
		DoIt();
	}
	system("pause");
	return 0;
}

