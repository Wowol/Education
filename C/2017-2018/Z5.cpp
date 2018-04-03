#include <iostream>

using namespace std;

// int f(int z)
// {
//     int count = 0;
//     for (int x = z; x < z + 10000; x++)
//     {
//         if (x % 3 == 0)
//         {
//             count++;
//         }
//     }
//     return count;
// }

void doIt()
{
    string s;
    cin >> s;
    int questionMarks = 0;
    int sum = 0;
    for (int x = 0; x < s.size(); x++)
    {
        if (s[x] == '?')
        {
            questionMarks++;
        }
        else
        {
            sum += s[x] - '0';
        }
    }

    if (questionMarks == 1 && s.size() == 1)
    {
        cout << 4 << endl;
        return;
    }
    int mod = sum % 3;

    if (questionMarks == 0)
    {
        if (mod == 0)
            cout << 0;
        else
            cout << -1;
        cout << endl;
        return;
    }

    if (s[0] == '?')
    {
        cout << 3;
        for (int x=0; x<questionMarks - 1; x++)
        {
            cout << 0;
        }
        cout << endl;
    }
    else
    {
        for (int x = 0; x < questionMarks - 1; x++)
        {
            cout << 3;
        }
        if (mod == 0)
        {
            cout << 4;
        }
        else
        {
            cout << 3;
        }
        cout << endl;
    }
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