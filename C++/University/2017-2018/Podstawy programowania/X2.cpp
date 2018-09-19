#include <stdio.h>
#include <iostream>
//#include "list.cpp"
#include <stddef.h>
#include <algorithm>

using namespace std;

class list
{

  public:
    struct player
    {
        string name;
        int points;
        player *next;
        player *nextByPoints;
    };
    bool reversed = false;

  private:
    player *head;
    player *tail;
    int size = 0;

  public:
    list()
    {
        head = new player;
        tail = new player;
        (*head).name = "<HEAD>";
        (*tail).name = "<TAIL>";
        (*head).next = tail;
        (*head).nextByPoints = tail;
        head->points = -1;
        tail->points = INT32_MAX;
    }

    void print2()
    {
        player *tab = new player[size];
        string s;
        s.clear();
        int p = 0;
        for (player *x = head->next; x != tail; x = x->next)
        {
            tab[p++] = *x;
        }
        if (reversed)
        {
            reverse(tab, tab + size);
        }
        for (int x = 0; x < size; x++)
        {
            cout << tab[x].name << " " << tab[x].points << endl;
        }
        delete[] tab;
    }

    void ranking()
    {
        player *tab = new player[size];
        string s;
        s.clear();
        int p = 0;
        for (player *x = head->nextByPoints; x != tail; x = x->nextByPoints)
        {
            tab[p++] = *x;
        }
        if (reversed)
        {
            reverse(tab, tab + size);
        }
        for (int x = 0; x < size; x++)
        {
            cout << tab[x].name << " " << tab[x].points << endl;
        }
        delete[] tab;
    }

    void clean()
    {
        while (head->next != tail)
        {
            player *next = head->next->next;
            delete head->next;
            head->next = next;
        }
        head->next = tail;
        head->nextByPoints = tail;
        size = 0;
        reversed = false;
    }

    void print()
    {
        cout << "BY NAME:" << endl;
        for (player *x = head->next; x != tail; x = x->next)
        {
            cout << x->name << "  " << x->points << "  " << x->next->name << endl;
        }
        cout << endl;

        cout << "BY POINTS:" << endl;
        for (player *x = head->nextByPoints; x != tail; x = x->nextByPoints)
        {
            cout << x->name << "  " << x->points << "  " << x->nextByPoints->name << endl;
        }
        cout << endl
             << endl;
    }

    bool empty()
    {
        return size == 0;
    }

    bool erase(string name)
    {
        player *x = head;
        while (x != tail && x->next->name < name)
        {
            x = x->next;
        }

        if (x == tail || x->next->name != name)
        {
            return false;
        }

        player *playerToDelete = x->next;
        x->next = playerToDelete->next;

        ////////////////////////
        x = head;
        while (x != tail && x->nextByPoints->points <= playerToDelete->points)
        {
            if (x->nextByPoints->name == name)
            {
                playerToDelete = x->nextByPoints;
                x->nextByPoints = playerToDelete->nextByPoints;
                break;
            }

            x = x->nextByPoints;
        }

        ///////////////////////

        delete playerToDelete;
        size--;
        return true;
    }

    bool correct(string name, int points)
    {
        player *current = head->next;
        while (current != tail)
        {
            if (current->name == name)
            {
                int currentPoints = current->points + points;
                currentPoints = max(currentPoints, 0);
                erase(current->name);
                insert(name, currentPoints);
                return true;
            }

            if (current->name > name)
            {
                return false;
            }
            current = current->next;
        }
        return false;
    }

    bool tryFind(string name, player &returnPlayer)
    {
        player *x = head->next;

        while (x != tail)
        {
            if (name == x->name)
            {
                returnPlayer = *x;
                return true;
            }
            if (x->name > name)
            {
                return false;
            }
            x = x->next;
        }
        return false;
    }

    void insert(string name, int points)
    {

        player *newPlayer = new player;
        newPlayer->name = name;
        newPlayer->points = points;
        player *current = head;
        while (current->next != tail && current->next->name <= newPlayer->name)
        {
            current = current->next;
        }

        if (newPlayer->name == current->name)
        {
            int currentPoints = current->points + newPlayer->points;
            erase(current->name);
            insert(newPlayer->name, currentPoints);
            return;
        }

        player *beforeNext = current->next;
        current->next = newPlayer;
        newPlayer->next = beforeNext;

        //////////////////////////////////////
        current = head;
        while (current->nextByPoints != tail &&
               (current->nextByPoints->points < newPlayer->points ||
                (current->nextByPoints->points == newPlayer->points && current->nextByPoints->name <= newPlayer->name)))
        {
            current = current->nextByPoints;
        }

        beforeNext = current->nextByPoints;
        current->nextByPoints = newPlayer;
        newPlayer->nextByPoints = beforeNext;
        ////////////////////////////////////

        size++;
    }
};

list l;

void add(string name, int points)
{
    l.insert(name, points);
}

void disq(string name)
{
    if (!l.erase(name))
    {
        cout << "ERROR " << name << endl;
    }
}

void find(string name)
{
    list::player p;
    if (l.tryFind(name, p))
    {
        cout << name << " " << p.points << endl;
    }
    else
    {
        cout << "ERROR " << name << endl;
    }
}

void correct(string name, int p)
{
    if (!l.correct(name, p))
    {
        cout << "ERROR " << name << endl;
    }
}

void change(string oldName, string newName)
{
    list::player old;
    list::player n;
    if (l.tryFind(oldName, old))
    {
        if (!l.tryFind(newName, n))
        {
            disq(oldName);
            add(newName, old.points);
        }
        else
        {
            cout << "ERROR " << oldName << " " << newName << endl;
        }
    }
    else
    {
        cout << "ERROR " << oldName << " " << newName << endl;
    }
}

void print()
{
    if (l.empty())
    {
        cout << "EMPTY" << endl;
    }
    l.print2();
}

void reverse()
{
    l.reversed = !l.reversed;
}

void clean()
{
    l.clean();
    cout << "CLEAN OK" << endl;
}

void printDesc()
{
    reverse();
    print();
    reverse();
}

void ranking()
{
    if (l.empty())
    {
        cout << "EMPTY" << endl;
    }
    else
    {
        l.ranking();
    }
}

void rankingDesc()
{
    reverse();
    ranking();
    reverse();
}

void doIt()
{
    l.clean();
    int n;
    cin >> n;
    while (n--)
    {
        string op;
        string name;
        string name2;
        int points;
        cin >> op;
        if (op == "ADD")
        {
            cin >> name >> points;
            add(name, points);
        }
        else if (op == "DISQ")
        {
            cin >> name;
            disq(name);
        }
        else if (op == "FIND")
        {
            cin >> name;
            find(name);
        }
        else if (op == "CORRECT")
        {
            cin >> name >> points;
            correct(name, points);
        }
        else if (op == "CHANGE")
        {
            cin >> name >> name2;
            change(name, name2);
        }
        else if (op == "PRINT")
        {
            print();
        }
        else if (op == "PRINT_DESC")
        {
            printDesc();
        }
        else if (op == "REVERSE")
        {
            reverse();
        }
        else if (op == "CLEAN")
        {
            clean();
        }
        else if (op == "RANKING")
        {
            ranking();
        }
        else if (op == "RANKING_DESC")
        {
            rankingDesc();
        }
        //l.print();
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
    return 0;
}
