#include <iostream>
#include <cstring>

#define MAX 1000010

using namespace std;

int nieParzysty[MAX];
int parzysty[MAX];


int przygotuj(string s)
{
    string slowo;
    slowo = '&'+s+'*';
    int dl = slowo.length();

  /*  for (int x=0; x<dl+4; x++)
    {
        parzysty[x] = 1;
        nieParzysty[x] = 0;
    }*/

    int r = 0;
    int x =0;
    while (x<dl)
    {
        while (slowo[x-r]==slowo[x+r+1])
        {
            r++;
        }
        nieParzysty[x] = r;
        int k = 1;
        while (nieParzysty[x-k]!=r-k)
        {
            if (k>=r)
            {
                break;
            }
            nieParzysty[x+k] = min(nieParzysty[x-k], r-k);
            k++;
        }
        r = max(0, r-k);
        x += k;
    }

    x =0;
    while (x<dl)
    {
        while (slowo[x-r]==slowo[x+r])
        {
            r++;
        }
        parzysty[x] = r;
        int k = 1;
        while (parzysty[x-k]!=r-k)
        {
            if (k>=r)
            {
                break;
            }
            parzysty[x+k] = min(parzysty[x-k], r-k);
            k++;
        }
        r = max(0, r-k);
        x += k;
    }
}

int doIt()
{
    string s;
    cin >> s;
    przygotuj(s);
    int n;
    cin >> n;
    while (n--)
    {
        int a,b;
        cin >> a >> b;
        if ((b-a)%2==0)
        {
            int dl = ((b-a)/2)+1;
            int p = parzysty[(a+b)/2];
            if (p>=dl)
            {
                 cout << "TAK" << endl;
            }
            else
            {
                cout << "NIE" << endl;
            }
        }
        else
        {
            int dl = (b-a+1)/2;
            int sr = (a+b)/2;
            int p = nieParzysty[sr];
            if (p>=dl)
             {
                 cout << "TAK" << endl;
            }
            else
            {
                cout << "NIE" << endl;
            }
        }
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
