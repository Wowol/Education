#include <iostream>

using namespace std;

unsigned long long potegamodulo(unsigned long long a, unsigned long long b, unsigned long long c)
{
    unsigned long long wynik = 1;
    unsigned long long n = a%c; //b=potega, c=modulo7384

    for (int i=1; i<=b; i<<=1) // zamiana na postac bitowa
    {
        n = n%c;
        if ((b&i)!=0)
        {
            wynik = wynik * n;
            wynik = wynik % c;
        }
        n = n*n;

    }

    return wynik;


}

int main()
{
    unsigned long long n;
    cin >> n;
    unsigned long long a,b,c;

    for (int i=0; i<n; i++)
    {
        cin >> a >> b >> c;
        cout << potegamodulo(a,b,c) << endl;
    }

}
