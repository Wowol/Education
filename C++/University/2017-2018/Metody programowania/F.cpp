#include <iostream>
#define left first
#define right second

using namespace std;

void doIt()
{
    pair<int, int> *nodes;
    int n, root;
    cin >> n >> root;
    nodes = new pair<int, int>[n+10];
    for (int x = 1; x <= n; x++)
    {
        cin >> nodes[x].left >> nodes[x].right;
    }

    int current = root;
    int previous = -2;
    while (current != -2)
    {
        cout << current << " ";
        do
        {
            int temp = nodes[current].left;
            nodes[current].left = nodes[current].right;
            nodes[current].right = previous;
            previous = current;
            current = temp;
            if (current == 0)
            {
                current = previous;
                previous = 0;
            }
        } while (previous == 0);
    }
    delete[] nodes;
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