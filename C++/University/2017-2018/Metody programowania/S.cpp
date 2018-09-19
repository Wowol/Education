#include <iostream>
#define MAX 2005
typedef unsigned long long ull;

using namespace std;

int currentIndex = -1;
int tab[MAX];
int result[MAX];
int n;

struct element
{
    int index;
    int multipler;

    bool operator>(const element &e)
    {
        if ((ull)tab[index] * (ull)e.multipler > (ull)tab[e.index] * (ull)multipler)
        {
            return true;
        }
        if ((ull)tab[index] * (ull)e.multipler < (ull)tab[e.index] * (ull)multipler)
        {
            return false;
        }

        if (tab[index] > tab[e.index])
        {
            return true;
        }

        if (tab[index] < tab[e.index])
        {
            return false;
        }

        return index < e.index;
    }
};

element heap[MAX + 3];

int getLeftChildIndex(int number)
{
    return number * 2 + 1;
}

int getRightChildIndex(int number)
{
    return number * 2 + 2;
}

bool hasLeftChild(int number)
{
    return getLeftChildIndex(number) <= currentIndex;
}

bool hasRightChild(int number)
{
    return getRightChildIndex(number) <= currentIndex;
}

int getFatherIndex(int number)
{
    return (number - 1) / 2;
}

element getFather(int number)
{
    return heap[getFatherIndex(number)];
}

element getLeftChild(int number)
{
    return heap[getLeftChildIndex(number)];
}

element getRightChild(int number)
{
    return heap[getRightChildIndex(number)];
}

void insert(element e)
{
    heap[++currentIndex] = e;
    int temp = currentIndex;

    while (temp != 0)
    {
        element father = getFather(temp);
        if (e > father)
        {
            int fatherIndex = getFatherIndex(temp);
            swap(heap[fatherIndex], heap[temp]);
            temp = fatherIndex;
        }
        else
        {
            break;
        }
    }
}

element pop()
{
    element head = heap[0];
    heap[0] = heap[currentIndex--];

    int temp = 0;
    while (hasLeftChild(temp))
    {
        element current = heap[temp];
        element left = getLeftChild(temp);
        if (hasRightChild(temp))
        {
            element right = getRightChild(temp);
            if (left > right && left > current)
            {
                int index = getLeftChildIndex(temp);
                swap(heap[index], heap[temp]);
                temp = index;
                continue;
            }
            if (right > left && right > current)
            {
                int index = getRightChildIndex(temp);
                swap(heap[index], heap[temp]);
                temp = index;
                continue;
            }
            break;
        }
        else
        {
            if (left > current)
            {
                int index = getLeftChildIndex(temp);
                swap(heap[index], heap[temp]);
                temp = index;
                continue;
            }
            break;
        }
    }
    return head;
}

void clear()
{
    currentIndex = -1;
    for (int x = 0; x < n + 1; x++)
    {
        result[x] = 0;
    }
}

void doIt()
{
    int k;
    cin >> n >> k;
    clear();
    for (int x = 0; x < n; x++)
    {
        cin >> tab[x];
        element e;
        e.index = x;
        e.multipler = 1;
        insert(e);
    }
    while (k--)
    {
        element head = pop();
        result[head.index]++;
        head.multipler++;
        insert(head);
    }
    for (int x = 0; x < n; x++)
    {
        cout << result[x] << " ";
    }
    cout << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    int z;
    cin >> z;
    while (z--)
    {
        doIt();
    }
}