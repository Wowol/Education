#include <iostream>
#include <set>
#include <cmath>
#include <map>

using namespace std;

long long rozszerzonyEuklides(long long a, long long n)
{
  long long a0,n0,p0,p1,q,r,t;
  p0 = 0;
  p1 = 1;
  a0 = a;
  n0 = n;
  q  = n0 / a0;
  r  = n0 % a0;
  while(r > 0)
  {
    t = p0 - q * p1;
    if(t >= 0)
    {
        t = t % n;
    }

    else
    {
        t = n - ((-t) % n);
    }
    p0 = p1;
    p1 = t;
    n0 = a0;
    a0 = r;
    q  = n0 / a0;
    r  = n0 % a0;
  }
  return p1;
}

 long long potega( long long x,  long long d,  long long m)
{
     long long q = 1;
    while (d>0)
    {
        if (d%2)
        {
            q*=x;
            q%=m;
        }
        x*=x;
        x%=m;
        d/=2;
    }
    return q;
}

void doIt()
{
     long long a, b, m;
    cin >> a >> b >> m;
    set< long long> secik;
     long long k = sqrt(m)+1;
     long long poprzednie = 1;
     map<int, int> indeksy;
    secik.insert(1);
    indeksy[1] = 0;
    for ( long long x=1; x<k; x++)
    {
        long long q = poprzednie*a;
        q%=m;
        map<int,int>::iterator it = indeksy.find(q);
        if (it==indeksy.end())
        {
            indeksy[q] = x;
            secik.insert(q);
        }


        poprzednie = q;
    }

     long long dziwnaLiczba = rozszerzonyEuklides(a, m);

     long long tabSpecjalna[2];

    tabSpecjalna[0] = b;
     long long podstawa = potega(dziwnaLiczba, k, m);
    tabSpecjalna[1] = (podstawa*b) % m;

    for ( long long x=0; x<2; x++)
    {
         long long s = tabSpecjalna[x];
        set< long long>::iterator it;
        it = secik.find(s);
        if (it!=secik.end())
        {
            cout << x*k+indeksy[s] << endl;
            return;
        }
    }

    for ( long long x=2; x<k; x++)
    {
         long long kolejna = potega(podstawa, x, m);
         long long s = (kolejna*b) % m;;
        set< long long>::iterator it;
        it = secik.find(s);
        if (it!=secik.end())
        {
            cout << x*k+indeksy[s] << endl;
            return;
        }
    }
    cout << "-1" << endl;



}

int main()
{
     long long z;
    cin >> z;
    while (z--)
    {
        doIt();
    }
}
