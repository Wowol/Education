#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX 10010
#define MAXWORDLENGTH 105

char tab[MAX][MAXWORDLENGTH];
char reverseTemp[MAXWORDLENGTH];

int n;
int dlugoscSlowa;

void swap(int a, int b)
{
    char c[MAXWORDLENGTH];
    strcpy(c, tab[a]);
    strcpy(tab[a], tab[b]);
    strcpy(tab[b], c);
}

// returns:
// 0, if B should be before A
// 1, if A should be before B
// 2, if A is equal to B
int aIsBeforeB(char a[], char b[])
{
    int returnValue = -1;
    for (int x = 0; x < MAXWORDLENGTH; x++)
    {
        if (tolower(a[x]) > tolower(b[x]))
        {
            return false;
        }

        if (tolower(a[x]) < tolower(b[x]))
        {
            return true;
        }
    }

    for (int x = 0; x < dlugoscSlowa; x++)
    {
        if (tolower(a[x]) == tolower(b[x]) && isupper(b[x]) && !isupper(a[x]))
        {
            return true;
        }

        if (tolower(a[x]) == tolower(b[x]) && !isupper(b[x]) && isupper(a[x]))
        {
            return false;
        }
    }

    return 2;
}

void insertionSort()
{
    for (int x = 1; x < n; x++)
    {
        for (int y = x; y >= 1; y--)
        {
            if (aIsBeforeB(tab[y], tab[y - 1]))
            {
                swap(y - 1, y);
            }
            else
            {
                break;
            }
        }
    }
}

char *reverse(char c[])
{
    for (unsigned int x = 0; x < dlugoscSlowa; x++)
    {
        reverseTemp[dlugoscSlowa - x - 1] = c[x];
    }
    return reverseTemp;
}

bool arraysAreEqual(char a[], char b[])
{
    for (int x = 0; x < dlugoscSlowa; x++)
    {
        if (tolower(a[x]) != tolower(b[x]))
        {
            return false;
        }
    }

    return true;
}

void doIt()
{
    scanf("%i", &n);
    for (int x = 0; x < n; x++)
    {
        scanf("%s", tab[x]);
        dlugoscSlowa = strlen(tab[x]);
    }
    insertionSort();

    int numberOfResults = 0;

    for (int x = 0; x < n; x++)
    {
        bool found = false;
        if (x == 0 || !arraysAreEqual(tab[x], tab[x - 1]))
        {
            reverse(tab[x]);
            for (int y = x + 1; y < n; y++)
            {
                if (arraysAreEqual(tab[y], reverseTemp))
                {
                    if (!found)
                    {
                        printf("%s %s\n", tab[x], tab[y]);
                        numberOfResults++;                        
                        break;
                    }
                }
            }
        }
    }
    printf("%i\n", numberOfResults);
    

            // int l = x+1;
            // int r = n-1;
            // int m;
            // while (l<=r)
            // {
                
            // }

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