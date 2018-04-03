#include <iostream>
#include <vector>
#include <list>



using namespace std;

const int MAX = (3e6)+3;
int tab[MAX];
int potegaDwojki = 1;
int t[MAX];
vector<int> tree(MAX);

void createTree(int n)
{
    int k = 1;
    while (k<n)
    {
        k*=2;
    }
    potegaDwojki = k;
    int T = n;

    for (int x=k; x<n+k; x++)
    {
        tree[x] = 1;
    }
    for (int x=n+k; x<2*k; x++)
    {
        tree[x] = 0;
    }
    int ileElementow = k;
    while (k!=1)
    {
       // int stareElemtny = ileElementow;
       k = k / 2;
       for (int x=k; x<2*k; x++)
       {
           tree[x] = tree[2*x] + tree[2*x+1];
       }
    }
}

int getValue(int szukane)
{
    int x = 1;
    szukane = tree[x]-szukane;
    while (x<potegaDwojki)
    {
        tree[x]--;
        if (tree[x*2]>=szukane)
        {
            x = x*2;
        }
        else
        {
            szukane = szukane-tree[x*2];
            x = x*2+1;
        }
    }
    tree[x] = 0;
    return x-potegaDwojki+1;
}


void JUSTdoIt()
{
    int n;
    cin >> n;
    createTree(n);

    for (int x=0; x<n; x++)
    {
        cin >> tab[x];
    }

    for (int x=n-1; x>=0; x--)
    {
        int liczba = tab[x];
        t[x] = getValue(liczba);
    }

    for (int x=0; x<n; x++)
    {
        cout << t[x] << " ";
    }
    cout << endl;

}

int main()
{
  //  ios_base::sync_with_stdio(true);
    int n;
    cin >> n;
    while (n--)
    {
        JUSTdoIt();
    }
}
