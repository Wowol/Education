#include <iostream>
#define MAX 10000007

using namespace std;

int tab[MAX];
int n;

int upperBound(int value, int l)
{
    int r = n;
    while (l < r)
    {
        int m = (l + r) / 2;
        if (tab[m] > value)
        {
            r = m;
        }
        else if (tab[m] < value)
        {
            l = m + 1;
        }
        else if (tab[m] == value)
        {
            return m + 1;
        }
    }
    return r;
}

bool function(int result, int routerNumber)
{
    int currentPoint = 0;
    int p;
    for (int x = 0; x < routerNumber; x++)
    {
        p = tab[currentPoint] + result * 2;
        currentPoint = upperBound(p, currentPoint);
        if (currentPoint == n)
        {
            return true;
        }
    }
    if (tab[n - 1] == p)
    {
        return true;
    }
    return false;
}

void doIt()
{
    cin >> n;
    for (int x = 0; x < n; x++)
    {
        int temp;
        cin >> temp;
        tab[x] = x == 0 ? temp : temp + tab[x - 1];
    }
    tab[n] = INT32_MAX;

    int k;
    cin >> k;
    while (k--)
    {
        int routerNumber;
        cin >> routerNumber;

        int l = 0;
        int r = tab[n - 1];
        while (l < r)
        {
            int m = (l + r) / 2;
            bool result = function(m, routerNumber);
            if (result)
            {
                r = m;
            }
            else
            {
                l = m + 1;
            }
        }
        cout << r << endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    int z;
    cin >> z;
    while (z--)
    {
        doIt();
    }
}