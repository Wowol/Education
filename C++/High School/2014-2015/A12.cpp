#include <iostream>
#include <sstream>
using namespace std;

int cyfra = 0;

string zamiana(int n)
{
    string wynik;

    string podstawa;
    string pol;
    string wieksza;

    if (cyfra==1)
    {
        podstawa = "I";
        pol = "V";
        wieksza = "X";
    }
    if (cyfra==2)
    {
        podstawa = "X";
        pol = "L";
        wieksza = "C";
    }

    if (cyfra==3)
    {
        podstawa = "C";
        pol = "D";
        wieksza = "M";
    }
    if (cyfra==4)
    {
        for (int i=0; i<n; i++)
        {
            wynik = wynik + "M";
        }
        return wynik;
    }




    if (n <= 3)
    {
        for (int i=0; i<n; i++)
        {
            wynik = wynik + podstawa;
        }
    }

    if (n == 4)
    {
        wynik = podstawa + pol;
    }

    if (n == 5)
    {
        wynik = pol;
    }

    if (n > 5 && n < 9)
    {
        for (int i=0; i<n-5; i++)
        {
            wynik = wynik + podstawa;
        }
        wynik = pol + wynik;
    }

    if (n == 9)
    {
        wynik = podstawa + wieksza;
    }

    if (n == 10)
    {
        wynik = wieksza;
    }

    return wynik;


}



int main()
{
    string wynik;
    int liczba = 0;
    int operacje = liczba;
    int tysiace = 0;
    int setki = 0;
    int dziesiatki = 0;
    int jednosci = 0;
    string liczbRzymska;

    string tablica[2001];
    for (int i = 1; i<2001; i++)
    {
        liczba = i;
        operacje = liczba;

        tysiace = operacje / 1000;
        operacje = operacje-tysiace*1000;

        setki = operacje / 100;
        operacje = operacje - setki*100;

        dziesiatki = operacje / 10;
        operacje = operacje - dziesiatki*10;

        jednosci = operacje;


        cyfra = 4;
        wynik = wynik + zamiana(tysiace);

        cyfra = 3;
        wynik = wynik + zamiana(setki);

        cyfra = 2;
        wynik = wynik + zamiana(dziesiatki);

        cyfra = 1;
        wynik = wynik + zamiana(jednosci);


        tablica[i] = wynik;
        wynik = "";
    }

        int n = 0;


        cin >> n;

        for (int m = 0; m<n; m++)
        {
            string liczbaString;
            cin >> liczbaString;

            int i;
            istringstream iss(liczbaString);
            iss >> i;

            if (i==0)
            {
                for (int i=0; i<2001; i++)
                {
                    if (tablica[i]==liczbaString)
                    {
                        cout << i;
                        break;
                    }
                }
            }

            else
            {
                cout << tablica[i];
            }
            cout << endl;
        }



   // cout << tablica[liczba];






   /* tysiace = operacje / 1000;
    operacje = operacje-tysiace*1000;

    setki = operacje / 100;
    operacje = operacje - setki*100;

    dziesiatki = operacje / 10;
    operacje = operacje - dziesiatki*10;

    jednosci = operacje;

    cyfra = 4;
    wynik = wynik + zamiana(tysiace);

    cyfra = 3;
    wynik = wynik + zamiana(setki);

    cyfra = 2;
    wynik = wynik + zamiana(dziesiatki);

    cyfra = 1;
    wynik = wynik + zamiana(jednosci);*/





}



