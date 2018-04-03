#include <iostream>

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
        if (zmiana);
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

    vector& operator=(const vector &a)
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