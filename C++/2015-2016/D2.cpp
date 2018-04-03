#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

const int MAX = 1e7+1;
vector<int> pierwsze;

int p[MAX];

void znajdzPierwsze()
{
    p[0] = 69;
    p[1] = 69;
    for (int x=2; x<MAX; x++)
    {
        p[x] = x;
    }

    for (int x=2; x*x<MAX; x++)
    {
        if (p[x]==x)
        {
            pierwsze.push_back(x);
            for (int y=2; y*x<MAX; y++)
            {
                p[y*x] = x;
            }

        }
    }



}

void JUST_DO_IT()
{
    int n;
    cin >> n;

    int q = n;

     cout << q << " = ";
     priority_queue< pair<int, int> > k;
     int poprzednie = p[n];
     int ilosc = 0;
    while (n!=0)
    {
        ilosc++;
        if (p[n]!=poprzednie)
        {
            k.push(make_pair(poprzednie*-1, --ilosc));
            ilosc = 1;
            poprzednie = p[n];
        }

       // cout << p[n] << " ";
        n/=p[n];
    }

    while (!k.empty())
    {
        pair<int, int> s = k.top();
        k.pop();
        int podstawa = s.first;
        int wykladnik = s.second;
        if (wykladnik!=1)
        {
            cout << podstawa*-1 << "^" << wykladnik;
        }
        else
        {
            cout << podstawa*-1;
        }
        if (!k.empty())
        {
            cout << "*";
        }

    }

    cout << endl;


}

int main()
{
    znajdzPierwsze();
    int z;
    cin >> z;
    while (z--)
    {
        JUST_DO_IT();
    }

}
