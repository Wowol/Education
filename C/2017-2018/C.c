#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define min(x, y) (((x) < (y)) ? (x) : (y))


#define MAX 1000010

int dzielnik[MAX*4+10];
int result[MAX*4+10];
int ciag[MAX*4+10];
int maxWykorzystanaWielokrotnoscLiczbyPierwszej[MAX*4+10];

void doIt()
{
    int n;
    scanf("%i", &n);
    printf("%i\n", result[n]+1);
    
    // for (int n=2; n<300005; n++)
    // {
    //     printf("%i: %i\n",n, result[n]+1);
    // }
}

void calculate()
{
    for (int x=0; x<MAX; x++)
    {
        maxWykorzystanaWielokrotnoscLiczbyPierwszej[x] = 0;
    }
    for (int x=0; x<MAX; x++)
    {
        result[x] = -1;        
    }

    ciag[0] = 1;
    ciag[1] = 2;
    result[1] = 0;
    result[2] = 1;
    maxWykorzystanaWielokrotnoscLiczbyPierwszej[2] = 2;

    for (int n=2; n<MAX; n++)
    {
        int primeNumbers[MAX];
        int old = -1;
        int indeks = -1;

        int previousNumber = ciag[n-1];
    
        while (previousNumber>1)
        {
            int dz = dzielnik[previousNumber];
            if (old != dz)
            {
                old = dz;
                indeks++;
                primeNumbers[indeks] = dz;
                primeNumbers[indeks+1] = -1;
            }
            previousNumber/=dz;
        }

        int minTempResult = 2147483647;
        int tempPrime = -1;
        for (int i=0; i<=indeks; i++)
        {
            int prime = primeNumbers[i];
            int primeWielokrotnosc = maxWykorzystanaWielokrotnoscLiczbyPierwszej[prime];
            if (primeWielokrotnosc + prime < MAX)
            {
                while (result[primeWielokrotnosc + prime] != -1)
                {
                    primeWielokrotnosc += prime;
                    if (primeWielokrotnosc + prime > MAX)
                    {
                        break;
                    }
                }
            }
            maxWykorzystanaWielokrotnoscLiczbyPierwszej[prime] = primeWielokrotnosc;
            if (primeWielokrotnosc + prime < minTempResult)
            {
                minTempResult = primeWielokrotnosc + prime;
                tempPrime = prime;
            }
        }
        ciag[n] = minTempResult;
        maxWykorzystanaWielokrotnoscLiczbyPierwszej[tempPrime] = minTempResult;
        result[minTempResult] = n;
    }
}

void sito()
{
    int a = 0, b = MAX*2;
    for (int x=a; x<b; x++)
    {
        dzielnik[x] = x;
    }

    dzielnik[1] = 1;

    for (int c = 2; c<=sqrt(b); c++)
    {
        if (dzielnik[c]==c)
        {
            for (int d = c*c; d<=b; d+=c)
            {
                if (dzielnik[d] == d)
                {
                    dzielnik[d] = c;
                }
            }
        }
    }

}

int main()
{
    sito();

    calculate();

    int z;
    scanf("%i", &z);
    while (z--)
    {
        doIt();
    }
    return 0;
}