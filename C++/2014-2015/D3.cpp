#include <iostream>
#define MAX 1005
using namespace std;

int doIt()
{
    int a,b;
    int tab[MAX][MAX] = {0};
    int wynik[MAX][MAX] = {0};
    int droga[MAX][MAX] = {0};
    char koncowa[MAX*MAX];
    int k=0;

    cin >> a >> b;
    for (int y=1; y<=b; y++)
    {
        for (int x=1; x<=a; x++)
        {
            cin >> tab[x][y];
            wynik[x][y] = tab[x][y] + max (wynik[x-1][y], wynik[x][y-1]);
            if (wynik[x-1][y]>wynik[x][y-1])
            {
                droga[x][y]=1; // 1 - lewo
                k++;
            }

            if (wynik[x][y-1]>=wynik[x-1][y])
            {
                droga[x][y]=2; // 2 - gora
                k++;
            }

            if (x==1 && y!=1)
            {
                droga[x][y]=2;
            }

            if (y==1 && x!=1)
            {
                droga[x][y]=1;
            }
        }
    }

    droga[2][1]=1;
    droga[1][2]=2;

    int o = a;
    int p = b;

    for (int i=0; i<a+b-2; i++)
    {
        if (droga[o][p]==2)
        {
            koncowa[i]='v';
            p--;
            continue;
        }

        if (droga[o][p]==1)
        {
            koncowa[i]='>';
            o--;
            continue;
        }
    }

    cout << wynik[a][b] << " ";

    for (int x=a+b-2-1; x>=0; x--)
    {
        cout << koncowa[x];
    }

    cout << endl;


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
