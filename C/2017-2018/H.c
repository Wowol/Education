#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAXDLUGOSCIMIENIA 35
#define MAX 20005

struct osoba
{
    char imie[MAXDLUGOSCIMIENIA];
    int iloscGlosow;
};

struct osoba tab[MAX];
int iloscOsob;
int n;
int sorted[MAX];
char imiona[MAX][MAXDLUGOSCIMIENIA];
int imionaSorted[MAX];

void swap(int a, int b)
{
    int c = sorted[a];
    sorted[a] = sorted[b];
    sorted[b] = c;
}

void swap2(int a, int b)
{
    int c = imionaSorted[a];
    imionaSorted[a] = imionaSorted[b];
    imionaSorted[b] = c;
}

void insertionSort()
{
    for (int x = 1; x < iloscOsob; x++)
    {
        for (int y = x; y >= 1; y--)
        {
            if (tab[sorted[y]].iloscGlosow > tab[sorted[y - 1]].iloscGlosow)
            {
                swap(y - 1, y);
                continue;
            }
            else
            {
                break;
            }
        }
    }
}

void sort2()
{
    for (int x = 1; x < n; x++)
    {
        for (int y = x; y >= 1; y--)
        {
            if (strcmp(imiona[imionaSorted[y]], imiona[imionaSorted[y - 1]]) < 0)
            {
                swap2(y - 1, y);
            }
            else
            {
                break;
            }
        }
    }
}

void wordToLower(char *imie)
{
    for (int x = 0; x < strlen(imie); x++)
    {
        imie[x] = tolower(imie[x]);
    }
}

void doIt()
{

    scanf("%i", &n);
    iloscOsob = 0;

    for (int x=0; x<n+3; x++)
    {
        imionaSorted[x] = x;
        sorted[x] = x;
    }

    for (int x = 0; x < n; x++)
    {
        scanf("%s", &imiona[x]);
        wordToLower(imiona[x]);
    }

    sort2();

    imiona[n][0] = '\0';
    int p = 0;
    int z = 0;
    for (int x = 1; x <= n; x++)
    {
        p++;
        if (strcmp(imiona[imionaSorted[x]], imiona[imionaSorted[x - 1]]) != 0)
        {
            tab[z].iloscGlosow = p;
            strcpy(tab[z].imie, imiona[imionaSorted[x - 1]]);
            z++;
            p = 0;
        }
    }

    iloscOsob = z;

    printf("%i\n", iloscOsob);

    insertionSort();

    for (int x = 0; x < iloscOsob; x++)
    {
        printf("%s %i\n", tab[sorted[x]].imie, tab[sorted[x]].iloscGlosow);
    }
}

int main()
{
    int z;

    scanf("%i", &z);

    while (z--)
    {
        doIt();
    }
}