#include <iostream>
#include <queue>
#include <string.h>

using namespace std;

std::queue< std::pair< int, int > > kolejka;
char tab[2005][2005];
int wynik[2005][2005];
int a = 2005;
int b = 2005;

int BFS(int maxY, int maxX)
{
    maxY--;
    maxX--;
    std::pair<int, int> glowny;
    std::pair<int, int> poboczny;

    while (!kolejka.empty())
    {
        glowny = kolejka.front();
        if (glowny.first!=0) // LEWY
        {
            poboczny=make_pair(glowny.first-1, glowny.second);
            if (wynik[poboczny.first][poboczny.second]==0 && tab[poboczny.second][poboczny.first]!='1')
            {
                wynik[poboczny.first][poboczny.second]=wynik[glowny.first][glowny.second]+1;
                if (tab[poboczny.second][poboczny.first] != '2')
                {
                    kolejka.push(poboczny);
                }
            }
        }
        if (glowny.first!=maxX) // PRAWY
        {
            poboczny=make_pair(glowny.first+1, glowny.second);
            if (wynik[poboczny.first][poboczny.second]==0 && tab[poboczny.second][poboczny.first]!='1')
            {
                poboczny=make_pair(glowny.first+1, glowny.second);
                wynik[poboczny.first][poboczny.second]=wynik[glowny.first][glowny.second]+1;
                if (tab[poboczny.second][poboczny.first] != '2')
                {
                    kolejka.push(poboczny);
                }
            }
        }


        if (glowny.second!=maxY) // DOLNY
        {
            poboczny=make_pair(glowny.first, glowny.second+1);
            if (wynik[poboczny.first][poboczny.second]==0 && tab[poboczny.second][poboczny.first]!='1')
            {
                wynik[poboczny.first][poboczny.second]=wynik[glowny.first][glowny.second]+1;
                if (tab[poboczny.second][poboczny.first] != '2')
                {
                    kolejka.push(poboczny);
                }
            }
        }


        if (glowny.second!=0) // Gorny
        {
            poboczny=make_pair(glowny.first, glowny.second-1);
            if (wynik[poboczny.first][poboczny.second]==0 && tab[poboczny.second][poboczny.first]!='1')
            {
                wynik[poboczny.first][poboczny.second]=wynik[glowny.first][glowny.second]+1;
                if (tab[poboczny.second][poboczny.first] != '2')
                {
                    kolejka.push(poboczny);
                }
            }
        }


        kolejka.pop();

    }

}




void doIt()
{
    string s;
    cin >> a >> b;
    for (int x=0; x<a; x++)
    {
        cin >> tab[x];

        for (int z=0; z<b; z++)
        {
            if (tab[x][z]=='1')
            {
                kolejka.push(make_pair(z,x));
            }
        }
    }

/*    for (int q=0; q<a; q++)
    {
        for (int z=0; z<b; z++)
        {
            if (tab[q][z]=='1')
            {
                kolejka.push(make_pair(z,q));
            }
        }
    }*/

    BFS(a,b);

    for (int q=0; q<a; q++)
    {
        for (int z=0; z<b; z++)
        {
            if (wynik[z][q]==0 && tab[q][z]!='1')
            {
                cout << "-1" << " ";
            }
            else
            {
                cout << wynik[z][q] << " ";
            }

        }

        cout << endl;
    }
}




int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        for (int x=0; x<a; x++)
        {
            for (int y=0; y<b; y++)
            {
                wynik[y][x]=0;
            }
        }
    //    memset (wynik, 0, sizeof(wynik));
        doIt();
    }
}
