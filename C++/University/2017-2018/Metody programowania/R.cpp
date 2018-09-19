#include <iostream>
#include <algorithm>
#define MAX 5000005
using namespace std;

int n, k;
int tab[MAX];
int helper[5];

pair<int, int> transfer(int t[], int left, int right, int element)
{
    int indexOfElement;
    for (int x = left; x <= right; x++)
    {
        if (t[x] == element)
        {
            indexOfElement = x;
            break;
        }
    }

    swap(t[indexOfElement], t[right]);

    int lowerItem = left - 1;
    for (int x = left; x < right; x++)
    {
        if (t[x] <= element)
        {
            lowerItem++;
            swap(t[lowerItem], t[x]);
        }
    }

    swap(t[++lowerItem], t[right]);

    int p = lowerItem;
    for (int x = left; x < lowerItem; x++)
    {
        if (t[x] == element)
        {
            swap(t[x], t[--lowerItem]);
        }
    }
    return make_pair(lowerItem, p);
}

int medianOfMedians(int t[], int left, int right, int k)
{
    int n = right - left + 1;
    if (k < 0 || k > n)
    {
        // >:(, something IS WRONG!
        return -1;
    }
    int numberOfFives = n / 5 + (n % 5 != 0);
    int medians[numberOfFives];
    for (int x = 0; x < numberOfFives; x++)
    {
        int y;
        for (y = 0; y < 5 && x * 5 + y < n; y++)
        {
            int qq = 0;
            if (x * 5 + y < n)
            {
                helper[y] = t[left + x * 5 + y];
            }
        }
        sort(helper, helper + y);
        medians[x] = helper[y / 2];
    }

    int m;
    if (numberOfFives == 1)
    {
        m = medians[0];
    }
    else
    {
        m = medianOfMedians(medians, 0, numberOfFives - 1, numberOfFives / 2);
    }

    pair<int, int> p = transfer(t, left, right, m);
    if (p.first - left <= k && p.second - left >= k)
    {
        return t[p.first];
    }
    else if (p.second - left > k)
    {
        return medianOfMedians(t, left, p.first - 1, k);
    }
    else
    {
        return medianOfMedians(t, p.second + 1, right, k - p.second + left - 1);
    }
}

void doIt()
{
    cin >> n >> k;
    for (int x = 1; x <= n; x++)
    {
        cin >> tab[x];
    }
    cout << medianOfMedians(tab, 1, n, k - 1) << endl;

    //     for (int q = 0; q < n; q++)
    //     {
    //         cout << medianOfMedians(tab, 1, n, q) << " ";
    //     }
    //     cout << endl;

    //     sort(tab + 1, tab + n + 1);
    //     for (int x = 1; x <= n; x++)
    //     {
    //         cout << tab[x] << " ";
    //     }
    //     cout << endl;
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