// CiagDeBruina.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

void doIt()
{
	int n;
	cin >> n;
	if (n == 1)
	{
		cout << "ba" << endl;
		return;
	}

	int potega = 1 << n;
	int prowadziDo = (1 << (n - 1));
	vector<int> ileRazyOdwiedzony(potega);
	stack<int> stos;
	stos.push(0);
	while (!stos.empty())
	{
		int wierzcholek = stos.top();
		if (ileRazyOdwiedzony[wierzcholek] == 2)
		{
			if (wierzcholek % 2 == 0) cout << 'a';
			else cout << 'b';
			//cout << wierzcholek;
			stos.pop();
		}
		else
		{
			int p = wierzcholek * 2;
			int kolejny = ((prowadziDo-1) & p) + ileRazyOdwiedzony[wierzcholek]++;
			stos.push(kolejny);
		}
	}

	for (int x = 0; x < n - 2; x++)
	{
		cout << 'a';
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

