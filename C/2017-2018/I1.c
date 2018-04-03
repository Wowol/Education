#include "stdio.h"

#define MAXWORDLENGTH 10
#define MAX 100

void swap(unsigned long long a, unsigned long long b, char *tab)
{
    char c;
    c = tab[a];
    tab[a] = tab[b];
    tab[b] = c;
}

unsigned long long changeToDecimal(char *number, unsigned long long system)
{
    unsigned long long result = 0;

    for (unsigned long long x = 0; number[x] != '\0'; x++)
    {
        unsigned long long s = (number[x] <= 57 ? number[x] : number[x]-55);
        result += number[x] <= 57 ? number[x] - '0' : number[x]-55;
        result *= system;
    }
    result /= system;

    return result;
}

void changeFromDecimal(unsigned long long n, unsigned long long system, char * result)
{
    result[0] = 0 + '0';
    result[1] = '\0';
    unsigned long long x = 0;
    for (; n > 0; x++)
    {
        result[x] = n % system + '0';
        n /= system;
    }
    if (x != 0)
    {
        result[x] = '\0';
    }

    for (unsigned long long y =0; y<x; y++)
    {
        int diff = result[y] - 57;
        if (diff > 0)
        {
            result[y] = 'A' + diff - 1;
        }
    }

    for (unsigned long long y = 0; y < x / 2; y++)
    {
        swap(x - y - 1, y,result);
    }

}

void test()
{
    for (unsigned long long system = 2; system <= 16; system++)
    {
        for (unsigned long long x=0; x<100000; x++)
        {
            char c[MAX];
            changeFromDecimal(x, system, c);

            unsigned long long dec = changeToDecimal(c, system);
            if (dec != x) 
            {
                printf("%i %i \n", x, dec);
            }
        }
    }
    scanf("%i");
}

void doIt()
{
    char operation[MAXWORDLENGTH];
    unsigned long long systemFrom;
    unsigned long long systemTo;
    char number[MAX];

    char result[MAX];
    scanf("%s %llu %llu %s", &operation, &systemFrom, &systemTo, &number);
    if (operation[0]=='C')
    {
        unsigned long long decimal = changeToDecimal(number, systemFrom);
        changeFromDecimal(decimal, systemTo, result);
        printf("%s\n", result);
    }
}



unsigned long long main()
{
    unsigned long long z;
    scanf("%i", &z);
    while (z--)
    {
        doIt();
    }
}
