#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define min(a,b) (((a)<(b))?(a):(b))
#define MAX_PROSTE 1000005
#define MAX_PUNKTY 10005
#define INT_MAX 2147483647

struct punkt
{
    int x;
    int y;
    int k;
};

int proste[MAX_PROSTE];
struct punkt punkty[MAX_PUNKTY];
int liczbaPunktow;
int liczbaProstych;

#pragma region funkcje
bool punktNadProsta(struct punkt p, int prosta)
{
    return p.y>prosta*p.x;
}

bool punktNaProstej(struct punkt p, int prosta)
{
    return p.y==prosta*p.x;
}

void input()
{
    scanf("%i", &liczbaProstych);
    for (int i=0; i<liczbaProstych; i++)
    {
        scanf("%i", &proste[i]);
    }
    scanf("%i", &liczbaPunktow);
    for (int i=0; i<liczbaPunktow; i++)
    {
        scanf("%i %i %i", &punkty[i].x, &punkty[i].y, &punkty[i].k);
    }
}

double odlegloscPunktuOdProstej(struct punkt p, int prosta)
{
    return (double)(abs(prosta*p.x-p.y))
        /(double)(sqrt(prosta*prosta+1));
}

#pragma endregion funkcje

int iloscProstychZDolu(struct punkt p, int indexNajblizszejDolnej)
{
    int r = indexNajblizszejDolnej;
    int l = 0;
    int m;
    int indexOstatniejDobrej = indexNajblizszejDolnej + 1;

    while (l<=r)
    {
        m = (l+r)/2;
        double odl = odlegloscPunktuOdProstej(p, proste[m]);

        if (odl > p.k)
        {
            l = m + 1;
        }
        else
        {
            r = m - 1;
            indexOstatniejDobrej = m;
        }

    }
    return indexNajblizszejDolnej-indexOstatniejDobrej + 1;
}

int iloscProstychZGory(struct punkt p, int indexNajblizszejGornej)
{
    int r = liczbaProstych-1;
    int l = indexNajblizszejGornej;
    int m;
    int indexOstatniejDobrej = indexNajblizszejGornej - 1;

    while (l<=r)
    {
        m = (l+r)/2;
        double odl = odlegloscPunktuOdProstej(p, proste[m]);

        if (odl > p.k)
        {
            r = m - 1;
        }
        else
        {
            l = m + 1;
            indexOstatniejDobrej = m;
        }

    }
    return indexOstatniejDobrej-indexNajblizszejGornej + 1;
}

void JUSTDOIT(struct punkt p)
{
    int l = 0;
    int r = liczbaProstych - 1;
    int indexNajblizszejDolnej = -1;
    int indexNajblizszejGornej = -1;
    while (l<=r)
    {
        int m = (l+r)/2;
        int prosta = proste[m];

        if (punktNaProstej(p, prosta))
        {
            indexNajblizszejGornej = m;
            indexNajblizszejDolnej = m;
            break;
        }

        if (punktNadProsta(p, prosta))
        {
            indexNajblizszejDolnej = m;
            l = m+1;
        }
        else
        {
            indexNajblizszejGornej = m;
            r = m-1;
        }
    }

    double odlegloscOdGornej = indexNajblizszejGornej != -1 ? odlegloscPunktuOdProstej(p, proste[indexNajblizszejGornej])
        : INT_MAX;
    double odlegloscOdDolnej = indexNajblizszejDolnej != -1 ? odlegloscPunktuOdProstej(p, proste[indexNajblizszejDolnej])
        : INT_MAX;

    int zDolu = indexNajblizszejDolnej != -1 ? iloscProstychZDolu(p, indexNajblizszejDolnej)
        : 0;
    int zGory = indexNajblizszejGornej != -1 ? iloscProstychZGory(p, indexNajblizszejGornej)
        : 0;

    int dobreOdleglosci = zDolu + zGory;
    if (indexNajblizszejDolnej == indexNajblizszejGornej)
    {
        dobreOdleglosci--;
    }

    printf("%i %i\n", odlegloscOdGornej>odlegloscOdDolnej ? indexNajblizszejDolnej : indexNajblizszejGornej,
        dobreOdleglosci);
}

int main()
{
    int z;
    scanf("%i", &z);
    while (z--)
    {
        input();
        for (int i=0; i<liczbaPunktow; i++)
        {
            JUSTDOIT(punkty[i]);
        }
    }

}