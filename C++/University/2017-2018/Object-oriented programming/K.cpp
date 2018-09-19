#include <iostream>
#include <vector>

using namespace std;

class tracer
{
  public:
    vector<string> tab;
    mutable int numberOfPrint = 0;
    static int numberOfObjects;
    tracer()
    {
        numberOfObjects++;
    }

    tracer(const string s[], int n)
    {
        tab.resize(n);
        for (int x = 0; x < n; x++)
        {
            tab[x] = s[x];
        }
        numberOfObjects++;
    }

    tracer(const tracer &t)
    {
        numberOfObjects++;
        tab = t.tab;
    }

    void concat(int k, int l)
    {
        tab[k] += tab[l];
    }

    int printno() const
    {
        return numberOfPrint;
    }

    static int objectno()
    {
        return numberOfObjects;
    }

    tracer &operator=(const tracer &t)
    {
        tab = t.tab;
        return *this;
    }

    ~tracer()
    {
        numberOfObjects--;
    }
};

int tracer::numberOfObjects = 0;

ostream &operator<<(ostream &os, const tracer &t)
{
    t.numberOfPrint++;
    for (int x = 0; x < t.tab.size(); x++)
    {
        os << t.tab[x] << '\n';
    }
    return os;
}
