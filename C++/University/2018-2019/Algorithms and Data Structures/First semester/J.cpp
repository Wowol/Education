#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Number
{
    int value;
    bool begin;
    int indexOfSector;
};

const int MAX = 1e6;
int sectors[MAX];
int state[MAX];
int n;

bool operator<(const Number &x, const Number &y)
{
    if (x.value == y.value && x.begin == y.begin)
        return false;
    if (x.value == y.value)
    {
        if (x.begin)
        {
            return true;
        }
    }
    return x.value < y.value;
}

void doIt()
{
    cin >> n;
    int left;
    int currentState = 0;
    int right;
    int number;
    for (int x = 0; x < n * 2; x++)
    {
        state[x] = 0;
        sectors[x] = 0;
    }
    vector<Number> V;
    for (int x = 0; x < n; x++)
    {
        cin >> left >> right >> number;
        sectors[x] = number;
        Number l;
        l.value = left;
        l.indexOfSector = x;
        l.begin = true;

        Number p;
        p.value = right;
        p.indexOfSector = x;
        p.begin = false;

        V.push_back(l);
        V.push_back(p);
    }

    sort(V.begin(), V.end());
    for (int x = 0; x < n * 2; x++)
    {
        Number a = V[x];
        if (a.begin)
        {
            state[a.indexOfSector] = currentState;
        }
        else
        {
            int num = sectors[a.indexOfSector];
            int z = state[a.indexOfSector];
            int ileProstychZostaloZrobionychNaTymPrzedziale = currentState - z;
            int y = num - ileProstychZostaloZrobionychNaTymPrzedziale;
            if (y > 0)
            {
                currentState += y;
            }
        }
    }
    cout << currentState << endl;
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
