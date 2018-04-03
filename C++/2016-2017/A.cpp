//#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
const int MAX = 131075;
const int MAX_LOG = 17;
int tab[MAX_LOG + 3][MAX];
//int mniejszaRowna[MAX];
//int potegiDwojki[MAX_LOG+4];
set<pair<int, int>> sameThings;

int n;


struct parka
{
	int first;
	int last;
	int index;
};

parka parki[MAX];

bool operator<(const parka& a, const parka& b)
{
	if (a.first<b.first)
		return true;
	if (a.first>b.first)
		return false;
	if (a.last<b.last)
		return true;
	if (a.last>b.last)
		return false;
	return (a.index<b.index);

}

int logarithm(int number)
{
	int temp = -1;
	while (number>0)
	{
		number /= 2;
		temp++;
	}
	return temp;
}

bool ExistsSame(int number)
{
	sameThings.clear();
	int log = logarithm(number);
	int pot = 1 << log;
	int roznica = number - pot; // potegiDwojki[pot];
	pair<int, int> temp;
	for (int x = 0; x<n; x++)
	{
		temp.first = tab[log][x];
		if (x + roznica >= n)
		{
			return false;
		}
		temp.second = tab[log][x + roznica];
		if (!sameThings.insert(temp).second)
		{
			return true;
		}
	}
	return false;
}


void doIt()
{
	cin >> n;
	int log = logarithm(n) + 2;
	for (int x = 0; x<n; x++)
	{
		cin >> tab[0][x];
	}

	for (int y = 0; y<log; y++)
	{
		for (int x = 0; x<n; x++)
		{
			parki[x].first = tab[y][x];
			int pot = 1 << y;
			if (x + pot<n)
				parki[x].last = tab[y][x + pot];
			else parki[x].last = -1;
			parki[x].index = x;
		}

		sort(parki, parki + n);
		int currentIndex = 1;
		parka temp;
		int index;
		parka previous;
		for (int x = 0; x<n; x++)
		{
			temp = parki[x];
			index = temp.index;
			if (x >= 1)
			{
				previous = parki[x - 1];
				if (previous.first != temp.first || previous.last != temp.last)
				{
					currentIndex++;
				}
			}
			tab[y + 1][index] = currentIndex;
		}
	}
	int l = 1;
	int r = n;
	int mid;
	int lastGood;
	while (l <= r)
	{
		mid = (r + l) / 2;
		if (ExistsSame((mid)))
		{
			l = mid + 1;
		}
		else
		{
			r = mid - 1;
			lastGood = mid;
		}
	}
	cout << lastGood << endl;
}



int main()
{
	std::ios::sync_with_stdio(false);
	/* int p = 1<<1;
	cout << p << endl;
	return 0;*/

	int z;
	cin >> z;
	while (z--)
		doIt();
	//system("pause");
}