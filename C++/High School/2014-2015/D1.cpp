#include <iostream>


using namespace std;

int doIt()
{
    int a,wielkosc;
    int pomocniczaMasa = 0;
    int cena, masa;
    bool drugaJestNowa = true;
    std::pair<int, int> pierwsza[10005] = {make_pair(0, 0)};
    std::pair<int, int> druga[10005] = {make_pair(0, 0)};
    cin >> a >> wielkosc;

    for (int i=1; i<=a; i++)
    {
        cin >> masa >> cena;
        if (drugaJestNowa)
        {
            for (int x=0; x<=wielkosc; x++)
            {
                if (x-masa<0)
                {
                    if (masa<=x)
                    {
                        druga[x].second = cena;
                        druga[x].first = masa;
                    }
                    else
                    {
                         druga[x].second = pierwsza[x].second;
                         druga[x].first = pierwsza[x].first;
                    }
                    continue;
                }

                if (pierwsza[x].second>cena+pierwsza[x-masa].second || pierwsza[x-masa].first+masa>x)
                {
                    druga[x].second = pierwsza[x].second;
                    druga[x].first = pierwsza[x].first;
                }
                else
                {
                    if (pierwsza[x-masa].first+masa<=x)
                    {
                        druga[x].second = pierwsza[x-masa].second+cena;
                        druga[x].first = pierwsza[x-masa].first+masa;
                    }
                    else
                    {
                        druga[x].second = pierwsza[x-masa].second;
                        druga[x].first = pierwsza[x-masa].first;
                    }
                }
            }

            drugaJestNowa = false;
        }

        else
        {
            for (int x=0; x<=wielkosc; x++)
            {
                if (x-masa<0)
                {
                    if (masa<=x)
                    {
                        druga[x].second = cena;
                        druga[x].first = masa;
                    }
                    else
                    {
                         pierwsza[x].second = druga[x].second;
                         pierwsza[x].first = druga[x].first;
                    }
                    continue;
                }

                if (druga[x].second>cena+druga[x-masa].second || druga[x-masa].first+masa>x)
                {
                    pierwsza[x].second = druga[x].second;
                    pierwsza[x].first = druga[x].first;
                }
                else
                {
                    if (druga[x-masa].first+masa<=x)
                    {
                        pierwsza[x].second = druga[x-masa].second+cena;
                        pierwsza[x].first = druga[x-masa].first+masa;
                    }

                    else
                    {
                        druga[x].second = pierwsza[x-masa].second;
                        druga[x].first = pierwsza[x-masa].first;
                    }
                }
            }
            drugaJestNowa = true;
        }
    }


    if (drugaJestNowa)
    {
        cout << pierwsza[wielkosc].second << endl;
    }
    else
    {
        cout << druga[wielkosc].second << endl;
    }
}


int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        doIt();
    }
}
