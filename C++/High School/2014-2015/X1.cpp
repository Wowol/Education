#include <iostream>

using namespace std;

int doIt()
{
    int n;
    int liczba = 1;
    int sumka = 1;
    cin >> n;
    for (int x=2; sumka<n; x++)
    {
        int pomoc = (n-sumka)/x;
        if (n-sumka==x*pomoc)
        {
            cout << n << " = ";
            cout << pomoc;
            pomoc++;
            for(int y=1; y<x; y++)
            {
               cout << " + " << pomoc;
               pomoc++;
            }
            cout << endl;
            return 0;
        }
        liczba++;
        sumka += liczba;
    }
    cout << "IMPOSSIBLE" << endl;


}

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        doIt();
    }
}
