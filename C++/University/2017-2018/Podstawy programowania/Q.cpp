#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>

#define MAX 15
#define MAXPRIME 1111119
using namespace std;

int n;
bool wykreslone[MAXPRIME];
int inputNumber;
bool found = false;

bool check(char number[])
{
    int numberInt = atoi(number);
    int diff = abs(inputNumber - numberInt);
    if (diff % 9 == 0)
    {
        diff/=9;
        if (diff < 1111111 && !wykreslone[diff])
        {
            return true;
        }
    }

    return false;
}

void rek(char number[], int currentIndex)
{
    if (found) return;    
    if (currentIndex == n)
    {
        if (check(number))
        {
            found = true;
            printf("TAK %s\n", number);
        }
        return;
    }

    for (int x=currentIndex; x<n; x++)
    {
        if (found) return;
        swap(number[currentIndex], number[x]);
        rek(number, currentIndex+1);
        swap(number[currentIndex], number[x]);
    }

}

void sito()
{
    int a = 0, b = MAXPRIME-3;
    for (int x=a; x<MAXPRIME; x++)
    {
        wykreslone[x] = false;
    }

    wykreslone[1] = true;
    wykreslone[0] = true;

    for (int c = 2; c*c<=b; c++)
    {
        if (!wykreslone[c])
        {
            for (int d = c*c; d<=b; d+=c)
            {
                wykreslone[d] = true;
            }
        }
    }
}

void doIt()
{
    found = false;
    char number[MAX];    
    scanf("%s", number);
    inputNumber = atoi(number);    
    n = strlen(number);
    rek(number, 0);
    if (!found)
    {
        printf("NIE\n");
    }
}

int main()
{
    sito();
    int z;
    cin >> z;
    while (z--)
    {
        doIt();
    }
}