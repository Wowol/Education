// Diagnostyka.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include <queue>

const int ALPHABET = 4;
const int MAX = 1000006;

using namespace std;
int nextState[MAX][ALPHABET];
int states = 0;
int maxSufix[MAX];
bool visited[MAX];
vector<int> sorted;
int endOfWords[MAX];
int numberOfWords;

void clear()
{
	sorted.clear();
	for (int x = 0; x < ALPHABET; x++)
	{
		nextState[0][x] = -1;
	}
	for (int x = 0; x < MAX; x++)
	{
		visited[x] = false;
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
	for (int x = 0; x < ALPHABET; x++)
	{
		nextState[newState][x] = -1;
	}
	return newState;
}

int convertLetterToInt(char letter)
{
	if (letter == 'A')
	{
		return 0;
	}
	if (letter == 'C')
	{
		return 1;
	}
	if (letter == 'G')
	{
		return 2;
	}
	if (letter == 'T')
	{
		return 3;
	}

	return 4;
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
	for (int x = 1; x < states; x++)   // nie wiem czy nie bedzie <=
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


void walk(string word)
{
	int currentPosition = 0;
	for (int x = 0; x < word.length(); x++)
	{
		visited[currentPosition] = true;
		currentPosition = nextState[currentPosition][convertLetterToInt(word[x])];
	}
	visited[currentPosition] = true;


	// Wszystkie sufiksy uznajemy za ogladniete
	for (int x = sorted.size()-1; x >= 0; x--)
	{
		if (visited[sorted[x]]) visited[maxSufix[sorted[x]]] = true;
	}

	for (int x = 0; x < numberOfWords; x++)
	{
		int endOfWord = endOfWords[x];
		if (visited[endOfWord] == true)
		{
			cout << "TAK";
		}
		else cout << "NIE";
		cout << endl;
	}
}

void doIt()
{
    string word;
	cin >> word;

	cin >> numberOfWords;
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
	walk(word);

}





int main()
{
	int z;
	cin >> z;
	while (z--)
	{
		doIt();
	}
	//system("pause");
}

