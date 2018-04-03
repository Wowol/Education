#include <iostream>

using namespace std;

int ResztaFibbonaci()
{
    unsigned long long n;
    cin >> n;
    unsigned long long pierwsza = 0;
    unsigned long long druga = 1;

    for (int x=0; x<n; x++)
    {
        druga = (pierwsza + druga);
        pierwsza = (druga-pierwsza) % n;
    }

    cout << pierwsza << endl;

}


int main()
{
    unsigned long long  n;
    cin >> n;
    while (n--)
    {
        ResztaFibbonaci();
    }

}
