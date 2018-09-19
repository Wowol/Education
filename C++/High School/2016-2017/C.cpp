// Diagnostyka.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <set>

const int ALPHABET = 2;
const int MAX = 5005;
const int MODNUMBER = 1e9 + 7;

using namespace std;
int nextState[MAX][ALPHABET];

int n;
int sizeString = 0;
int states = 0;
int maxSufix[MAX];
vector<int> sorted;
set<int> previous[MAX];
int dp[2][MAX];

void clear()
{
	sorted.clear();
	for (int x = 0; x < ALPHABET; x++)
	{
		nextState[0][x] = -1;
	}
	for (int x = 0; x <= sizeString; x++)
	{
		previous[x].clear();
	}
	states = 0;
}

void bfs()
{
	queue<int> q;
	q.push(0);
	while (!q.empty())
	{
		int state = q.front();
		sorted.push_back(state);
		q.pop();
		for (int x = 0; x < ALPHABET; x++)
		{
			int neighbour = nextState[state][x];
			if (neighbour != -1)
			{
				q.push(neighbour);
			}
		}
	}
}

int addLetterTonextState(char c, int place)
{
	if (nextState[place][c] != -1) return nextState[place][c];
	int newState = ++states;
	nextState[place][c] = newState;
	previous[newState].insert(place);
	for (int x = 0; x < ALPHABET; x++)
	{
		nextState[newState][x] = -1;
	}
	return newState;
}

int convertLetterToInt(char letter)
{
	if (letter == 'a')
	{
		return 0;
	}
	if (letter == 'b')
	{
		return 1;
	}

	return 4;
}

void addWordToNextState(string s)
{
	int currentPosition = 0;
	for (int x = 0; x < s.length(); x++)
	{
		currentPosition = addLetterTonextState(convertLetterToInt(s[x]), currentPosition);
	}
}



void createRest()
{
	for (int a = 0; a < ALPHABET; a++)
	{
		if (nextState[0][a] != -1) maxSufix[nextState[0][a]] = 0;
	}
	for (int a = 0; a < ALPHABET; a++)
	{
		if (nextState[0][a] == -1)
		{
			nextState[0][a] = 0;
			previous[0].insert(0);

		}
			
	}

	for (int x = 1; x < states; x++)
	{
		int state = sorted[x];
		for (int a = 0; a < ALPHABET; a++)
		{
			int p = nextState[state][a];
			if (p == -1)
			{
				nextState[state][a] = nextState[maxSufix[state]][a];
				previous[nextState[maxSufix[state]][a]].insert(state);
			}
			else
			{
				maxSufix[p] = nextState[maxSufix[state]][a];
			}
		}

	}

}

int potagaModulo(int exp)
{
	int c = 1;
	for (int x = 1; x <= exp; x++)
	{
		c = (c * 2) % MODNUMBER;
	}
	return c;
}



void doIt()
{
	cin >> n;
	string s;
	cin >> s;
	sizeString = s.size();
	clear();
	
	addWordToNextState(s);


	bfs();
	createRest();



	dp[0][0] = 1;
	for (int x = 1; x < sizeString; x++)
	{
		dp[0][x] = 0;
	}

	bool makingOne = false;
	int q = 0;
	for (int t = 1; t <= n; t++)
	{
		makingOne = !makingOne;
		if (makingOne) q = 1;
		else q = 0;
		for (int v = 0; v < sizeString; v++)
		{
			int sum = 0;
			std::set<int>::iterator it;
			
			for (it = previous[v].begin(); it != previous[v].end(); it++)
			{			
				int temp = *it;
				sum += dp[abs(q-1)][temp];	
				sum %= MODNUMBER;
			}

			dp[q][v] = sum;
		}

	}

	int p = potagaModulo(n);
	int sum = 0;
	for (int x = 0; x < sizeString; x++)
	{
		sum += dp[q][x];
		sum %= MODNUMBER;
	}
	int result = p - sum;
	if (result < 0) result = MODNUMBER + result;
	cout << result << endl;
	
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

