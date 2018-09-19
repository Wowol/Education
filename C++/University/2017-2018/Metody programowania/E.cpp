#include <iostream>
#define MAX 100005
#include <map>

using namespace std;

int n;

int preOrder[MAX];
int inOrder[MAX];
int postOrder[MAX];
map<int, int> where;
int currentIndex;

void preIn(int inFirst, int inLast)
{
    if (inFirst > inLast)
    {
        return;
    }
    cout << '(';
    if (inFirst == inLast)
    {
        cout << ')';
        return;
    }
    int node = preOrder[currentIndex];
    int w = where[node];

    if (inFirst <= w - 1)
    {
        currentIndex++;
        preIn(inFirst, w - 1);
    }
    if (inFirst <= w - 1 && w + 1 <= inLast)
    {
        cout << ',';
    }
    if (w + 1 <= inLast)
    {
        currentIndex++;
        preIn(w + 1, inLast);
    }
    cout << ')';
}


void postIn(int inFirst, int inLast, int numberOfRight)
{
    cout << '(';
    int node = postOrder[inLast];
    int w = where[node] - numberOfRight;
    if (inFirst == inLast)
    {
        cout << ')';
        return;
    }

    if (inFirst <= w - 1)
    {
        postIn(inFirst, w - 1, numberOfRight);
    }

    if (inFirst <= w - 1 && w <= inLast - 1)
    {
        cout << ',';
    }

    if (w <= inLast - 1)
    {
        postIn(w, inLast - 1, numberOfRight + 1);
    }
    cout << ')';
}

void prePost(int postFirst, int postLast)
{
    cout << '(';
    if (postFirst == postLast)
    {
        cout << ')';
        return;
    }

    int node = preOrder[currentIndex];
    int w = where[node];
    bool imLisc = false;

    if (postFirst <= w - 1)
    {
        currentIndex++;
        prePost(postFirst, w - 1);
    }

    cout << ')';

    if (w + 1 <= postLast)
    {
        cout << ',';
        currentIndex++;
        prePost(w + 1, postLast);
    }
}

void doIt()
{
    cin >> n;
    string order1, order2;
    cin >> order1;
    for (int x = 0; x < n; x++)
    {
        if (order1 == "PREORDER")
        {
            cin >> preOrder[x];
        }
        else if (order1 == "INORDER")
        {
            cin >> inOrder[x];
        }
        else
        {
            cin >> postOrder[x];
        }
    }

    cin >> order2;
    for (int x = 0; x < n; x++)
    {
        int temp;
        cin >> temp;
        if (order2 == "PREORDER")
        {
            preOrder[x] = temp;
        }
        else if (order2 == "INORDER")
        {
            inOrder[x] = temp;
        }
        else
        {
            postOrder[x] = temp;
        }
    }

    if ((order1 == "PREORDER" && order2 == "INORDER") || (order1 == "INORDER" && order2 == "PREORDER"))
    {
        for (int x = 0; x < n; x++)
        {
            where[inOrder[x]] = x;
        }
        currentIndex = 0;
        preIn(0, n - 1);
    }
    if ((order1 == "POSTORDER" && order2 == "INORDER") || (order2 == "POSTORDER" && order1 == "INORDER"))
    {
        for (int x = 0; x < n; x++)
        {
            where[inOrder[x]] = x;
        }
        currentIndex = n - 1;
        postIn(0, n - 1, 0);
    }
    if ((order1 == "PREORDER" && order2 == "POSTORDER") || (order2 == "PREORDER" && order1 == "POSTORDER"))
    {
        for (int x = 0; x < n; x++)
        {
            where[postOrder[x]] = x;
        }
        currentIndex = 0;
        prePost(0, n - 1);
    }
    where.clear();
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