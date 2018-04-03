#include <iostream>
#include <math.h>

using namespace std;

// int gcd(int a, int b)
// {
//     if (a == 0)
//     {
//         return b;
//     }

//     if (b == 0)
//     {
//         return a;
//     }

//     if ((a & 1) == 0 && (b & 1) == 0)
//     {
//         return (gcd((a >> 1), (b >> 1)) << 1);
//     }

//     if ((a & 1) == 0)
//     {
//         return gcd((a >> 1), b);
//     }

//     if ((b & 1) == 0)
//     {
//         return gcd(a, (b >> 1));
//     }

//     return gcd((abs(a - b) >> 1), min(a, b));
// }

int gcdO1(int a, int b)
{
    int wynik = 0;
    while (true)
    {
        if (a == 0)
        {
            return (b << wynik);
        }

        if (b == 0)
        {
            return (a << wynik);
        }

        if ((a & 1) == 0 && (b & 1) == 0)
        {
            wynik++;
        }

        if ((a & 1) == 1 && (b & 1) == 1)
        {
            int c = min(a, b);
            a = (abs(a - b) >> 1);
            b = c;
            continue;
        }

        if ((a & 1) == 0)
        {
            a = (a >> 1);
        }
        if ((b & 1) == 0)
        {
            b = (b >> 1);
        }
    }
}

void doIt()
{
    int a, b;
    cin >> a >> b;
    cout << gcdO1(a, b) << endl;
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