#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int MAX = 1e7;
unsigned long long d[MAX];

void doIt()
{
    char tab[25][25];

    unsigned long long n;
    cin >> n;
    for (unsigned long long y=0; y<n; y++)
    {
        for (unsigned long long x=0; x<n; x++)
        {
            cin >> tab[y][x];
        }
    }
    unsigned long long potega = 1 << n;
    for (unsigned long long x=0; x<=potega; x++)
    {
        d[x] = 0;
    }
    d[0] = 1;

    for (unsigned long long x=1; x<potega; x++)
    {
        unsigned long long zapaloneBity = __builtin_popcountll(x);
        for (unsigned long long y=0; y<n; y++)
        {
            if (x & (1<<y) && tab[zapaloneBity-1][y]=='.')
            {
                d[x] += d[x & ~(1 << y)];
            }
        }
    }

    cout << d[potega-1] << endl;


}

int main()
{
    int q;
    cin >> q;
    while (q--)
    {
        doIt();
    }
}
