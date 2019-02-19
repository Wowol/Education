#include <iostream>
#define MAX 600005
#define NUM_CABLES 8

using namespace std;

int tree[MAX][NUM_CABLES + 1];
int k;
int n;

int getIndexOfParent(int w)
{
    return w / 2;
}

int *getParent(int w)
{
    return tree[w / 2];
}

void makeTree(int w)
{
    if (w * 2 < n)
    {
        makeTree(w * 2);
        makeTree(w * 2 + 1);
    }
    for (int y = 1; y <= NUM_CABLES; y++)
    {
        int first = tree[w * 2 + 1][y];
        int second = tree[w * 2][first];
        tree[w][y] = second;
    }
}

void printTree()
{
    int level = 0;
    while ((1 << level) <= n)
    {
        cout << "level:" << level << endl;
        for (int x = (1 << level); x < 2 * (1 << level); x++)
        {
            for (int y = 1; y <= NUM_CABLES; y++)
            {
                cout << tree[x][y];
            }
            cout << endl;
        }
        level++;
    }
}

void updateTree(int w)
{
    if (w != 0)
    {
        for (int y = 1; y <= NUM_CABLES; y++)
        {
            int first = tree[w * 2 + 1][y];
            int second = tree[w * 2][first];
            tree[w][y] = second;
        }
        updateTree(w / 2);
    }
}

void printRoot()
{
    for (int y = 1; y <= NUM_CABLES; y++)
    {
        cout << tree[1][y] << " ";
    }
    cout << endl;
}

void doIt()
{
    cin >> k;
    n = 1;
    while (n < k)
    {
        n *= 2;
    }

    for (int x = 0; x < n; x++)
    {
        for (int y = 1; y <= NUM_CABLES; y++)
        {
            if (x < k)
            {
                cin >> tree[x + n][y];
            }
            else
            {
                tree[x + n][y] = y;
            }
        }
    }
    makeTree(1);

    int numberOfChanges;
    cin >> numberOfChanges;
    for (int x = 0; x < numberOfChanges; x++)
    {
        int index;
        cin >> index;
        index--;
        for (int y = 1; y <= NUM_CABLES; y++)
        {
            cin >> tree[n + index][y];
        }
        updateTree((n + index) / 2);
        printRoot();
    }
}

int main()
{
    doIt();
}