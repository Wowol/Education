#include <iostream>

using namespace std;

__int128 gcd(__int128 a, __int128 b)
{
    __int128 c;
    while (b!=0)
    {
      c = a%b;
      a = b;
      b = c;
    }

    return a;

}

__int128 rozszerzonyEuklides(__int128 a, __int128 n)
{
  __int128 a0,n0,p0,p1,q,r,t;

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

struct Dzialanie
{
     __int128 modulo;
     __int128 wynik;
};

void doIt()
{
    long long nn;
    __int128 n;
    cin >> nn;
    n = nn;
    __int128 iloraz = 1;
    bool czyRobic = true;
    __int128 ost = 0;
    Dzialanie dzialania[5];
    for (__int128 i=0; i<n; i++)
    {
        long long aa;
        long long wynika;
        long long moduloa;
        __int128 a, wynik, modulo;
        char mnozenie, rownosc;
        char iks;
        string stringmodxD;

        cin >> aa >> mnozenie >> iks >> rownosc >> wynika >> stringmodxD >> moduloa;
        modulo = moduloa;
        a = aa;
        wynik = wynika;

        if (!czyRobic) continue;

        //cout << a << " " << wynik << " " << modulo << endl;

        __int128 dzielnik = gcd(a, modulo);
        if (wynik%dzielnik != 0)
        {
            cout << "NIE" << endl;
            czyRobic = false;
            continue;
        }
         a /= dzielnik;
         wynik /= dzielnik;
         modulo /= dzielnik;

        if (a==0)
        {
            a = 1;
            modulo = 1;
        }
         __int128 inwersja = rozszerzonyEuklides(a, modulo);
         wynik *= inwersja;
         wynik = wynik % modulo;
         a = 1;

        Dzialanie dzialanie;
        dzialanie.modulo = modulo;
        dzialanie.wynik = wynik;

        dzialania[i] = dzialanie;
        iloraz *= modulo;
    }

    if (!czyRobic)
    {
        return;
    }

    for (__int128 i=0; i<n; i++)
    {
        Dzialanie dzialanie;
        __int128 modulo = dzialania[i].modulo;
        __int128 wynik = dzialania[i].wynik;
         __int128 q = iloraz/modulo;
        if (gcd(modulo, q)!=1)
        {
            cout << "NIE" << endl;
            return;
        }
        __int128 s = rozszerzonyEuklides(iloraz/modulo, modulo);

         __int128 p = wynik*s;
         p = p%iloraz;
         __int128 z = iloraz/modulo;
         __int128 asd = p*z;
         asd = asd%iloraz;
         ost += asd;
        // ost += p*z;
         ost = ost%iloraz;
    }

   //   cout << "asd";
  //  return;


    cout << (long long)(ost%iloraz) << endl;


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
