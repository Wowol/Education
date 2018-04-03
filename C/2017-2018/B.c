#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MAX 10000007

bool wykreslone[MAX+2];
int dzielnik[MAX+2];
int results[MAX+2];

void prog()
{
    int a, b;
    scanf("%i %i", &a, &b);
    printf("%i %i %i \n", results[b]-results[a] + !wykreslone[a], dzielnik[a], dzielnik[b]);
}

int main()
{
    int z;
    scanf("%i", &z);

    int a = 0, b = MAX;
    for (int x=a; x<=b; x++)
    {
        wykreslone[x] = false;
        dzielnik[x] = x;
    }

    wykreslone[1] = true;

    for (int c = 2; c<=sqrt(b); c++)
    {
        if (!wykreslone[c])
        {
            for (int d = c*c; d<=b; d+=c)
            {
                wykreslone[d] = true;
                if (dzielnik[d] == d)
                {
                    dzielnik[d] = c;
                }
            }
        }
    }

    int count = 0;
    for (int x=1; x<b; x++)
    {
        count += !wykreslone[x] ? 1 : 0;
        results[x] = count;
    }

    while (z--)
    {
        prog();
    }

    return 0;
}