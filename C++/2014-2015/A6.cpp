#include <iostream>

using namespace std;

bool pierwsza(int n)
{
    if (n==1) return false;
    if (n==2) return true;
    if (n%2==0) return false;

    for (int p=3; p*p<=n; p = p+2)
    {
        if (n%p == 0)
        {
            return false;
        }

    }
    return true;
}

int findPrimeNumber(int n)
{
    if (n%2 == 0)
    {
        return 2;
    }

    if (n%3 == 0)
    {
        return 3;
    }

    for (int i = 2; i*i<=n; i++)
    {
        if (n%i==0)
        {
            return i;
         /*   if (pierwsza(i))
            {
                return i;
            }*/
        }
    }

    return n;

}


int licz(int n)
{
    int dzielnik;
    int poprzedniDzielnik=0;
    int potega = 0;
    dzielnik = findPrimeNumber(n);
    poprzedniDzielnik = dzielnik;
    cout << n << "=";
    while (true)
    {
        while (true)
        {
            dzielnik = findPrimeNumber(n);

            if (poprzedniDzielnik==dzielnik)
            {
                potega++;
                poprzedniDzielnik = dzielnik;
            }

            if (poprzedniDzielnik != dzielnik)
            {
                if (potega != 1)
                {
                    cout << poprzedniDzielnik << "^" << potega;
                }
                else
                {
                    cout << poprzedniDzielnik ;
                }

                break;
            }




            n = n/dzielnik;
        }

        potega = 0;
        poprzedniDzielnik = findPrimeNumber(n);

        if (n==1)
        {
            cout << endl;
            break;
        }
        else
        {
            cout << "*";
        }
    }


}


int main()
{
    int n;
    int k;
    cin >> k;

    for (int i=0; i<k; i++)
    {
        cin >> n;
        licz(n);
    }

}



