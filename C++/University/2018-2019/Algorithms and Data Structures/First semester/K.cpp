#include <iostream>
#include <algorithm>
#define MAX 1000006

using namespace std;
int base = 10;

int han[MAX];
int jabba[MAX];

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
    
    sort(han, han+n);
    sort(jabba, jabba+n);

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

    cout << points * 200 << endl;
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
