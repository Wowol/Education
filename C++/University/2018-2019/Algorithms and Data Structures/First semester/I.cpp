#include <iostream>
#include <algorithm>
#include <vector>

#define MAX 3006

using namespace std;

int result[2][MAX];
vector<bool> path;

void doIt()
{

    string first, second;
    cin >> first >> second;

    result[0][0] = 0;
    result[1][0] = 0;

    for (int s = 0; s < second.size() + 2; s++)
    {
        result[0][s] = 0;
    }

    for (int f = 1; f <= first.size(); f++)
    {
        for (int s = 1; s <= second.size(); s++)
        {
            if (first[f - 1] == second[s - 1])
            {
                result[f % 2][s] = result[(f - 1) % 2][s - 1] + 1;
            }
            else
            {
                result[f % 2][s] = max(result[(f - 1) % 2][s], result[f % 2][s - 1]);
                if (result[(f - 1) % 2][s] > result[f % 2][s - 1])
                {
                    path[f * MAX + s] = true; // 1 - idziemy w gore
                }
                else
                {
                    path[f * MAX + s] = false; // 0 - idziemy w lewo
                }
            }
        }
    }
    cout << result[first.size() % 2][second.size()] << endl;

    int f = first.size();
    int s = second.size();
    string resultString;

    while (f != 0 && s != 0)
    {
        if (first[f - 1] == second[s - 1])
        {
            resultString += first[f - 1];
            f--;
            s--;
        }
        else if (path[f * MAX + s] == 1)
        {
            f--;
        }
        else
        {
            s--;
        }
    }

    reverse(resultString.begin(), resultString.end());
    cout << resultString << endl;
}

int main()
{
    path.resize(MAX * MAX + MAX + 5);
    int q = path.size();
    int z;
    cin >> z;
    while (z--)
    {
        doIt();
    }
}
