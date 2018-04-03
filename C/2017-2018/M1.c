#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int *tab;
int *closest;

void doIt()
{
    int n;
    scanf("%d", &n);

    tab = malloc(n * sizeof(int));
    closest = malloc(n * sizeof(int));

    for (int x = 0; x < n; x++)
    {
        scanf("%d", tab + x);
        *(closest + x) = -1;
    }

    int closestGood = -1;

    if (n > 1)
    {
        if (*(tab + n - 1) < *(tab + n - 2))
        {
            closestGood = n - 1;
        }

        *(closest + n - 1) = closestGood;
        *(closest + n - 2) = closestGood;
    }

    for (int x = n - 2; x >= 1; x--)
    {
        if (*(tab + x) < *(tab + x - 1) && *(tab + x) < *(tab + x + 1))
        {
            closestGood = x;
        }
        *(closest + x) = closestGood;
        *(closest + x - 1) = closestGood;
    }

    if (n == 1 || *(tab + 0) < *(tab + 1))
    {
        *(closest + 0) = 0;
    }

    int k = sqrt(n)+1;

    int maxCounter = -1;
    int bestK = -1;

    for (int x = 1; x <= k; x++)
    {
        int counter = 0;
        int y = 0;

        while (y < n)
        {
            int p = *(closest + y);

            if (p == -1)
            {
                break;
            }

            counter++;
            if (counter == x || p == n - 1)
            {
                break;
            }

            y = p + x;
        }

        if (counter > maxCounter)
        {
            maxCounter = counter;
            bestK = x;
        }

    }

    printf("%d\n", maxCounter);

    int y = 0;

    int counter = 0;
    while (y < n)
    {
        int p = *(closest + y);

        if (p == -1)
        {
            break;
        }

        counter++;

        printf("%d ", p);
        if (counter == bestK || p == n - 1)
        {
            break;
        }

        y = p + bestK;
    }
    printf("\n");
}

int main()
{
    int z;
    scanf("%d", &z);
    while (z--)
    {
        doIt();
        free(tab);
        free(closest);
    }
}