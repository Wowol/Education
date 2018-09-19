#include <iostream>
#include <map>


using namespace std;
const int MAX = 1e5;
int P[MAX];
int I[MAX];
map<int, int> M;
int ktoryElement = 0;

int rekurencja(int minimum, int maximum)
{

    int liczba = P[ktoryElement];
    int index = M[liczba];
    if (minimum==maximum)
    {
        cout << liczba << " ";
        return 0;
    }

    if (index!=minimum)
    {
        ktoryElement++;
        rekurencja(minimum, index-1);
    }
    else
    {
        //++ktoryElement;
    }
    if (index!=maximum)
    {
        ktoryElement++;
        rekurencja(index+1, maximum);
    }


    cout << liczba << " ";

}


void doIt()
{
    int n;
    cin >> n;
    for (int x=0; x<n; x++)
    {
        cin >> P[x];
    }

    for (int x=0; x<n; x++)
    {
        int l;
        cin >> l;
        I[x] = l;
        M[l] = x;
    }
    rekurencja(0, n-1);
    ktoryElement = 0;
    cout << endl;
   /* for (int x=0; x<n; x++)
    {
        int liczba = P[x];
        int index = M[liczba];
        maximum = index;

    }*/

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
