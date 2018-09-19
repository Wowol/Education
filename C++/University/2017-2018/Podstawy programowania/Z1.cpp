#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MAX 8000007

int dzielnik[MAX];

struct prime{
    int value;
    int count;
};

void doIt()
{
    int n;
    scanf("%i", &n);

    struct prime primeNumbers[MAX];
    
    int iloscDzielnikowPierwszych = 0;
    int x = 0;

    int old = -1;
    int indeks = -1;

    for (; n>1; x++)
    {
        int dz = dzielnik[n];
        if (old != dz)
        {
            old = dz;
            indeks++;
            primeNumbers[indeks].value = dz;
            primeNumbers[indeks].count = 0;
        }
        primeNumbers[indeks].count++;
        n/=dz;
    }

    int result = 1;
    for (int x=0; x<=indeks; x++)
    {
        struct prime p = primeNumbers[x];
        int temp = (round(pow(p.value, p.count+1))-1)/(p.value-1);
        result*=temp;
    }
    printf("%i\n", result);
}

void sito()
{
    int a = 0, b = MAX;
    for (int x=a; x<=b; x++)
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
    int z;
    scanf("%i", &z);
    while (z--)
    {
        doIt();
    }
}