#include <iostream>
//#include "list.cpp"
#include <map>
#include <vector>

using namespace std;

template <class T>
class Node
{
  public:
    Node *t[2] = {nullptr, nullptr};

    T name;

    Node *nextDiffrentThen(Node *diff)
    {
        return t[intNextDiffrentThen(diff)];
    }

    int intNextDiffrentThen(Node *diff)
    {
        if (t[0] == diff)
        {
            return 1;
        }
        else
            return 0;
    }
};

template <typename T>
class DoubleList
{

  public:
    string listName;
    
    T *ends[2];
    bool currentEnd = 1;
    DoubleList(string listName)
    {
        this->listName = listName;
        ends[0] = new T;
        ends[0]->name = "";
        ends[1] = new T;
        ends[1]->name = "";
        clean();
    }

    void addFirst(T *n)
    {
        T *end = ends[!currentEnd];

        T *temp = end->nextDiffrentThen(nullptr);
        int p = end->intNextDiffrentThen(nullptr);
        n->t[p] = temp;

        int q = !temp->intNextDiffrentThen(end);
        temp->t[q] = n;
        n->t[q] = end;
        end->t[p] = n;
    }

    void addFirst(string name)
    {
        T *n = new T();
        n->name = name;
        addFirst(n);
    }

    void addLast(string name)
    {
        reverse();
        addFirst(name);
        reverse();
    }

    void addLast(T *n)
    {
        reverse();
        addFirst(n);
        reverse();
    }

    T *detachFront()
    {
        if (isEmpty())
        {
            return NULL;
        }
        T *end = ends[!currentEnd];
        T *temp = end->nextDiffrentThen(nullptr);

        T *next = temp->nextDiffrentThen(end);
        end->t[end->intNextDiffrentThen(nullptr)] = next;
        next->t[!next->intNextDiffrentThen(temp)] = ends[!currentEnd];
        temp->t[0] = nullptr;
        temp->t[1] = nullptr;
        return temp;
    }

    T *detachLast()
    {
        reverse();
        T *ret = detachFront();
        reverse();
        return ret;
    }

    bool isEmpty()
    {
        return ends[!currentEnd]->nextDiffrentThen(nullptr) == ends[currentEnd];
    }

    void unionn(DoubleList &l)
    {
        if (l.currentEnd == currentEnd)
        {
            T *end = ends[currentEnd];
            T *poprzednik = end->nextDiffrentThen(nullptr);

            T *end2 = l.ends[!l.currentEnd];
            T *first = end2->nextDiffrentThen(nullptr);

            poprzednik->t[!poprzednik->intNextDiffrentThen(end)] = first;
            first->t[!first->intNextDiffrentThen(end2)] = poprzednik;
            delete ends[currentEnd];
            delete l.ends[!l.currentEnd];
            ends[currentEnd] = l.ends[l.currentEnd];
        }
        else
        {
            T *end = ends[currentEnd];
            T *first = end->nextDiffrentThen(nullptr);

            T *end2 = l.ends[!l.currentEnd];
            T *first2 = end2->nextDiffrentThen(nullptr);

            first->t[!first->intNextDiffrentThen(end)] = first2;
            first2->t[!first2->intNextDiffrentThen(end2)] = first;
            delete ends[currentEnd];
            delete l.ends[!l.currentEnd];
            ends[currentEnd] = l.ends[l.currentEnd];
        }
    }

    void reverse()
    {
        currentEnd = !currentEnd;
    }

    void clean()
    {
        ends[0]->t[0] = nullptr;
        ends[0]->t[1] = ends[1];
        ends[1]->t[0] = ends[0];
        ends[1]->t[1] = nullptr;
        currentEnd = 1;
    }

    void print()
    {
        cout << "\"" << listName << "\":" << endl;
        T *skad = ends[!currentEnd];
        for (T *x = ends[!currentEnd]->nextDiffrentThen(nullptr);
             x != ends[currentEnd];)
        {
            cout << x->name;
            T *q;
            q = x->nextDiffrentThen(skad);
            skad = x;
            x = q;

            if (x != ends[currentEnd])
            {
                cout << "<-";
            }
        }
        cout << endl;
    }

    void removeAll()
    {
        T *skad = ends[!currentEnd];
        for (T *x = ends[!currentEnd]->nextDiffrentThen(nullptr);
             x != ends[currentEnd];)
        {
            T *q;
            q = x->nextDiffrentThen(skad);
            if (skad != ends[!currentEnd])
            {
                delete skad;
            }
            skad = x;
            x = q;
        }
        delete skad;
        delete ends[0];
        delete ends[1];
    }
};

void test()
{
    DoubleList<Node<string>> list1("list1");
    DoubleList<Node<string>> list2("list2");
    DoubleList<Node<string>> list3("list3");

    list1.addFirst("3");
    list1.addFirst("2");
    list1.addFirst("1");
    list1.addLast("4");
    list1.addLast("5");
    list1.print();
    list1.reverse();
    list1.print();

    Node<string> *p = list1.detachFront();
    list1.print();

    Node<string> *q = list1.detachLast();
    list1.print();

    list2.addFirst(p);
    list2.addLast(q);
    list2.print();
    list2.unionn(list1);
    list2.print();

    list3.addFirst("a");
    list3.addLast("b");
    list3.addFirst("c");
    list3.reverse();
    list3.print();
    list2.print();
    list2.unionn(list3);
    list2.print();
}

map<string, DoubleList<Node<string>> *> m;    


void doIt()
{
    m.clear();
    int n;
    cin >> n;
    string op;
    string name;
    string person;

    while (n--)
    {
        cin >> op;
        cin >> name;

        if (op == "NEW")
        {
            cin >> person;
            DoubleList<Node<string>> *d = new DoubleList<Node<string>>(name);
            m[name] = d;
            m[name]->addFirst(person);
        }
        else if (op == "BACK")
        {
            cin >> person;
            m[name]->addLast(person);
        }
        else if (op == "FRONT")
        {
            cin >> person;
            m[name]->addFirst(person);
        }
        else if (op == "PRINT")
        {
            m[name]->print();
        }
        else if (op == "REVERSE")
        {
            m[name]->reverse();
        }
        else if (op == "UNION")
        {
            string train2;
            cin >> train2;
            m[name]->unionn(*m[train2]);
            delete m[train2];
            m.erase(train2);
        }
        else if (op == "DELFRONT")
        {
            string train2;
            cin >> train2;
            Node<string> *p = m[train2]->detachFront();
            DoubleList<Node<string>> *d;
            if (m[train2]->isEmpty())
            {
                d = m[train2];
                m.erase(train2);
                d->clean();                
                d->listName = name;
                m[name] = d;
            }
            else
            {
                d = new DoubleList<Node<string>>(name);
                m[name] = d;
            }
            m[name]->addFirst(p);               
        }
        else if (op == "DELBACK")
        {
            string train2;
            cin >> train2;
            Node<string> *p = m[name]->detachLast();
            DoubleList<Node<string>> *d;
            if (m[name]->isEmpty())
            {
                d = m[name];
                m.erase(name);
                d->clean();                
                d->listName = train2;
                m[train2] = d;
            }
            else
            {
                d = new DoubleList<Node<string>>(train2);
                m[train2] = d;
            }
            m[train2]->addFirst(p);  
        }
    }

    for (auto const &x : m)
    {
        if (x.second != nullptr)
        {
            x.second->removeAll();
        }
        delete x.second;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    int z;
    cin >> z;
    while (z--)
    {
        doIt();
    }
}