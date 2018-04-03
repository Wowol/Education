// Dojarka.cpp : Defines the entry polong long for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

struct pole
{
	long long x;
	long long y;
	long long i;
};

void doIt()
{
	long long n;
	cin >> n;
	vector<pole> tab;
	long long xo = 0;
	long long count = 0;
	for (long long x = 0; x < n; x++)
	{
		pole temp;
		cin >> temp.x >> temp.y >> temp.i;
		if (temp.x == 0 || temp.y == 0)
		{
			count += temp.i;
		}
		if (temp.i % 2 == 1)
		{
			xo ^= (temp.x - 1);
			xo ^= (temp.y - 1);
		}
		tab.push_back(temp);

	}
	if (count != 0)
	{
		cout << count << endl;
		return;
	}

	for (long long x = 0; x < n; x++)
	{
		pole temp = tab[x];
		long long s = (temp.x - 1) ^ xo;
		long long p = (temp.y - 1) ^ xo;
		if (s < temp.x - 1)
		{
			count += temp.i;
		}
		if (p < temp.y - 1)
		{
			count += temp.i;
		}
	}


	cout << count << endl;




}

int main()
{
	ios_base::sync_with_stdio(0);
	long long z;
	cin >> z;
	while (z--)
	{
		doIt();
	}
	system("pause");
}

