#include <iostream>
#include <math.h>

using namespace std;

int gcd(int a, int b)
{
    if (a == 0)
    {
        return b;
    }

    if (b == 0)
    {
        return a;
    }

    if ((a & 1) == 0 && (b & 1) == 0)
    {
        return (gcd((a >> 1), (b >> 1)) << 1);
    }

    if ((a & 1) == 0)
    {
        return gcd((a >> 1), b);
    }

    if ((b & 1) == 0)
    {
        return gcd(a, (b >> 1));
    }

    return gcd((abs(a - b) >> 1), min(a, b));
}

void doIt()
{
    int a, b;
    cin >> a >> b;
    cout << gcd(a, b) << endl;
}

int main()
{
    // printf("10: %d\n", gcd(50, 60));
    // printf("50: %d\n", gcd(100, 50));
    // printf("1: %d\n", gcd(14, 3));
    // printf("8: %d\n", gcd(64, 8));
    // printf("10: %d\n", gcd(60, 50));
    // printf("50: %d\n", gcd(50, 100));
    // printf("1: %d\n", gcd(3, 14));
    // printf("8: %d\n", gcd(8, 64));
    int z;
    cin >> z;
    while (z--)
    {
        doIt();
    }
}