#include <iostream>
#include <vector>
#define MAX 2000006
#define left first
#define right second

using namespace std;

int n;

pair<int, int> tab[MAX];
vector<pair<int, int>> result;

void compile(int w, int odl)
{
    cout << w << " ";
    if (tab[w].left == -1 && tab[w].right == -1) result.push_back(make_pair(w, odl));
}

void preOrder(int w, int odl)
{
    if (w == -1)
    {
        return;
    }
    compile(w, odl);
    preOrder(tab[w].left, odl + 1);
    preOrder(tab[w].right, odl + 1);
}

void inOrder(int w, int odl)
{
    if (w == -1)
    {
        return;
    }
    inOrder(tab[w].left, odl + 1);
    compile(w, odl);
    inOrder(tab[w].right, odl + 1);
}

void postOrder(int w, int odl)
{
    if (w == -1)
    {
        return;
    }
    postOrder(tab[w].left, odl + 1);
    postOrder(tab[w].right, odl + 1);
    compile(w, odl);
}

void doIt()
{
    cin >> n;
    for (int x = 0; x < n; x++)
    {
        cin >> tab[x].left >> tab[x].right;
    }
    string order;
    cin >> order;
    if (order == "PREORDER")
    {
        preOrder(0, 0);
    }
    if (order == "INORDER")
    {
        inOrder(0, 0);
    }
    if (order == "POSTORDER")
    {
        postOrder(0, 0);
    }
    cout << endl;
    for (int x=0; x<result.size(); x++) 
    {
        cout << result[x].first <<":" <<result[x].second << " ";
    }
    result.clear();
    cout << endl;
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