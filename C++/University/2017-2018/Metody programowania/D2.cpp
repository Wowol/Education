#include <iostream>
#include <vector>
#define MAX 2000006
#define left first
#define right second

using namespace std;

int n;
int p = -1;

pair<int, int> tab[MAX];

struct Res
{
    int number;
    int distance;
};

struct Node
{
    pair<int, int> distance;
    pair<int, int> number;
};

Node treeSizes[MAX];
Res res[MAX];
int numberOfHouses[MAX];
int houses = 0;
int qq = 0;

void getResult(int w, int distanceFromUp, int numberFromUp)
{

    if (w == -1)
    {
        return;
    }
    if (distanceFromUp > max(treeSizes[w].distance.left, treeSizes[w].distance.right))
    {
        res[w].distance = distanceFromUp;
        res[w].number = numberFromUp;
    }
    if (distanceFromUp < max(treeSizes[w].distance.left, treeSizes[w].distance.right))
    {
        if (treeSizes[w].distance.left > treeSizes[w].distance.right)
        {
            res[w].number = treeSizes[w].number.left;
            res[w].distance = treeSizes[w].distance.left;
        }
        else if (treeSizes[w].distance.left < treeSizes[w].distance.right)
        {
            res[w].number = treeSizes[w].number.right;
            res[w].distance = treeSizes[w].distance.right;
        }
        else if (treeSizes[w].distance.left == treeSizes[w].distance.right)
        {
            res[w].number = min(treeSizes[w].number.left, treeSizes[w].number.right);
            res[w].distance = treeSizes[w].distance.right;
        }
    }
    if (distanceFromUp == max(treeSizes[w].distance.left, treeSizes[w].distance.right))
    {
        int tempBestNumber = -1;
        if (treeSizes[w].distance.left > treeSizes[w].distance.right)
        {
            tempBestNumber = treeSizes[w].number.left;
        }
        else if (treeSizes[w].distance.left < treeSizes[w].distance.right)
        {
            tempBestNumber = treeSizes[w].number.right;
        }
        else if (treeSizes[w].distance.left == treeSizes[w].distance.right)
        {
            tempBestNumber = min(treeSizes[w].number.left, treeSizes[w].number.right);
        }
        res[w].number = min(tempBestNumber, numberFromUp);
        res[w].distance = distanceFromUp;
    }

    if (distanceFromUp > treeSizes[w].distance.right)
    {
        getResult(tab[w].left, distanceFromUp + 1, numberFromUp);
    }
    else if (distanceFromUp < treeSizes[w].distance.right)
    {
        getResult(tab[w].left, treeSizes[w].distance.right + 1, treeSizes[w].number.right);
    }
    else if (distanceFromUp == treeSizes[w].distance.right)
    {
        if (treeSizes[w].distance.right == 0)
        {
            getResult(tab[w].left, 0, INT32_MAX);
        }
        else
            getResult(tab[w].left, treeSizes[w].distance.right + 1, min(treeSizes[w].number.right, numberFromUp));
    }

    if (distanceFromUp > treeSizes[w].distance.left)
    {
        getResult(tab[w].right, distanceFromUp + 1, numberFromUp);
    }
    else if (distanceFromUp < treeSizes[w].distance.left)
    {
        getResult(tab[w].right, treeSizes[w].distance.left + 1, treeSizes[w].number.left);
    }
    else if (distanceFromUp == treeSizes[w].distance.left)
    {
        if (treeSizes[w].distance.left == 0)
        {
            getResult(tab[w].right, 0, INT32_MAX);
        }
        else
            getResult(tab[w].right, treeSizes[w].distance.left + 1, min(treeSizes[w].number.left, numberFromUp));
    }
}

int calculateHouses(int w)
{
    if (w == -1)
    {
        return 0;
    }
    if (tab[w].left == -1 && tab[w].right == -1)
    {
        numberOfHouses[w] = 1;
        return 1;
    }
    numberOfHouses[w] = calculateHouses(tab[w].left) + calculateHouses(tab[w].right);
    return numberOfHouses[w];
}

void calculateTreeSize(int w)
{
    if (w == -1)
    {
        return;
    }
    if (tab[w].left == -1 && tab[w].right == -1)
    {
        Node result;
        result.distance = make_pair(0, 0);
        result.number = make_pair(w, w);
        treeSizes[w] = result;
        return;
    }
    calculateTreeSize(tab[w].left);
    calculateTreeSize(tab[w].right);

    Node leftNode;
    if (tab[w].left == -1)
    {
        leftNode.distance = make_pair(-1, -1);
        leftNode.number = make_pair(INT32_MAX, INT32_MAX);
    }
    else
    {
        leftNode = treeSizes[tab[w].left];
    }

    Node rightNode;
    if (tab[w].right == -1)
    {
        rightNode.distance = make_pair(-1, -1);
        rightNode.number = make_pair(INT32_MAX, INT32_MAX);
    }
    else
    {
        rightNode = treeSizes[tab[w].right];
    }
    Node result;

    if (leftNode.distance.left > leftNode.distance.right)
    {
        result.distance.left = leftNode.distance.left + 1;
        result.number.left = leftNode.number.left;
    }

    if (leftNode.distance.left < leftNode.distance.right)
    {
        result.distance.left = leftNode.distance.right + 1;
        result.number.left = leftNode.number.right;
    }

    if (leftNode.distance.left == leftNode.distance.right)
    {
        result.distance.left = leftNode.distance.right + 1;
        result.number.left = min(leftNode.number.left, leftNode.number.right);
    }

    if (rightNode.distance.left > rightNode.distance.right)
    {
        result.distance.right = rightNode.distance.left + 1;
        result.number.right = rightNode.number.left;
    }

    if (rightNode.distance.left < rightNode.distance.right)
    {
        result.distance.right = rightNode.distance.right + 1;
        result.number.right = rightNode.number.right;
    }

    if (rightNode.distance.left == rightNode.distance.right)
    {
        result.distance.right = rightNode.distance.right + 1;
        result.number.right = min(rightNode.number.left, rightNode.number.right);
    }

    treeSizes[w] = result;
}

void compile(int w)
{
    cout << w << " ";
    if (p == -1)
    {
        if (tab[w].left == -1 && tab[w].right == -1)
        {
            return;
        }
        int l = tab[w].left != -1 ? numberOfHouses[tab[w].left] : 0;
        int r = tab[w].right != -1 ? numberOfHouses[tab[w].right] : 0;
        if (max(l, r) <= houses / 2 && houses - (l + r) <= houses / 2)
        {
            p = w;
        }
    }
}

void compile2(int w, int odl)
{
    if (tab[w].left == -1 && tab[w].right == -1)
    {
        cout << w << ":" << odl << " ";
    }
}

void preOrder(int w)
{
    if (w == -1)
    {
        return;
    }
    compile(w);
    preOrder(tab[w].left);
    preOrder(tab[w].right);
}

void inOrder(int w)
{
    if (w == -1)
    {
        return;
    }
    inOrder(tab[w].left);
    compile(w);
    inOrder(tab[w].right);
}

void postOrder(int w)
{
    if (w == -1)
    {
        return;
    }
    postOrder(tab[w].left);
    postOrder(tab[w].right);
    compile(w);
}

void preOrder2(int w, int odl)
{
    if (w == -1)
    {
        return;
    }
    compile2(w, odl);
    preOrder2(tab[w].left, odl + 1);
    preOrder2(tab[w].right, odl + 1);
}

void inOrder2(int w, int odl)
{
    if (w == -1)
    {
        return;
    }
    inOrder2(tab[w].left, odl + 1);
    compile2(w, odl);
    inOrder2(tab[w].right, odl + 1);
}

void postOrder2(int w, int odl)
{
    if (w == -1)
    {
        return;
    }
    postOrder2(tab[w].left, odl + 1);
    postOrder2(tab[w].right, odl + 1);
    compile2(w, odl);
}

void doIt()
{
    p = -1;
    qq = 0;
    cin >> n;
    for (int x = 0; x < n; x++)
    {
        cin >> tab[x].left >> tab[x].right;
    }

    calculateTreeSize(0);
    calculateHouses(0);
    houses = numberOfHouses[0];
    getResult(0, 0, INT32_MAX);
    string order;
    cin >> order;

    if (order == "PREORDER")
    {
        preOrder(0);
        cout << endl;
        preOrder2(0, 0);
    }
    if (order == "INORDER")
    {
        inOrder(0);
        cout << endl;
        inOrder2(0, 0);
    }
    if (order == "POSTORDER")
    {
        postOrder(0);
        cout << endl;
        postOrder2(0, 0);
    }

    cout << endl;

    for (int x = 0; x < n; x++)
    {
        cout << x << ":" << res[x].number << ":" << res[x].distance << " ";
    }
    cout << endl;
    cout << p << endl;

    //result.clear();
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