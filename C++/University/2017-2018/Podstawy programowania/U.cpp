#include <iostream>
#include <cstring>

class point
{
  private:
    int x;
    int y;

  public:
    point(int x = 0, int y = 0)
    {
        this->x = x;
        this->y = y;
    }
    int getY()
    {
        return (y);
    }

    int getX()
    {
        return (x);
    }

    void print()
    {
        std::cout << x << " " << y << std::endl;
    }
};

class queue
{
  private:
    int currentSize;
    int size;
    int index = -1;
    int beginIndex = 0;
    point *tab;

  public:
    queue(int size = 15)
    {
        this->size = size;
        currentSize = 0;
        index = -1;
        beginIndex = 0;
        tab = new point[size];
    }

    void enqueue(point &x)
    {
        if (!full())
        {
            currentSize++;
            index++;
            index %= size;
            tab[index] = x;
        }
    }

    bool full()
    {
        return currentSize == size;
    }

    bool empty()
    {
        return currentSize == 0;
    }

    point dequeue()
    {
        if (!empty())
        {
            currentSize--;
            point f = tab[beginIndex];
            beginIndex++;
            beginIndex %= size;
            return f;
        }
        else
        {
            return point(0, 0);
        }
    }

    point front()
    {
        if (!empty())
        {
            return tab[beginIndex];
        }
        else
        {
            return point(0, 0);
        }
    }

    void clear()
    {
        index = -1;
        beginIndex = 0;
        currentSize = 0;
    }

    void resize(int n)
    {
        if (n < size)
        {
            return;
        }

        point *newTab = new point[n];

        for (int x = 0; x < currentSize; x++)
        {
            newTab[x] = tab[beginIndex];
            beginIndex++;
            beginIndex %= size;
        }

        index = currentSize - 1;
        

        beginIndex = 0;
        size = n;
        delete[] tab;
        tab = newTab;
    }

    ~queue()
    {
        delete[] tab;
    }
};

#include <cstring>

class stack
{
  private:
    int size;
    long long *tab;
    int index;

  public:
    stack(int size = 15)
    {
        this->size = size;
        tab = new long long[size];
        index = -1;
    }

    void push(long long &x)
    {
        if (full())
        {
            return;
        }
        tab[++index] = x;
    }

    long long top()
    {
        if (empty())
        {
            return 0;
        }
        return tab[index];
    }

    long long pop()
    {
        if (empty())
        {
            return 0;
        }
        return tab[index--];
    }

    bool empty()
    {
        return (index == -1);
    }

    bool full()
    {
        return (index == size - 1);
    }

    void clear()
    {
        index = -1;
    }

    void resize(int n)
    {
        if (n < size)
        {
            return;
        }

        long long *newTab = new long long[n];
        std::memcpy(newTab, tab, size * sizeof(long long));

        size = n;
        delete[] tab;
        tab = newTab;
    }

    ~stack()
    {
        delete[] tab;
    }
};
