#include <iostream>
#include <queue>

using namespace std;
void doIt()
{
    priority_queue<int> q;

    int a;
    int ilosc = 0;
    int najmniejsza;
    int mala;
    int k = 3403434;
    int suma = 0;

    for (int i=-1; i<k; i++)
    {
        if (i==-1)
        {
            cin >> k;
        }
        else
        {
            cin >> a;
            q.push(a*-1);
        }
    }

    while(true)
    {
        najmniejsza = q.top();
        q.pop();
        mala = q.top();
        q.pop();
        q.push(najmniejsza+mala);
        suma += najmniejsza+mala;
        ilosc++;
        if (q.size()==1)
        {
            break;
        }
    }

    cout << suma*-1 << endl;

}
int main()
{
    int a;
    cin >> a;
    while (a--)
    {
        doIt();
    }
}
