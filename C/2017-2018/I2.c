#include "stdio.h"
#include "stdbool.h"
#include "string.h"

#define MAXWORDLENGTH 10
#define MAX 100

void swap(long long a, long long b, char *tab)
{
    char c;
    c = tab[a];
    tab[a] = tab[b];
    tab[b] = c;
}

long long changeToDecimal(char *number, long long system)
{
    unsigned long long result = 0;
    long long realResult = 0;
    long long highestPower = strlen(number) - 1;

    for (long long x = 1; number[x] != '\0'; x++)
    {
        result += number[x] - '0';
        result *= system;
    }

    result /= system;
    realResult = result;

    if (number[0] == '1')
    {
        realResult = result - (unsigned long long)((unsigned long long)(1) << highestPower);
    }

    return realResult;
}

void addOne(char *tab, long long *size)
{
    for (long long y = 0; y < *size; y++)
    {
        if (tab[y] == '0')
        {
            tab[y] = '1';
            return;
        }
        else
        {
            tab[y] = '0';
        }
    }

    for (long long y = 0; y < *size; y++)
    {
        tab[y] = '0';
    }
    tab[*size] = '1';
    *size += 1;
}

void inversion(char *tab, long long size)
{
    for (long long y = 0; y < size; y++)
    {
        tab[y] = tab[y] == '1' ? '0' : '1';
    }
}

bool changeFromDecimal(long long n, long long system, char *result, long long reg)
{
    if (n > 0 && (unsigned long long)((unsigned long long)(1) << (reg - 1)) <= n)
    {
        return false;
    }

    if (n < 0 && (unsigned long long)((unsigned long long)(1) << (reg - 1)) < n * -1)
    {
        return false;
    }

    long long begin = n;
    if (n < 0)
    {
        n *= -1;
    }

    result[0] = 0 + '0';
    result[1] = '\0';
    long long x = 0;
    for (; n > 0; x++)
    {
        result[x] = n % system + '0';
        n /= system;
    }
    if (x != 0)
    {
        result[x] = '0';
        result[++x] = '\0';
    }

    if (begin < 0)
    {
        inversion(result, x);
        addOne(result, &x);
    }

    for (; x < reg; x++)
    {
        result[x] = begin < 0 ? '1' : '0';
    }
    result[x] = '\0';

    for (long long y = 0; y < x / 2; y++)
    {
        swap(x - y - 1, y, result);
    }

    return true;
}

void pr(char *tab, long long reg)
{
    long long len = strlen(tab);
    for (long long x = len - reg; tab[x] != '\0'; x++)
    {
        printf("%c", tab[x]);
    }
    printf("\n");
}

void test()
{
    for (long long  x = -13232323323; x < 123131313; x++)
    {
        char c[MAX];
        if (!changeFromDecimal(x, 2, c, 64))
        {
            continue;
        }

        long long  dec = changeToDecimal(c, 2);
        if (dec != x)
        {
            printf("%lld %lld \n", x, dec);
        }
    }
    printf("DONE");
    
    scanf("%i");
}

void doIt()
{
   //  test();
    // return;

    char operation[MAXWORDLENGTH];
    scanf("%s", &operation);
    
    if (operation[0] == 'W')
    {
        char result[MAX];
        long long reg;
        long long number;

        scanf("%lld %lld", &reg, &number);
        if (changeFromDecimal(number, 2, result, reg))
        {
            pr(result, reg);
        }
        else
        {
            printf("ERROR\n");
        }
    }

    if (operation[0] == 'R')
    {
        char binaryNumber[MAX];
        scanf("%s", &binaryNumber);

        long long decimal = changeToDecimal(binaryNumber, 2);
        printf("%lld\n", decimal);
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
