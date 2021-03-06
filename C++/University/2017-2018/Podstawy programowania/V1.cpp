#include <iostream>
using namespace std;

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
    int index = -1;
    int beginIndex = 0;
    int size;
    point *tab;

  public:
    int currentSize;

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

#define MAX 2018

int map[MAX][MAX];
queue q(MAX *MAX);
int visited[MAX][MAX];
int n, m;

void bfs()
{
    while (!q.empty())
    {
        point current = q.dequeue();
        int currentY = current.getX();
        int currentX = current.getY();

        if (map[currentY][currentX] > 3)
        {
            cout << map[currentY][currentX] << " " << visited[currentY][currentX] + 1 << endl;
            return;
        }

        if (currentY != 0 && visited[currentY - 1][currentX] == -1 && map[currentY - 1][currentX] != 3)
        {
            visited[currentY - 1][currentX] = visited[currentY][currentX] + 1;
            point p(currentY - 1, currentX);
            q.enqueue(p);
        }

        if (currentY != n - 1 && visited[currentY + 1][currentX] == -1 && map[currentY + 1][currentX] != 3)
        {
            visited[currentY + 1][currentX] = visited[currentY][currentX] + 1;
            point p(currentY + 1, currentX);
            q.enqueue(p);
        }

        if (currentX != 0 && visited[currentY][currentX - 1] == -1 && map[currentY][currentX - 1] != 3)
        {
            visited[currentY][currentX - 1] = visited[currentY][currentX] + 1;
            point p(currentY, currentX - 1);
            q.enqueue(p);
        }

        if (currentX != m - 1 && visited[currentY][currentX + 1] == -1 && map[currentY][currentX + 1] != 3)
        {
            visited[currentY][currentX + 1] = visited[currentY][currentX] + 1;
            point p(currentY, currentX + 1);
            q.enqueue(p);
        }
    }

    cout << -1 << " " << -1 << endl;
}

void clear(int n, int m)
{
    for (int y = 0; y < n + 5; y++)
    {
        for (int x = 0; x < m + 5; x++)
        {
            visited[y][x] = -1;
        }
    }
    q.clear();
}

void doIt()
{
    cin >> n >> m;
    clear(n, m);
    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < m; x++)
        {
            int number;
            cin >> number;
            map[y][x] = number;
            if (number == 3)
            {
                point p(y, x);
                q.enqueue(p);
            }
            if (number == 2 || number == 1)
            {
                visited[y][x] = -2;
            }
        }
    }
    bfs();
}

int main()
{
    int z;
    cin >> z;
    while (z--)
    {
        doIt();
    }
}