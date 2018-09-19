#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

struct punkt
{
	long long x;
	long long y;
};

long long n;
const long long MAX = 1000006;
const long long MAX_XY = 1000000005;

long long minY = MAX_XY;
long long minX = MAX_XY;
long long minimumIndex = -1;

punkt pierwszy;



long long iloczynWektorowy(punkt a, punkt b, punkt c)
{
   return (b.x-a.x) * (c.y-b.y) - (c.x-b.x) * (b.y-a.y);
}

bool porownaj (punkt a, punkt c)
{
    if (iloczynWektorowy(a, pierwszy ,c)==0)
    {
        long long odl1 = (a.x-pierwszy.x)*(a.x-pierwszy.x)+(a.y-pierwszy.y)*(a.y-pierwszy.y);
        long long odl2 = (c.x-pierwszy.x)*(c.x-pierwszy.x)+(c.y-pierwszy.y)*(c.y-pierwszy.y);
        return odl1>odl2;
    }
    else
    {
        return iloczynWektorowy(a, pierwszy, c)<0;
    }
}

void doIt()
{
	cin >> n;
	punkt tab[MAX];
	for (int x=0; x<n; x++)
    {
        tab[x].x = 9999;
        tab[x].y = 9999;
    }
    stack<punkt> s;

	minY = MAX_XY;
	minX = MAX_XY;
	minimumIndex = -1;

	for (long long x = 0; x<n; x++)
	{
        punkt nowy;
        cin >> nowy.x >> nowy.y;

        if (nowy.y==minY)
        {
            if (nowy.x<minX)
            {
                minimumIndex = x;
                minY = nowy.y;
                minX = nowy.x;
            }
        }

        if (nowy.y<minY)
        {
            minimumIndex = x;
            minY = nowy.y;
            minX = nowy.x;
        }

        tab[x] = nowy;
	}

    pierwszy.x = minX;
    pierwszy.y = minY;

    punkt newTab[MAX];
    long long p = 0;
    for (long long x=0; p<n; x++)
    {
        if (x!=minimumIndex)
        {
            newTab[p] = tab[x];
            p++;
        }
    }

    sort(newTab, newTab+n-1, porownaj);

    punkt koncowa[MAX]; //XDDD
    long long z = 0;
    for (long long x=0; x<n-1; x++)
    {
        if (iloczynWektorowy(newTab[x], pierwszy, newTab[x+1])!=0)
        {
            koncowa[z] = newTab[x];
            z++;
        }
        else
        {
            koncowa[z] = newTab[x];
            z++;

            while (true)
            {
               // koncowa[z] = newTab[x];
                x++;
                //z++;

                if (x==n-1)
                {
                    break;
                }

                if (iloczynWektorowy(newTab[x], pierwszy, newTab[x+1])!=0)
                {
                    break;
                }
            }
        }
    }



    s.push(pierwszy);
    s.push(koncowa[0]);
    s.push(koncowa[1]);

    for (long long i=2; i<z; i++)
    {
        while (true)
        {
            punkt top = s.top();
            if (s.empty()) return;
            s.pop();
            punkt topTop = s.top();
            s.push(top);
            if (iloczynWektorowy(top, topTop, koncowa[i])<0)
            {
                break;
            }
            if (s.empty()) return;
            s.pop();
        }

        s.push(koncowa[i]);
    }

    vector<punkt> V;
    V.clear();
    punkt m;
    m.x = 0;
    m.y = 0;
    V.push_back(m);
    while (!s.empty())
    {
        V.push_back(s.top());
        s.pop();
    }

    V[0] = V[V.size()-1];
    V.push_back(V[1]);

    long long sum = 0;
    for (long long x=1; x<V.size()-1; x++)
    {
        sum+=V[x].y*(V[x-1].x-V[x+1].x);
    }
    sum = abs(sum);

    cout << sum << endl;
	//cout << minimumIndex << " " << minX << " " << minY << endl;*/
}

int main()
{
	long long z;
	cin >> z;
	while (z--)
		doIt();
}
