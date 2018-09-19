#include <iostream>
#include <cstring>

using namespace std;

int doIt()
{
    string p;
    cin >> p;
    int tabPrefix[1000055];
    tabPrefix[0] = 0;
    int z = 0;
    int dl = p.length();
    int v=0;
    for (int x=1; x<dl; x++)
    {
        while (v>0)
        {
            if (p[x]==p[v]) break;
            v = tabPrefix[v-1];
        }

        if (p[x]==p[v])
        {
            v++;
        }
        tabPrefix[x] = v;
       // z = max(v, z);
    }

    if (dl-tabPrefix[dl-1]==0)
    {
        cout << 1 << endl;
        return 0;
    }
    int wynik = dl/(dl-tabPrefix[dl-1]);
    if ((dl-tabPrefix[dl-1])*wynik==dl)
    {
        cout << wynik << endl;
    }
    else
    {
        cout << 1 << endl;
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
