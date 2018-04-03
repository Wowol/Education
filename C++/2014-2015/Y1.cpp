#include <iostream>

using namespace std;

struct przycisk
{
    char znak1;
    char znak2;
    char znak3;
    char znak4;
};

przycisk tab[8];



int doIt()
{
    string org;
    string nowy;
    cin >> org;
    cin >> nowy;

    for (int x=0; x<org.size(); x++)
    {
        for (int z=0; z<8; z++)
        {
            char znakOrg = org[x];
            bool znalazlo = false;
            if (tab[z].znak1==org[x] || tab[z].znak2==org[x] || tab[z].znak3==org[x] || tab[z].znak4==org[x])
            {
                if (tab[z].znak1==nowy[x] || tab[z].znak2==nowy[x]  || tab[z].znak3==nowy[x] || tab[z].znak4==nowy[x])
                {
                    znalazlo = true;
                }
                if (znalazlo==false)
                {
                    cout << "NIE" << endl;
                    return 0;
                }
            }
        }
    }

    cout << "TAK" << endl;



}

int main()
{
    tab[0].znak1 = 'A';
    tab[0].znak2 = 'B';
    tab[0].znak3 = 'C';
    tab[1].znak1 = 'D';
    tab[1].znak2 = 'E';
    tab[1].znak3 = 'F';
    tab[2].znak1 = 'G';
    tab[2].znak2 = 'H';
    tab[2].znak3 = 'I';
    tab[3].znak1 = 'J';
    tab[3].znak2 = 'K';
    tab[3].znak3 = 'L';
    tab[4].znak1 = 'M';
    tab[4].znak2 = 'N';
    tab[4].znak3 = 'O';
    tab[5].znak1 = 'P';
    tab[5].znak2 = 'Q';
    tab[5].znak3 = 'R';
    tab[5].znak4 = 'S';
    tab[6].znak1 = 'T';
    tab[6].znak2 = 'U';
    tab[6].znak3 = 'V';
    tab[7].znak1 = 'W';
    tab[7].znak2 = 'X';
    tab[7].znak3 = 'Y';
    tab[7].znak4 = 'Z';
    int n;
    cin >> n;
    while (n--)
    {
        doIt();
    }
}
