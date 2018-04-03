#include <iostream>
#include <map>

using namespace std;



void licz()
{
    map <string, string> m;
    int n;
    cin >> n;
    string imie;
    string poprzednieImie = "";

    for (int i=0; i<n; i++)
    {
        cin >> imie;
        if (m.count(imie) > 0)
        {
            cout << m[imie] << " ";
        }

        else
        {
            cout << "- ";
        }

        if (i!=0)
        {
            if (poprzednieImie != "" && poprzednieImie != imie)
                m[poprzednieImie]=imie;
        }

        poprzednieImie = imie;
    }

    cout << endl;
}

int main()
{
    int c;
    cin >> c;
    while (c--)
    {
        licz();
    }
}
