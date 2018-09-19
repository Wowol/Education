#include <iostream>
#include <algorithm>

using namespace std;
const int MAX = int((1e5)+2);

int doIt()
{
    int n;
    int ork[MAX];
    int elf[MAX];
    cin >> n;
    int punkt = 0;
    int k = n;
    int orkPoczatkowy = 1;
    int elfPoczatkowy = 1;
    int orkKoncowy = n;
    int elfKoncowy = n;
    for (int x=1; x<=n; x++)
    {
        cin >> ork[x];
    }

    for (int x=1; x<=n; x++)
    {
        cin >> elf[x];
    }

    sort(ork+1, ork+n+1, greater < int >() );
    sort(elf+1, elf+n+1, greater < int >() );

    while (k--)
    {
        if (ork[orkKoncowy]>elf[elfKoncowy])
        {
            punkt++;
            elfKoncowy--;
            orkKoncowy--;
        }
        else
        {
            if (ork[orkPoczatkowy]>elf[elfPoczatkowy])
            {
                punkt++;
                elfPoczatkowy++;
                orkPoczatkowy++;
            }
            else
            {
                // Najslabszy gra z najelpszym
                if (ork[orkKoncowy]<elf[elfPoczatkowy])
                {
                    punkt--;
                }
                elfPoczatkowy++;
                orkKoncowy--;
            }
        }
    }

    cout << punkt*200 << endl;






}
int main()
{
    int q;
    cin >> q;
    while (q--)
    {
        doIt();
    }
}
