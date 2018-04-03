#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

long long pw(pair<long long, long long> a, pair<long long, long long> c)
{
   return (0-a.first)*(c.second)-(c.first)*(0-a.second);
}

struct wektor
{
    long long x, y;

    bool operator < (const wektor& str) const
    {
        long long s = pw(make_pair(x, y), make_pair(str.x, str.y));
        return s<0;
    }
};



void doIt()
{
    long long n;
    priority_queue<pair<wektor, pair<long long, long long> >> kolejka;
    cin >> n;
    for (long long i=1; i<=n; i++)
    {
        long long x, y;
        cin >> x >> y;
        wektor w;
        w.x = x;
        w.y = y;
        pair<wektor, pair<long long, long long> > p;
        p.first = w;
        p.second.first = (x*x+y*y)*(-1);
        p.second.second = i;

        kolejka.push(p);
    }
    while (!kolejka.empty())
    {
        pair<wektor, pair<long long, long long> > p = kolejka.top();
        cout << p.second.second << endl;
        kolejka.pop();
    }
}

int main()
{
    long long z;
    cin >> z;
    while (z--)
        doIt();
}
