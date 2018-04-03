#include <iostream>
#include <string>
using namespace std;

using namespace std;

class vector
{
  private:
    string *tab;
    int capacity;
    int size;

  public:
    vector(int a = 4, int b = 0, string c = "")
    {
        capacity = a;
        tab = new string[a];
        for (int x = 0; x < b; x++)
        {
            tab[x] = c;
        }
        size = b;
    }

    vector(const vector &a)
    {
        size = a.size;
        capacity = a.size;
        tab = new string[capacity];
        for (int x = 0; x < size; x++)
        {
            tab[x] = a.tab[x];
        }
    }

    void insertionSort()
    {
        for (int i = 1; i < size; i++)
        {
            string x = tab[i];
            int j = i - 1;
            while (j >= 0 && tab[j] > x)
            {
                tab[j + 1] = tab[j];
                j--;
            }
            tab[j + 1] = x;
        }
    }

    void sort(int i)
    {
        if (size == 1)
        {
            return;
        }

        if (size <= 40)
        {
            insertionSort();
            return;
        }

        vector buckets[27];
        vector empty;
        for (int x = 0; x < size; x++)
        {
            string p = tab[x];
            char c = p[i];
            if (c == 0)
            {
                empty.add(p);
            }
            else
            {
                buckets[c - 'A'].add(p);
            }
        }

        clear();
        for (int x = 0; x < empty.getSize(); x++)
        {
            add(empty[x]);
        }

        for (int x = 0; x < 27; x++)
        {
            if (buckets[x].getSize() != 0)
            {
                buckets[x].sort(i + 1);
                for (int y = 0; y < buckets[x].getSize(); y++)
                {
                    add(buckets[x][y]);
                }
            }
        }
    }

    void enlarge(int result)
    {
        capacity = result;
        string *newTab = new string[capacity];
        for (int x = 0; x < size; x++)
        {
            newTab[x] = tab[x];
            tab[x].clear();
        }
        for (int x = size; x < capacity; x++)
        {
            newTab[x] = "";
        }
        delete[] tab;
        tab = newTab;
    }

    void add(string a)
    {
        if (size == capacity)
        {
            enlarge(capacity + capacity / 4);
        }
        tab[size++] = a;
    }

    void erase(int i)
    {
        if (i >= size || i < 0)
        {
            return;
        }

        for (int x = i + 1; x < size; x++)
        {
            tab[x - 1] = tab[x];
            tab[x].clear();
        }
        size--;
    }

    void insert(int i, string a)
    {
        if (i > size || i < 0)
        {
            return;
        }
        if (size == capacity)
        {
            enlarge(capacity + capacity / 4);
        }
        for (int x = size - 1; x >= i; x--)
        {
            tab[x + 1] = tab[x];
            tab[x].clear();
        }
        tab[i] = a;
        size++;
    }

    int getSize()
    {
        return size;
    }

    void clear()
    {
        size = 0;
    }

    void resize(int s)
    {
        int p = capacity;
        bool zmiana = false;
        if (s > p)
        {
            zmiana = true;
        }
        while (s > p)
        {
            int temp = p / 4;
            p += temp;
        }
        if (zmiana)
            ;
        {
            enlarge(p);
        }
        size = s;
    }

    ~vector()
    {
        delete[] tab;
    }

    string &operator[](int i) const
    {
        return i >= size ? tab[size - 1] : tab[i];
    }

    vector &operator=(const vector &a)
    {
        if (&a == this)
        {
            return *this;
        }
        size = a.size;
        capacity = a.size;
        delete[] tab;
        tab = new string[capacity];
        for (int x = 0; x < size; x++)
        {
            tab[x] = a.tab[x];
        }
        return *this;
    }

    friend ostream &operator<<(ostream &stream, vector &a);
    friend istream &operator>>(istream &stream, vector &a);
};

ostream &operator<<(ostream &stream, vector &a)
{
    for (int x = 0; x < a.size; x++)
    {
        stream << a.tab[x] << " ";
    }
    return stream;
}

istream &operator>>(istream &stream, vector &a)
{
    for (int x = 0; x < a.size; x++)
    {
        stream >> a.tab[x];
    }
    return stream;
}

void doIt()
{
    vector a;
    int n;
    cin >> n;
    while (n--)
    {
        string q;
        cin >> q;
        a.add(q);
    }
    a.sort(0);
    cout << a << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    int z;
    cin >> z;
    while (z--)
    {
        doIt();
    }
}