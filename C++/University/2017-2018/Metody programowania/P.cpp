#include <algorithm>
#include <iostream>
#include <string>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000005

using namespace std;

string tab[MAX];
int n;

int randNumber(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

pair<int, int> transfer(int left, int right, int indexOfElement)
{
    string element = tab[indexOfElement];
    swap(tab[indexOfElement], tab[right]);

    int lowerItem = left - 1;
    for (int x = left; x < right; x++)
    {
        if (tab[x] + element <= element + tab[x])
        {
            lowerItem++;
            swap(tab[lowerItem], tab[x]);
        }
    }

    swap(tab[++lowerItem], tab[right]);
    int p = lowerItem;
    for (int x = left; x < lowerItem; x++)
    {
        if (tab[x] == element)
        {
            swap(tab[x], tab[--lowerItem]);
        }
    }
    return make_pair(lowerItem, p);
}

void quickSort()
{
    stack<int> st;
    st.push(n - 1);
    st.push(0);

    while (!st.empty())
    {
        int left = st.top();
        st.pop();
        int right = st.top();
        st.pop();

        if (left > right)
            continue;

        int randElementIndex = randNumber(left, right);
        pair<int, int> newIndexes = transfer(left, right, randElementIndex);
        st.push(newIndexes.first - 1);
        st.push(left);

        st.push(right);
        st.push(newIndexes.second + 1);
    }
}

void doIt()
{
    cin >> n;
    for (int x = 0; x < n; x++)
    {
        cin >> tab[x];
    }
    quickSort();
    for (int x = n - 1; x >= 0; x--)
    {
        cout << tab[x];
    }
    cout << endl;
    // while (true)
    // {
    //     s a;
    //     s b;
    //     cin >> a.s >> b.s;
    //     cout << (a < b) << endl;
    // }
}

int main()
{
    ios_base::sync_with_stdio(0);
    time_t tt;
    int zarodek = time(&tt);
    srand(zarodek);
    int z;
    cin >> z;
    while (z--)
    {
        doIt();
    }
}