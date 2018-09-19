// Diagnostyka.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include <queue>

const int ALPHABET = 2;
const int MAX = 500005;

using namespace std;
int nextState[MAX][ALPHABET];
int states = 0;
int maxSufix[MAX];
vector<int> sorted;
int endOfWords[MAX];
int numberOfWords;
int layer[MAX];
int maksLayer = 0;

void clear()
{
	layer[0] = 0;
	maksLayer = 0;
	sorted.clear();
	for (int x = 0; x < ALPHABET; x++)
	{
		nextState[0][x] = -1;
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
				layer[neighbour] = layer[state]+1;
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
	for (int x = 0; x < ALPHABET; x++)
	{
		nextState[newState][x] = -1;
	}
	return newState;
}

int convertLetterToInt(char letter)
{
	if (letter == '0')
	{
		return 0;
	}
	if (letter == '1')
	{
		return 1;
	}
}

void addWordToNextState(string s, int number)
{
	int currentPosition = 0;
	for (int x = 0; x < s.length(); x++)
	{
		currentPosition = addLetterTonextState(convertLetterToInt(s[x]), currentPosition);
	}
	endOfWords[number] = currentPosition;
}



void createRest()
{
	for (int a = 0; a < ALPHABET; a++)
	{
		if (nextState[0][a] != -1) maxSufix[nextState[0][a]] = 0;
	}
	for (int a = 0; a < ALPHABET; a++)
	{
		if (nextState[0][a] == -1) nextState[0][a] = 0;
	}
	for (int x = 1; x <= states; x++)
	{
		int state = sorted[x];
		for (int a = 0; a < ALPHABET; a++)
		{
			int p = nextState[state][a];
			if (p == -1)
			{
				nextState[state][a] = nextState[maxSufix[state]][a];
			}
			else
			{
				maxSufix[p] = nextState[maxSufix[state]][a];
			}
		}

	}

}


void searchForLongest()
{
	for (int x = 0; x < numberOfWords; x++)
	{
		int endOfWord = endOfWords[x];
		for (int a = 0; a < ALPHABET; a++)
		{
			maksLayer = max(layer[nextState[endOfWord][a]], maksLayer);
		}
	}
}

void doIt()
{
	int lengthOfWords;
	cin >> numberOfWords >> lengthOfWords;
	clear();
	int number = 0;
	for (int x = 0; x < numberOfWords; x++)
	{
		string s;
		cin >> s;
		addWordToNextState(s, number++);
	}

	bfs();
	createRest();
	searchForLongest();
	cout << lengthOfWords * 2 - maksLayer + 1 << endl;

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

