#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const double around = 1e-13;

double f(double x)
{
    return x*x*x-x*x+x;
}

double fabs(double x)
{
    return x>=0 ? x : x*(-1);
}

void doIt()
{
    double n;
    scanf("%lf", &n);
    double l = 0;
    double r = 1e7;
    double m;
    while(r-l>around)
    {
        m = (l+r)/2;
        double wynik = f(m);
        double s = fabs(wynik-n);
        if (s<around)
        {
            break;
        }
        if (wynik < n)
        {
            l = m;
        }
        else
        {
            r = m;
        }
    }
    int podloga = (int)m;
    int sufit = podloga+1;
    if (sufit-m<1e-10)
    {
        podloga++;
    }
    else if (m-podloga<1e-10)
    {
        sufit--;
    }
    printf("%.10lf %i %i\n", m, podloga, sufit);
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