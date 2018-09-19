#include <iostream>
#include <stack>

using namespace std;

int main()
{
    int n;
    int k;
    int s;
    cin >> s;
    for (int p=0; p<s; p++)
    {
        cin >> k;
        stack <int> s;

        for (int x=0; x<k; x++)
        {
            cin >> n;
            if (s.empty()==true)
            {
                s.push(n);
            }
            else
            {
               if (s.top()!=n)
                {
                    s.push(n);
                }
                else
                {
                    s.pop();
                }
            }

        }

        if (s.empty())
        {
            cout << "TAK" << endl;
        }
        else
        {
            cout << "NIE" << endl;
        }
    }
    return 0;
}
