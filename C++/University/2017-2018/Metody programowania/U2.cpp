#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#define MAX 40000007

using namespace std;

struct node
{
    int sum;
    int max;
    int number;
};

int firstLeafIndex;
node tab[MAX];
int n;

void clear()
{
    for (int x = 0; x < n * 3 + 4; x++)
    {
        tab[x].sum = 0;
        tab[x].number = 0;
        tab[x].max = 0;
    }
}

bool isLeftChild(int number)
{
    return number % 2 == 1;
}

bool isRightChild(int number)
{
    return !isLeftChild(number);
}

int getBrotherIndex(int number)
{
    if (number == 0)
        return -1;
    if (isLeftChild(number))
        return number + 1;
    else
        return number - 1;
}

int getLeftChildIndex(int number)
{
    return number * 2 + 1;
}

int getRightChildIndex(int number)
{
    return getLeftChildIndex(number) + 1;
}

int getFatherIndex(int number)
{
    return (number - 1) / 2;
}

void update(int index)
{
    tab[getFatherIndex(index)].max = max(tab[index].max, tab[getBrotherIndex(index)].max);
    tab[getFatherIndex(index)].number = tab[index].number + tab[getBrotherIndex(index)].number;
    tab[getFatherIndex(index)].sum = tab[index].sum + tab[getBrotherIndex(index)].sum;
    if (getFatherIndex(index) > 0)
    {
        update(getFatherIndex(index));
    }
}

void insert(int index, int value)
{
    tab[firstLeafIndex + index].sum += value;
    tab[firstLeafIndex + index].max += value;
    tab[firstLeafIndex + index].number += value != 0 ? 1 : 0;
    if (tab[firstLeafIndex + index].number > 1)
        tab[firstLeafIndex + index].number = 1;

    update(firstLeafIndex + index);
}

void delet(int index)
{
    if (tab[firstLeafIndex + index].number == 0)
    {
        cout << "ERROR" << endl;
        return;
    }
    cout << tab[firstLeafIndex + index].sum << endl;
    tab[firstLeafIndex + index].sum = 0;
    tab[firstLeafIndex + index].max = 0;
    tab[firstLeafIndex + index].number = 0;
    update(firstLeafIndex + index);
}

int sum(int left, int right)
{
    left += firstLeafIndex;
    right += firstLeafIndex;
    int result = 0;
    result += tab[left].sum;
    if (left == right)
    {
        return result;
    }
    result += tab[right].sum;
    while (getFatherIndex(left) != getFatherIndex(right))
    {
        if (isLeftChild(left))
        {
            result += tab[getBrotherIndex(left)].sum;
        }
        if (isRightChild(right))
        {
            result += tab[getBrotherIndex(right)].sum;
        }
        left = getFatherIndex(left);
        right = getFatherIndex(right);
    }
    return result;
}

int maks(int left, int right)
{
    left += firstLeafIndex;
    right += firstLeafIndex;
    int result = tab[left].max;
    if (left == right)
    {
        return result;
    }
    result = max(result, tab[right].max);
    while (getFatherIndex(left) != getFatherIndex(right))
    {
        if (isLeftChild(left))
        {
            result = max(result, tab[getBrotherIndex(left)].max);
        }
        if (isRightChild(right))
        {
            result = max(result, tab[getBrotherIndex(right)].max);
        }
        left = getFatherIndex(left);
        right = getFatherIndex(right);
    }
    return result;
}

int number(int left, int right)
{
    left += firstLeafIndex;
    right += firstLeafIndex;
    int result = 0;
    result += tab[left].number;
    if (left == right)
    {
        return result;
    }
    result += tab[right].number;
    while (getFatherIndex(left) != getFatherIndex(right))
    {
        if (isLeftChild(left))
        {
            result += tab[getBrotherIndex(left)].number;
        }
        if (isRightChild(right))
        {
            result += tab[getBrotherIndex(right)].number;
        }
        left = getFatherIndex(left);
        right = getFatherIndex(right);
    }
    return result;
}

void ave(int left, int right)
{
    int s = sum(left, right);
    int num = number(left, right);

    if (num == 0)
    {
        cout << "ERROR" << endl;
        return;
    }

    double av = (double)s / double(num);
    cout << round(av) << endl;
}

void nxt(int index)
{
    index += firstLeafIndex;
    while (true)
    {
        if (index == 0)
        {
            cout << "ERROR" << endl;
            return;
        }
        if (isLeftChild(index) && tab[getBrotherIndex(index)].number > 0)
        {
            break;
        }
        index = getFatherIndex(index);
    }
    index = getBrotherIndex(index);
    while (index < firstLeafIndex)
    {
        if (tab[getLeftChildIndex(index)].number > 0)
            index = getLeftChildIndex(index);
        else
            index = getRightChildIndex(index);
    }
    cout << index - firstLeafIndex << " " << tab[index].sum << endl;
}

void countFirstLeafIndex()
{
    int temp = 1;
    while (temp < n)
    {
        temp <<= 1;
    }
    firstLeafIndex = temp - 1;
}

void doIt()
{
    int m;
    cin >> n >> m;

    clear();
    countFirstLeafIndex();

    while (m--)
    {
        string op;
        cin >> op;
        if (op == "INS")
        {
            int index, value;
            cin >> index >> value;
            insert(index, value);
        }
        else if (op == "SUM")
        {
            int left, right;
            cin >> left >> right;
            cout << sum(left, right) << endl;
        }
        else if (op == "DEL")
        {
            int index;
            cin >> index;
            delet(index);
        }
        else if (op == "MAX")
        {
            int left, right;
            cin >> left >> right;
            cout << maks(left, right) << endl;
        }
        else if (op == "NUMBER")
        {
            int left, right;
            cin >> left >> right;
            cout << number(left, right) << endl;
        }
        else if (op == "AVE")
        {
            int left, right;
            cin >> left >> right;
            ave(left, right);
        }
        else if (op == "NXT")
        {
            int index;
            cin >> index;
            nxt(index);
        }
    }
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