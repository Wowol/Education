// PatyczkiMat.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <set>
#include <iostream>
using namespace std;
const int MAX = 1005;

int nimbers[MAX];

void doIt()
{
	int n;
	cin >> n;
	int wynik = 0;
	for (int x = 0; x < n; x++)
	{
		int p;
		cin >> p;
		wynik ^= nimbers[p];
	}
	if (wynik == 0)
	{
		cout << 'B';
	}
	else cout << 'A';
	cout << endl;



}

int main()
{
	nimbers[0] = 0;
	for (int x = 1; x < MAX; x++)
	{
		set<int> secik;
	//	secik.insert(nimbers[x - 1]);
	//	if (x>=2) secik.insert(nimbers[x - 2]);
	//	if (x>=3) secik.insert(nimbers[x - 3]);
		for (int y = 1; y <= x; y++)
		{
			int p = y - 1;
			int z = x - p - 1;
			secik.insert(nimbers[p] ^ nimbers[z]);
			if (y <= x - 1)
			{
				z--;
				secik.insert(nimbers[p] ^ nimbers[z]);
			}
			if (y <= x - 2)
			{
				z--;
				secik.insert(nimbers[p] ^ nimbers[z]);
			}
		}

		int expected = 0;
		for (auto it = secik.begin(); it != secik.end(); it++)
		{
			int v = *it;
			if (v != expected++)
			{
				expected--;
				break;
			}
		}
		nimbers[x] = expected;
	}

	int z;
	cin >> z;
	while (z--)
	{
		doIt();
	}
	system("pause");
}

