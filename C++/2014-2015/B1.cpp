#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int x;
    cin >> x;

    for (int z = 0; z<x; z++)
    {
        int a;
        int karta;
        int b;
        int c;
        int d;
        int liczba;
        queue <int> q1;
        queue <int> q2;
        cin >> a;
        for (int p=0; p<a; p++)
        {
            cin >> b;
            q1.push(b);
        }

        cin >> c;
        for (int p=0; p<c; p++)
        {
            cin >> d;
            q2.push(d);
        }

        cin >> liczba;

        for (int p=0; p<liczba; p++)
        {
            if (q1.front()>q2.front())
            {
                karta = q1.front();
                q1.pop();
                q1.push(q2.front());
                q1.push(karta);
                q2.pop();
            }
            else
            {
                karta = q2.front();
                q2.pop();
                q2.push(q1.front());
                q2.push(karta);
                q1.pop();
            }
            if (q1.empty())
            {
                cout << "B wygrywa w turze " << p+1 << ".";
                break;
            }

            if (q2.empty())
            {
                cout << "A wygrywa w turze " << p+1 << ".";
                break;
            }
        }

        if (q1.empty()==false && q2.empty()==false)
        {
            cout << "A:";
            while (q1.empty() == false)
            {
                cout << " " << q1.front();
                q1.pop();
            }
            cout << endl;

            cout << "B:";
            while (q2.empty() == false)
            {
                cout << " " << q2.front();
                q2.pop();
            }
        }

        cout << endl;

    }












}
