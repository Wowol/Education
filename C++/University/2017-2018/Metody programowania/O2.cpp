#include <iostream>
#define MAX 1000006

using namespace std;

int *t;
int *leftArray;
int *rightArray;
long long numberOfInversions;
int n, k;

void merge(int l, int m, int r)
{
    int leftArraySize = m - l + 1;
    int rightArraySize = r - m;

    for (int x = 0; x < leftArraySize; x++)
    {
        leftArray[x] = t[l + x];
    }

    for (int x = 0; x < rightArraySize; x++)
    {
        rightArray[x] = t[m + 1 + x];
    }

    int leftIndex = 0;
    int rightIndex = 0;
    int currentIndex = l;

    while (leftIndex < leftArraySize && rightIndex < rightArraySize)
    {
        if (leftArray[leftIndex] + k < rightArray[rightIndex])
        {
            numberOfInversions += leftArraySize - leftIndex;
            rightIndex++;
        }
        else
        {
            leftIndex++;
        }
    }

    leftIndex = 0;
    rightIndex = 0;
    currentIndex = l;

    while (leftIndex < leftArraySize && rightIndex < rightArraySize)
    {
        if (leftArray[leftIndex] >= rightArray[rightIndex])
        {
            t[currentIndex] = leftArray[leftIndex];
            leftIndex++;
        }
        else
        {
            t[currentIndex] = rightArray[rightIndex];
            rightIndex++;
        }
        currentIndex++;
    }

    while (leftIndex < leftArraySize)
    {
        t[currentIndex] = leftArray[leftIndex];
        currentIndex++;
        leftIndex++;
    }

    while (rightIndex < rightArraySize)
    {
        t[currentIndex] = rightArray[rightIndex];
        currentIndex++;
        rightIndex++;
    }
}

void mergeSort(int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        mergeSort(l, m);
        mergeSort(m + 1, r);
        merge(l, m, r);
    }
}

void doIt()
{
    cin >> n >> k;

    numberOfInversions = 0;

    delete[] t;
    delete[] leftArray;
    delete[] rightArray;
    t = new int[n + 5];
    leftArray = new int[n + 5];
    rightArray = new int[n + 5];
    for (int x = 0; x < n; x++)
    {
        cin >> t[x];
    }
    mergeSort(0, n - 1);
    // for (int x = 0; x < n; x++)
    // {
    //     cout << t[x] << " ";
    // }

    cout << numberOfInversions;
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