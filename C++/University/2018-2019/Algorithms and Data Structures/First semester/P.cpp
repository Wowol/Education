#include <iostream>
#define MAX 600000

using namespace std;

long long tree[MAX][2];
// int test[MAX];
int n;

bool isLeftChild(int w)
{
    return w % 2 == 0;
}

void printTree()
{
    int level = 0;
    while ((1 << level) <= n)
    {
        cout << "level:" << level << endl;
        for (int x = (1 << level); x < 2 * (1 << level); x++)
        {
            cout << tree[x][0] << "," << tree[x][1];
            cout << " ";
        }
        cout << endl;
        level++;
    }
}

void updateTree(int left, int right, long long value)
{
    int oldLeft = left;
    int oldRight = right;
    while (left / 2 != right / 2)
    {
        if (isLeftChild(left))
        {
            int brother = left + 1;
            tree[brother][0] += value;
            tree[brother][1] = left >= n ? tree[brother][0] : tree[brother][0] + max(tree[brother * 2][1], tree[brother * 2 + 1][1]);
        }
        if (!isLeftChild(right))
        {
            int brother = right - 1;
            tree[brother][0] += value;
            tree[brother][1] = right >= n ? tree[brother][0] : tree[brother][0] + max(tree[brother * 2][1], tree[brother * 2 + 1][1]);
        }

        left /= 2;
        right /= 2;
    }

    while (oldLeft != 0)
    {
        tree[oldLeft][1] = oldLeft >= n ? tree[oldLeft][0] : tree[oldLeft][0] + max(tree[oldLeft * 2][1], tree[oldLeft * 2 + 1][1]);
        if (oldLeft != 1)
        {
            tree[oldRight][1] = oldRight >= n ? tree[oldRight][0] : tree[oldRight][0] + max(tree[oldRight * 2][1], tree[oldRight * 2 + 1][1]);
        }
        oldLeft /= 2;
        oldRight /= 2;
    }
}

long long calculate(int w)
{
    long long r = tree[w][1];
    w /= 2;
    while (w != 0)
    {
        r += tree[w][0];
        w /= 2;
    }
    return r;
}

long long queryMax(int left, int right)
{
    long long result = calculate(left);
    result = max(result, calculate(right));
    while (left / 2 != right / 2)
    {
        if (isLeftChild(left))
        {
            int brother = left + 1;
            result = max(result, calculate(brother));
        }
        if (!isLeftChild(right))
        {
            int brother = right - 1;
            result = max(result, calculate(brother));
        }
        left /= 2;
        right /= 2;
    }
    return result;
}

void doIt()
{
    long long space, numQuery;
    int k;
    cin >> k >> space >> numQuery;
    n = 1;
    while (n < k)
    {
        n *= 2;
    }

    for (int x = 0; x < 2 * n + 5; x++)
    {
        // test[x] = 0;
        tree[x][0] = 0;
        tree[x][1] = 0;
    }

    for (int x = 0; x < numQuery; x++)
    {
        int left;
        int right;
        long long value;
        cin >> left >> right >> value;

        // for (int x = left; x <= right; x++)
        // {
        //     test[x] += value;
        // }

        left += n - 1;
        right += n - 1;
        right--;

        tree[left][0] += value;
        tree[left][1] += value;

        if (left != right)
        {
            tree[right][0] += value;
            tree[right][1] += value;
        }

        updateTree(left, right, value);
        long long m = queryMax(left, right);
        // cout << "MAX:" << m << endl;
        if (m > space)
        {
            tree[left][0] -= value;
            tree[left][1] -= value;
            if (left != right)
            {
                tree[right][0] -= value;
                tree[right][1] -= value;
            }
            updateTree(left, right, -value);
            cout << "N" << endl;
        }
        else
        {
            cout << "T" << endl;
        }

        // for (int x = 1; x <= k; x++)
        // {
        //     cout << test[x] << " ";
        // }
        // cout << endl;

        // printTree();
    }
}

int main()
{
    //   ios_base::sync_with_stdio(0);
    int z;
    cin >> z;
    while (z--)
    {
        doIt();
    }
}