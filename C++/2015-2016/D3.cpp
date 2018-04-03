#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int k;
vector<int> factors;
vector<int> firsts;
const int MAX = 82;
int matrixFactors[MAX][MAX];
int wynikGlob[MAX][MAX];
int wynikKoncowy[MAX][MAX];

int recursion(int n)
{
     int sum = 0;
     if (n<=k)
     {
        return firsts[n];
     }

     for (int x=1; x<=k; x++)
     {
         sum+=factors[x]*recursion(n-x);
         sum = sum%1000;
     }
     return sum;
}


int liczKolejne(int n)
{
   // for (int y=1; y<=k; y++)
   // {
        unsigned long long sum = 0;
        for (int x=1; x<=k; x++)
        {
            sum += wynikKoncowy[1][x]*firsts[n-x+1];
            sum = sum%1000;
        }

      //  firsts.push_back(sum);
        return sum;
}

void mnozMacierz(int m1[][MAX], int m2[][MAX])
{
    int a = 1;
    int b = 1;


    for (int x=1; x<=k; x++)
    {
        for (int y=1; y<=k; y++)
        {
            wynikGlob[y][x] = 0;
        }
    }

    for (a=1; a<=k; a++)
    {
        for (b=1; b<=k; b++)
        {
            for (int v=1; v<=k; v++)
            {
                int p = m1[a][v];
                int q = m2[v][b];
                unsigned long long z = q*p;
                z = z%1000;
                wynikGlob[a][b]+=z;
                wynikGlob[a][b] = wynikGlob[a][b]%1000;
            }
        }
    }


}

int power(int n[][MAX], int p)
{
   //[MAX][MAX];
    for (int x=1; x<=k; x++)
    {
        wynikKoncowy[x][x] = 1;
    }

    while (p>0)
    {
        if (p%2==1)
        {
            mnozMacierz(wynikKoncowy, n);
            for (int x=1; x<=k; x++)
            {
                for (int y=1; y<=k; y++)
                {
                    wynikKoncowy[y][x] = wynikGlob[y][x];
                }
            }
        }
        mnozMacierz(n, n);
        for (int x=1; x<=k; x++)
        {
            for (int y=1; y<=k; y++)
            {
                n[y][x] = wynikGlob[y][x];
            }
        }
        p/=2;
    }

/*    for (int x=1; x<=k; x++)
    {
        for (int y=1; y<=k; y++)
        {
            cout << wynikKoncowy[y][x] << " ";
        }
        cout << endl;
    }*/
}


void program()
{

    factors.clear();
    firsts.clear();

    factors.push_back(-1);


    int m;
    cin >> k >> m;



    for (int x=0; x<k; x++)
    {
        int a;
        cin >> a;
        factors.push_back(a);
    }

    for (int x=1; x<=k; x++)
    {
        for (int y=1; y<=k; y++)
        {
            wynikKoncowy[y][x] = 0;
            matrixFactors[y][x] = 0;
        }
    }

    for (int y=2; y<=k; y++)
    {
        matrixFactors[y][y-1] = 1;
    }


    for (int x=0; x<k; x++)
    {
        int a;
        cin >> a;
        firsts.push_back(a%1000);
    }
    firsts.push_back(-1);

    reverse(firsts.begin(), firsts.end());
    for (int x=1; x<=k; x++)
    {
        matrixFactors[1][x] = factors[x]%1000;
    }

    if (m-k>0)
    {
        power(matrixFactors, m-k);
        cout << setw(3) << setfill('0') << liczKolejne(k) << endl;
       // cout << setw(3) << setfill('0') << recursion(m) << endl;
    }
    else
    {
        cout << setw(3) << setfill('0') << firsts[m] << endl;
    }





    //for (int x=k; x<=m; x++)
   // {
   //     liczKolejne(x);
   //     cout << setw(3) << setfill('0') << recursion(x) << " ";

   // }

   // cout << setw(3) << setfill('0') << firsts[m] << endl;




    //





     //cout << recursion(m);

}

int main()
{
    int z;
    cin >> z;
    while (z--)
    {
         program();
    }
}
