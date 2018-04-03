#include <iostream>
#include <set>
using namespace std;

const int MAX = 5e4;


int doIt()
{
    int n;
    cin >> n;
    int tab[MAX];
    for (int x=0; x<n; x++)
    {
        cin >> tab[x];
    }
    if (n==1)
    {
        cout << 1 << endl;
        return 0;
    }
   // int first = n/2;
    unsigned long long nowyKrol = n;
    unsigned long long jakasLadnaDziesiatka = 1;
    int first = n/2;
    int maks = n;
    int minn = 0;
    while (maks!=minn)
    {
        set<unsigned long long> secik;
        secik.clear();
        jakasLadnaDziesiatka = 1;
        for (int z=1; z<first; z++)
        {
            jakasLadnaDziesiatka *= (unsigned long long)1e6+1;
        }

        unsigned long long liczba = 0;
        unsigned long long q = 1;
        for(int z=first-1; z>=0; z--)
        {
            liczba+=(tab[z]*q);
            q*=(int)1e6+1;
        }
        secik.insert(liczba);

        bool znalezioneGowniane = false;
        for (int x=first; x<n; x++)
        {
            unsigned long long l1 = (liczba-tab[x-first]*jakasLadnaDziesiatka);
            liczba = (liczba-tab[x-first]*jakasLadnaDziesiatka)*((unsigned long long)1e6+1)+tab[x];
            if (secik.count(liczba)!=0)
            {
                znalezioneGowniane = true;
                break;
            }
            else
            {
                secik.insert(liczba);
            }
        }
        if (znalezioneGowniane)
        {
            minn = first;
        }
        else
        {
            maks = first;
        }
        int staryFirst = first;
        first = (minn+maks)/2;
        if (first==minn || first==maks)
        {
            cout << maks << endl;
            return 0;
        }

        if (first==maks)
        {
            cout << minn << endl;
            return 0;
        }

        //jakasLadnaDziesiatka*=(int)1e6+1;
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
