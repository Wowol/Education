#include <iostream>
#define MAX 2008

using namespace std;

int n;
int pizza[MAX];
int result[MAX][MAX];
int sums[MAX];

int getSum(int d, int begin)
{
    if (d + begin + 1 < n)
    {
        return sums[begin + d + 1] - sums[begin];
    }
    else
    {
        int k = (d + begin + 1) % n;
        return sums[n] - sums[begin] + sums[k];
    }
}

void doIt()
{
    cin >> n;
    for (int x = 0; x < n; x++)
    {
        cin >> pizza[x];
    }

    sums[0] = 0;
    for (int x = 1; x <= n; x++)
    {
        sums[x] = sums[x - 1] + pizza[x - 1];
    }

    // while(true)
    // {
    //     int a, b;
    //     cin >> a >> b;
    //     cout << getSum(a, b) << endl;
    // }

    for (int x = 0; x < n; x++)
    {
        result[0][x] = pizza[x];
    }

    for (int d = 1; d < n - 1; d++)
    {
        for (int x = 0; x < n; x++)
        {
            int a = pizza[x] + getSum(d - 1, (x + 1) % n) - result[d - 1][(x + 1) % n];
            int b = pizza[(x + d) % n] + getSum(d - 1, x) - result[d - 1][x];
            result[d][x] = max(a, b);
        }
    }

    int m = -1;
    for (int x = 0; x < n; x++)
    {
        int s = getSum(n - 2, x + 1);
        int r = result[n - 2][(x + 1) % n];
        int p = pizza[x];
        m = max(m, p + s - r);
    }

    cout << m << " " << getSum(n-1, 0)-m << endl;
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