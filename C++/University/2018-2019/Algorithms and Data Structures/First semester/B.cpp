#include <iostream>
#define MAX 1005
#define MAX_WEIGHT 10005

using namespace std;

int values[MAX];
int weights[MAX];
int n;
int maxWeight;
int result[2][MAX_WEIGHT];

void input()
{
    cin >> n;
    cin >> maxWeight;

    for (int x = 1; x <= n; x++)
    {
        cin >> weights[x] >> values[x];
    }
}

void clear()
{
    for (int j = 0; j <= maxWeight; j++)
    {
        result[0][j] = 0;
    }
}

int algo()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= maxWeight; j++)
        {
            int notTaken = result[(i - 1) % 2][j];
            int taken = weights[i] > j ? 0 : values[i] + result[(i - 1) % 2][j - weights[i]];
            result[i % 2][j] = max(taken, notTaken);
        }
    }

    return result[n % 2][maxWeight];
}

void doIt()
{
    input();
    clear();
    cout << algo() << endl;
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