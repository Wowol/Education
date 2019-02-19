#include <iostream>
#include <algorithm>
#define MAX 1000005

using namespace std;


long long result[MAX];
int currentIndex;

int tapeLength;
int tapePrice;

int costs[MAX];
int positions[MAX];

int n;


long long computeResult(int i)
{
    if (i == -1)
    {
        return 0;
    }

    if (result[i] != -1)
    {
        return result[i];
    }

    currentIndex = lower_bound(positions, positions+n, positions[i]-tapeLength) - positions - 1;

    result[i] = min(computeResult(i - 1) + costs[i], tapePrice + computeResult(currentIndex));

    return result[i];
}

void clear()
{
    for (int x=0; x<n+2; x++)
    {
        result[x] = -1;
    }
}

void doIt()
{
    cin >> n;
    clear();
    for (int x = 0; x < n; x++)
    {
        cin >> positions[x] >> costs[x];
    }

    currentIndex = n-1;

    cin >> tapeLength >> tapePrice;

    cout << computeResult(n-1) << endl;
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