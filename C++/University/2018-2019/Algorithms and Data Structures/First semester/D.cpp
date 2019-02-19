#include <iostream>
#include <algorithm>

#define MAX 408

using namespace std;

unsigned long long result[MAX][MAX];
int path[MAX][MAX];
int tab[MAX];
int length, n;

void input()
{
    cin >> length >> n;
    tab[0] = 0;
    for (int x = 1; x <= n; x++)
    {
        cin >> tab[x];
    }
    n += 2;
    tab[n - 1] = length;
}

void printPath(int begin, int end)
{
    if (end == begin || end == begin + 1)
    {
        return;
    }
    int cutPlace = path[end - begin][begin];
    cout << tab[cutPlace] << " ";
    printPath(begin, cutPlace);
    printPath(cutPlace, end);
}

void calculate()
{
    sort(tab, tab + n);
    for (int i = 0; i < n; i++)
    {
        result[1][i] = 0;
        result[0][i] = 0;
    }

    for (int d = 2; d < n; d++)
    {
        for (int begin = 0; begin < n - d; begin++)
        {
            unsigned long long minimum = INT64_MAX;
            for (int lengthFromFirst = 1; lengthFromFirst < d; lengthFromFirst++)
            {
                unsigned long long value = result[lengthFromFirst][begin] + result[d - lengthFromFirst][begin + lengthFromFirst];
                value += max(tab[lengthFromFirst + begin] - tab[begin], tab[begin + d] - tab[begin + lengthFromFirst]);
                if (value < minimum)
                {
                    minimum = value;
                    path[d][begin] = lengthFromFirst + begin;
                }
            }
            result[d][begin] = minimum;
        }
    }

    cout << result[n - 1][0] << endl;

    printPath(0, n - 1);
    cout << endl;
}

void doIt()
{
    input();
    calculate();
}

int main()
{
    int z;
    cin >> z;
    while (z--)
    {
        doIt();
    }
}