#include <iostream>
#include <vector>
typedef unsigned long long ull;

using namespace std;

struct node
{
    string key;
    string value;
};

vector<node> *tab;
ull n = 0;
ull currentIndexPrime = 0;
ull primeNumbers[] = {599, 1277, 2713, 5519, 11243, 23081, 48731, 100151, 202481, 500009, 1000151, 2001199, 4001213, 8004443};

ull nicePrime = 2000000789;

ull currentSize = 0;
ull numberOfStars = 0;

ull hashFunction(string key, ull prime, ull mod)
{
    ull result = 0;
    for (ull x = 0; x < key.size(); x++)
    {
        result *= prime;
        result += key[x];
    }
    return result % mod;
}

void reHashTab(bool changeSize)
{
    ull newSize = changeSize ? primeNumbers[++currentIndexPrime] : n;
    vector<node> *newTab = new vector<node>[newSize];
    for (ull x = 0; x < n; x++)
    {
        for (ull y = 0; y < tab[x].size(); y++)
        {
            string key = tab[x][y].key;
            string value = tab[x][y].value;
            ull hash = hashFunction(key, nicePrime, newSize);
            node q;
            q.key = key;
            q.value = value;
            newTab[hash].push_back(q);
        }
        tab[x].clear();
        tab[x].shrink_to_fit();
    }
    delete[] tab;
    tab = newTab;
    n = newSize;
}

void checkSize()
{
    if (currentSize >= 2 * n)
    {
        reHashTab(true);
        return;
    }
}

void insert(string key, string value)
{
    ull hash = hashFunction(key, nicePrime, n);
    for (int x = 0; x < tab[hash].size(); x++)
    {
        if (tab[hash][x].key == key)
        {
            tab[hash][x].value = value;
            return;
        }
    }
    node q;
    q.key = key;
    q.value = value;
    tab[hash].push_back(q);

    currentSize++;
    checkSize();
}

void find(string key)
{
    ull hash = hashFunction(key, nicePrime, n);
    for (int x = 0; x < tab[hash].size(); x++)
    {
        if (tab[hash][x].key == key)
        {
            cout << tab[hash][x].value << endl;
            return;
        }
    }
    cout << "ERROR" << endl;
}

void delet(string key)
{
    ull hash = hashFunction(key, nicePrime, n);
    for (int x = 0; x < tab[hash].size(); x++)
    {
        if (tab[hash][x].key == key)
        {
            cout << tab[hash][x].value << endl;
            tab[hash].erase(tab[hash].begin() + x);
            currentSize--;
            return;
        }
    }
    cout << "ERROR" << endl;
}

void doIt()
{
    currentIndexPrime = 0;
    currentSize = 0;
    numberOfStars = 0;

    ull q;
    cin >> q;
    n = primeNumbers[0];
    tab = new vector<node>[n];
    string op;
    string key;
    string value;
    while (q--)
    {
        cin >> op >> key;
        if (op == "INSERT")
        {
            cin >> value;
            insert(key, value);
        }
        if (op == "FIND")
        {
            find(key);
        }
        if (op == "DELETE")
        {
            delet(key);
        }
    }
    delete[] tab;
}

int main()
{
    ios_base::sync_with_stdio(0);
    ull z;
    cin >> z;
    while (z--)
    {
        doIt();
    }
}