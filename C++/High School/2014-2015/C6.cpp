#include <iostream>
#include <vector>

using namespace std;
#define MAX 100005
int czasWejscia[MAX];
int czasWyjscia[MAX];
int color[MAX];
int tab[MAX];
int aktualnyCzas = 0;
int a=0;
std::vector < std::vector<int> > graph(MAX);

int DFS(int punkt)
{
      color[punkt]=1;
      std::vector<int> sasiedzi;
      sasiedzi = graph[punkt];
      for (int z=0; z<sasiedzi.size(); z++)
      {
              if (color[sasiedzi[z]]==0)
              {

                      aktualnyCzas++;
                      czasWejscia[sasiedzi[z]]=aktualnyCzas;
                      DFS(sasiedzi[z]);
              }
      }
      aktualnyCzas++;
      czasWyjscia[punkt] = aktualnyCzas;
      color[punkt]=2;
}



void doIt()
{
    int b,c;
    int doKtorejWpada, wpadajaca;

    cin >> a;
    for (int z=1; z<a; z++)
    {
      cin >> c;
      graph[c].push_back(z);
    }

    DFS(0);

    cin >> b;


      for (int z=0; z<b; z++)
    {
        cin >> doKtorejWpada >> wpadajaca;
       // if (czasWejscia[wpadajaca]<czasWyjscia[doKtorejWpada])
        if (czasWejscia[wpadajaca]>czasWejscia[doKtorejWpada]&&czasWyjscia[wpadajaca]<czasWyjscia[doKtorejWpada])
        {
              cout << "TAK";
        }
        else
        {
              cout << "NIE";
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
        doIt();
        for (int z=0; z<a+2; z++)
        {
              czasWejscia[z]=0;
                      czasWyjscia[z]=0;
                      color[z]=0;
                      tab[z]=0;
        }
        aktualnyCzas = 0;
        std::vector <std::vector<int> > nowy(MAX);
        graph = nowy;

    }
}
