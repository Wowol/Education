#include <stdio.h>
#include <stdbool.h>

#define MAX 10005

int n;
int tab[MAX];

void swap(int a, int b)
{
    int c = tab[a];
    tab[a] = tab[b];
    tab[b] = c;
}

void bubbleSort()
{
    bool sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (int x=0; x<n-1; x++)
        {
            if (tab[x]>tab[x+1])
            {
                sorted = false;
                swap(x, x+1);
            }
        }
    }
}

void selectionSort()
{
    for (int y=0; y<n; y++)
    {
        int indexOfMinElement = y;
        for (int x=y; x<n; x++)
        {
            if (tab[x] < tab[indexOfMinElement])
            {
                indexOfMinElement = x;
            }
        }
        swap(y, indexOfMinElement);
    }
}

void insertionSort()
{
    for (int x=1; x<n; x++)
    {
        for(int y=x; y>=1; y--)
        {
            if (tab[y-1]>tab[y])
            {
                swap(y-1, y);        
            }
            else
            {
                break;
            }
        }
    }
}

void doIt()
{
    scanf("%i", &n);
    for (int x=0; x<n; x++)
    {
        scanf("%i", &tab[x]);
    }
    selectionSort();
    //bubbleSort();
   // insertionSort();

    for (int x=0; x<n; x++)
    {
        printf("%i ", tab[x]);
    }
    printf("\n");
    unsigned long long result = 0;

    for (int x=n-1; x>=2; x--)
    {
        int z = x-1;
        for (int y=0; y<z; y++)
        {
            if (tab[y]+tab[z]>tab[x])
            {
                result+=z-y;
                z--;
                y--;
            }
        }
    }
    
    printf("%llu\n", result);
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