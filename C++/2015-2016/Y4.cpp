#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void DOIT()
{
    vector< pair<int, int> > V;

    V.clear();
    int m, n;
    cin >> m >> n;
    for (int x=0; x<m; x++)
    {
        pair<int, bool> k;
        cin >> k.first;
        k.second = true;
        V.push_back(k);

        cin >> k.first;
        k.second = false;

        V.push_back(k);
    }

    for (int x=0; x<n; x++)
    {
        pair<int, bool> k;
        cin >> k.first;
        k.second = true;
        V.push_back(k);

        cin >> k.first;
        k.second = false;
        V.push_back(k);
    }


    sort(V.begin(), V.begin()+(m+n)*2);

    int wartosc = 0;
    for (int x=0; x<(n+m)*2; x++)
    {
        int wspol = V[x].first;
        bool czyPoczatek = V[x].second;
        if (czyPoczatek)
        {
            wartosc++;
        }
        else
        {
            wartosc--;
        }

        if (wartosc>1)
        {
            cout << "TAK" << endl;
            return;
        }
    }

    cout << "NIE" << endl;

}


int main()
{
    int z;
    cin >> z;
    while (z--)
    {
        DOIT();
    }
}
