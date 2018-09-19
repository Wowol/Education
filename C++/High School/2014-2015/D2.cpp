#include <iostream>
#include <algorithm>

using namespace std;

int doIt()
{
    int n;
    int m;
    int tab[100005];
    int wyn[100005];
    tab[0]=0;
    wyn[0]=0;
    cin >> n;
    for (int i=1; i<=n; i++)
    {
        cin >> tab[i];
        if (i==1)
        {
            wyn[i]=tab[i];
        }

        if (i==2)
        {
            wyn[i]=wyn[i-1]+tab[i];
        }


 /*       if (i==3)
        {
            wyn[i]=max(wyn[i-1],wyn[i-2]+tab[i]);
        }*/
        if (i>=3)
        {
            wyn[i]=max( max(wyn[i-1],wyn[i-2]+tab[i]), wyn[i-3]+tab[i-1]+tab[i]);
        }
    }

    cout << wyn[n] << endl;


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
