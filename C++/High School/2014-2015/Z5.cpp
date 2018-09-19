#include <iostream>

using namespace std;
int wyn[32];

int main()
{
    wyn[1] = 1;
    for (int x=2; x<31; x++)
    {
        wyn[x] = wyn[x-1]*2+1;
    }

    int n;
    cin >> n;
    while (n--)
    {
        int k;
        cin >> k;
        cout << wyn[k] << endl;
    }
}
