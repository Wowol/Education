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


int main()
{
    int n=0;
    cin >> n;

    for (int i=n; i>1; i--)
    {
        if (pierwsza(i))
        {
            cout << "BUZZ green bottles standing on the wall." << endl;
            cout << "BUZZ green bottles standing on the wall." << endl;
            cout << "and if one green bottle should accidentally fall," << endl;
            if (pierwsza(i-1))
            {
                cout << "there'd be BUZZ green bottles standing on the wall." << endl;
            }
            else
            {
                if (i-1 == 1)
                {
                    cout << "there'd be 1 green bottle standing on the wall." << endl;
                }
                else
                {
                    cout << "there'd be " << i-1 << " green bottles standing on the wall." << endl;
                }
            }
            cout << endl;
        }
        else
        {
            cout << i <<" green bottles standing on the wall." << endl;
            cout << i <<" green bottles standing on the wall." << endl;
            cout << "and if one green bottle should accidentally fall," << endl;
            if (pierwsza(i-1))
            {
                cout << "there'd be BUZZ green bottles standing on the wall." << endl;
            }
            else
            {
                cout << "there'd be " << i-1 << " green bottles standing on the wall." << endl;
            }
            cout << endl;
        }
    }

    cout << "1 green bottle standing on the wall." << endl;
    cout << "1 green bottle standing on the wall." << endl;
    cout << "and if one green bottle should accidentally fall," << endl;
    cout << "there'd be no green bottles standing on the wall." << endl;



}


