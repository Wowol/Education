#include <iostream>
#define MAX 1000005
#include <algorithm>
#include <vector>

using namespace std;



int doIt()
{
    uint64_t kosztDziury[MAX];
    uint64_t pozDziury[MAX];
    uint64_t kosztLaty = 0;
    uint64_t dlLaty = 0;
    uint64_t n;
    uint64_t d[MAX];
    std::vector<uint64_t>::iterator up, down;
    uint64_t kosztDziuryPoLacie = 0;
    uint64_t dokad = 0;
    cin >> n;
    d[n]=0;
    for (int x=0; x<n; x++)
    {
        cin >> pozDziury[x] >> kosztDziury[x];
    }

    std::vector<uint64_t> v(pozDziury,pozDziury+n);

    cin >> dlLaty >> kosztLaty;

    for(int i=n-1; i>=0; --i)
    {
        dokad = upper_bound(&pozDziury[i], pozDziury+n, pozDziury[i]+dlLaty)-pozDziury;
       // dokad = up-v.begin();
        kosztDziuryPoLacie = d[dokad];
        d[i]=min(d[i+1]+kosztDziury[i], kosztLaty + kosztDziuryPoLacie);
    }
    cout << d[0] << endl;

}


int main()
{
    int k;
    cin >> k;
    while (k--)
    {
        doIt();
    }
}
