#include <iostream>
#include <algorithm>
#define MAX 1000006

using namespace std;
int base = 10;

int han[MAX];
int jabba[MAX];

int power(int b, int w)
{
    int result = 1;
    while (w--)
    {
        result *= b;
    }
    return result;
}

int getDigit(int number, int position)
{
    return (number / (power(base, position))) % base;
}

void countSort(int tab[], int n, int position)
{
    int countArray[base + 1];
    int output[n];

    for (int x = 0; x <= base; x++)
    {
        countArray[x] = 0;
    }
    for (int x = 0; x < n; x++)
    {
        int temp = getDigit(tab[x], position);
        countArray[temp]++;
    }

    for (int x = 1; x <= base; x++)
    {
        countArray[x] = countArray[x - 1] + countArray[x];
    }

    for (int x = n - 1; x >= 0; x--)
    {
        int temp = tab[x];
        int digit = getDigit(temp, position);
        int p = --countArray[digit];
        output[p] = temp;
    }
    for (int x = 0; x < n; x++)
    {
        tab[x] = output[x];
    }
}

void radixSort(int tab[], int n)
{
    int m = *max_element(tab, tab + n);
    int b = 0;
    while (m > 0)
    {
        m /= base;
        b++;
    }

    for (int x = 0; x < b; x++)
    {
        countSort(tab, n, x);
    }
}

void doIt()
{
    int n;
    cin >> n;
    for (int x = 0; x < n; x++)
    {
        cin >> han[x];
    }

    for (int x = 0; x < n; x++)
    {
        cin >> jabba[x];
    }

    radixSort(han, n);
    radixSort(jabba, n);
    reverse(han, han + n);
    reverse(jabba, jabba + n);

    int k = n;
    int hanEndIndex = n - 1;
    int jabbaEndIndex = n - 1;
    int hanBeginIndex = 0;
    int jabbaBeginIndex = 0;
    int points = 0;
    while (k--)
    {
        if (han[hanEndIndex] > jabba[jabbaEndIndex])
        {
            points++;
            jabbaEndIndex--;
            hanEndIndex--;
        }
        else
        {
            if (han[hanBeginIndex] > jabba[jabbaBeginIndex])
            {
                points++;
                jabbaBeginIndex++;
                hanBeginIndex++;
            }
            else
            {
                // Najslabszy gra z najelpszym
                if (han[hanEndIndex] < jabba[jabbaBeginIndex])
                {
                    points--;
                }
                jabbaBeginIndex++;
                hanEndIndex--;
            }
        }
    }

    cout << points * 20 << endl;
}

int main()
{
    int z;
    cin >> z;
    while (z--)
    {
        doIt();
    }

    // int n = 100000;
    // int tab[n];
    // for (int x = 0; x < n; x++)
    // {
    //     tab[x] = x;
    // }
    // random_shuffle(tab, tab + n);
    // radixSort(tab, n);
    // for (int x = 0; x < n; x++)
    // {
    //     cout << "n";
    //     if (tab[x] != x)
    //     {
    //         cout << "chuj!";
    //         getchar();
    //     }
    // }
    // getchar();
}
