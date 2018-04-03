#include <iostream>
#include <cstdlib>
#define MAX 100005

using namespace std;

unsigned long long pot(unsigned long long n)
{
    if (n==0) return 1;
    unsigned long long wynik = 1;
    for (int x=0; x<n; x++)
    {
        wynik = wynik * 3;
    }
    return wynik;
}


void doIt()
{
    string n;
    int nowa = 0;
    cin >> n;
    char wynik[MAX];
    bool ujemna = false;

    int wyn[MAX];

    nowa = atoi(n.c_str());
    if (nowa!=0)
    {
        if (n[0]=='-')
        {
            ujemna = true;
            nowa = nowa*-1;
        }
        bool naPoczatku = false;
        int tab[323] = {0};
        int k = 0;
        while (nowa!=0)
        {
            tab[k] = nowa % 3;
            nowa = nowa / 3;
            k++;
        }
        for (int i=k-1; i>=0; i--)
        {
            wyn[k-1-i] = tab[i];
//            cout << tab[i];
        }

        for (int i=k-1; i>=0; i--)
        {
            if (wyn[i]>2)
            {
                if (i!=0) wyn[i-1]++;
                else
                {
                    naPoczatku = true;
                }

                wyn[i] = wyn[i]-3;
            }
            if (wyn[i]==2)
            {
                wynik[i] = '-';
                if (i!=0)
                {
                    wyn[i-1]++;
                }
                else
                {
                    naPoczatku = true;
                }
            }

            if (wyn[i]==1)
            {
                wynik[i] = '+';
            }

            if (wyn[i]==0)
            {
                wynik[i] = '0';
            }
        }

        if (naPoczatku)
        {
            if (ujemna) cout << '-';
            else
                cout << '+';
        }

        for(int x=0; x<k; x++)
        {
            char c = wynik[x];
            if (ujemna)
            {
                if (c=='+') cout << '-';
                if (c=='-') cout << '+';
                if (c=='0') cout << '0';
            }
            else
            {
                cout << c;
            }
        }
        cout << endl;
    }
    else
    {
        int s = n.size();
        int wynik = 0;
        for (int x=0; x<s; x++)
        {
            if (n[x]=='+')
            {
                wynik = wynik + pot(s-x-1);
            }
            if (n[x]=='-')
            {
                wynik = wynik - pot(s-x-1);
            }
        }
        cout << wynik << endl;
    }

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
