#include <iostream>
#include <vector>
#include <queue>


using namespace std;

#define MAXLUDZI  200005
#define maxpolaczen 500006

int tab[MAXLUDZI];
int n=MAXLUDZI-4;
//std::priority_queue< pair<int, int> > kolejka;
std::vector< std::vector<int> > graph(MAXLUDZI);


int BFS(int wierzcholek)
{
    std::queue<int> kolejka;
    int actual = 0;
    int a = 0;
    int proba = graph.size();
    int k=0;
    std::vector <int> znaj;
    std::vector <int>::iterator i;
    znaj = graph[wierzcholek];
    i = znaj.begin();
    tab[wierzcholek]=0;

    k = znaj.size();
    kolejka.push(wierzcholek);
    while (!kolejka.empty())
    {
        for (int x=0; x<k; x++)
        {
            actual=znaj[x];
            if (tab[actual]==0 && actual!=wierzcholek)
            {
                actual = znaj[x];
                kolejka.push(actual);
                tab[actual] = tab[a]+1;
            }
        }
        if (!kolejka.empty()) kolejka.pop();
        if (!kolejka.empty()) a = kolejka.front();
        znaj=graph[a];
        k = znaj.size();

    }
}

void doIt()
{
    int m;
    int znaj;
    int myNumber;

    cin >> n >> m;

    for (int i=0; i<m; i++)
    {
        int a,b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    cin >> myNumber;

    cout << "Znajomi numeru " << myNumber << ":" << endl;
    int grupy = 1;
    int ileLudzi = 0;
    BFS(myNumber);

    for (int z=0; z<MAXLUDZI; z++)
    {
        if (tab[z]!=0)
        {
            cout << z << ": " << tab[z] << endl;
        }
    }



        for (int q=1; q<=n; q++)
        {
            if (n==ileLudzi || q==MAXLUDZI-2) break;
            ileLudzi++;
            if (tab[q]==0 && q!=myNumber)
            {
                tab[q]=1;
                BFS(q);
                grupy++;
            }

        }
    cout << "Grup znajomych jest " << grupy << "." << endl;
}


int main()
{
    int a;
    cin >> a;
    while (a--)
    {
        for(int x=0; x<n+2; x++)
        {
            tab[x]=0;
            graph[x].clear();
        }
        doIt();


    }
}
