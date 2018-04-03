//#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
const int MAX = 530000;
const int MAX_LOG = 19;
int tab[MAX_LOG + 3][MAX];
//int mniejszaRowna[MAX];
//int potegiDwojki[MAX_LOG+4];
int sorted[MAX];
int wynik[MAX];

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

bool AreSame(int indexOne, int indexTwo, int number)
{
	int log = logarithm(number);
	int pot = 1 << log;
	int roznica = number - pot; // potegiDwojki[pot];
	pair<int, int> tempOne;
	pair<int, int> tempTwo;

	tempOne.first = tab[log][indexOne];
	tempTwo.first = tab[log][indexTwo];

	if (indexOne + roznica >= n)
	{
		tempOne.second = -1;
	}
	else
	{
		tempOne.second = tab[log][indexOne + roznica];
	}
	if (indexTwo + roznica >= n)
	{
		tempTwo.second = -1;
	}
	else
	{
		tempTwo.second = tab[log][indexTwo + roznica];
	}

	if (tempOne == tempTwo)
	{
		return true;
	}

	return false;
}


void doIt()
{
	cin >> n;
	int log = logarithm(n) + 1;
	for (int x = 0; x<n; x++)
	{
		char znaczek;
		cin >> znaczek;
		if (znaczek == 'L')
			tab[0][x] = 0;
		else tab[0][x] = 1;
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
			if (y == log - 1)
			{
				sorted[x] = index;
			}
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
/*	for (int y = 0; y <= log; y++)
	{
		for (int x = 0; x < n; x++)
		{
			cout << tab[y][x] << " ";

		}
		cout << endl;
	}
	cout << endl;*/
	


	/*for (int x = 0; x < n; x++)
	{
		cout << sorted[x] << ":  ";
		for (int y = sorted[x]; y < n; y++)
		{
			cout << tab[0][y] << " ";
		}
		cout << endl;
	
	}*/

	for (int x = 0; x < n; x++)
	{
		int l = 1;
		int r = n;
		int mid;
		int lastGood = 0;
		int resultOne = 0;
		int resultTwo = 0;

		if (x != n - 1)
		{		
			while (l <= r)
			{
				mid = (r + l) / 2;
				if (AreSame(sorted[x], sorted[x + 1], mid))
				{
					lastGood = mid;
					l = mid + 1;
				}
				else
				{
					r = mid - 1;
				}
			}
			resultOne = lastGood;
		}	

		if (x != 0)
		{
			l = 1;
			r = n;
			lastGood = 0;
			while (l <= r)
			{
				mid = (r + l) / 2;
				if (AreSame(sorted[x], sorted[x - 1], mid))
				{
					lastGood = mid;
					l = mid + 1;
				}
				else
				{
					r = mid - 1;
				}
			}
			resultTwo = lastGood;
			
		}
		wynik[sorted[x]] = max(resultOne, resultTwo);
		
	}

	for (int x = 0; x < n; x++)
	{
		cout << wynik[x] << " ";
	}
	cout << endl;
	
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
	system("pause");
}