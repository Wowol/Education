#include <iostream>
#include <set>
#define MAX 1005

using namespace std;

int tab[MAX][MAX];
int suma[MAX][MAX];
int t[MAX];
int n;

int sprawdz(int i, int j)
{
    int sumka;
    if (tab[i-1][j-1]!=-1 && i!=-1 && j!=-1)
    {
        suma[i-1][j]=suma[i-1][j-1]+t[j];
        sumka = suma[i-1][j];
        tab[i-1][j]=sumka-min(tab[i][j], tab[i-1][j-1]);

        sprawdz(i-1, j);
    }
}

int doIt()
{
    int x;
    ios_base::sync_with_stdio;

    cin >> n;
    for (int i=1; i<=n; i++)
    {
        cin >> x;
        t[i] = x;
        suma[i][i]=x;
        tab[i][i] = x;
        sprawdz(i, i);
    }
    cout << tab[1][n] << endl;
}


int main()
{
    int k;
    cin >> k;
    n = MAX-3;
    while (k--)
    {
        for (int x=0; x<n+2; x++)
        {
            t[x]=-1;
            for (int z=x; z<n+2; z++)
            {
                tab[x][z]=-1;
            }
        }
        doIt();
    }
}
