#include <iostream>
using namespace std;

class polynomial
{
    struct mono
    {
        int power;
        long long int factor;
        mono *previous;
        mono *next;
    };

    mono *head;
    mono *tail;

  public:
    polynomial()
    {
        head = new mono;
        tail = new mono;
        head->power = -1;
        head->factor = -1;
        head->next = tail;
        tail->power = -1;
        tail->factor = -1;
        tail->previous = head;
    }

    void remove(mono *m)
    {
        m->previous->next = m->next;
        m->next->previous = m->previous;
        delete m;
    }

    void clean()
    {
        while (head->next != tail)
        {
            mono *next = head->next->next;
            delete head->next;
            head->next = next;
        }
        head->next = tail;
        tail->previous = head;
    }

    void print()
    {
        for (mono *x = head->next; x != tail; x = x->next)
        {
            if (x == head->next && x->factor < 0)
            {
                cout << "-";
            }
            if (abs(x->factor) != 1)
            {
                cout << abs(x->factor);
            }

            if (x->power != 0)
            {
                cout << "x^" << x->power;
            }
            else
            {
                if (abs(x->factor) == 1)
                {
                    cout << 1;
                }
            }

            if (x->next != tail)
            {
                if (x->next->factor > 0)
                    cout << "+";
                else
                    cout << "-";
            }
        }
        cout << endl;
    }

    void cleanZeroes()
    {
        for (mono *x = head->next; x != tail; x = x->next)
        {
            if (x->factor == 0)
            {
                remove(x);
            }
        }
    }

    void multipleConst(long long int p)
    {
        if (p == 0)
        {
            clean();
            return;
        }
        for (mono *x = head; x != tail; x = x->next)
        {
            x->factor *= p;
        }
    }

    void multiple(polynomial &p)
    {
        polynomial *newPoly = new polynomial;
        for (mono *first = p.head->next; first != p.tail; first = first->next)
        {
            mono *previous = newPoly->head;
            for (mono *second = head->next; second != tail; second = second->next)
            {
                previous = newPoly->addMonomial(first->power + second->power, first->factor * second->factor, previous);
            }
        }
        clean();
        head->next = newPoly->head->next;
        head->next->previous = head;

        tail->previous = newPoly->tail->previous;
        tail->previous->next = tail;
        delete newPoly;
        cleanZeroes();
    }
    void add(polynomial &p)
    {
        mono *current = p.head->next;
        for (mono *x = head->next; x != tail; x = x->next)
        {
            if (current == p.tail)
            {
                return;
            }
            if (x->power == current->power)
            {
                x->factor += current->factor;
                current = current->next;
                if (x->factor == 0)
                {
                    remove(x);
                    x = x->previous;
                }
            }
            else if (x->power > current->power)
            {
                mono *newMono = new mono;
                newMono->factor = current->factor;
                newMono->power = current->power;

                x->previous->next = newMono;
                newMono->next = x;
                newMono->previous = x->previous;
                x->previous = newMono;

                current = current->next;

                x = x->previous;
            }
        }

        if (current != p.tail)
        {
            for (; current != p.tail; current = current->next)
            {
                mono *newMono = new mono;
                newMono->factor = current->factor;
                newMono->power = current->power;

                tail->previous->next = newMono;
                newMono->next = tail;
                newMono->previous = tail->previous;
                tail->previous = newMono;
            }
        }
    }

    void reversePrint()
    {
        for (mono *x = tail->previous; x != head; x = x->previous)
        {
            if (x == tail->previous && x->factor < 0)
            {
                cout << "-";
            }
            if (abs(x->factor) != 1)
            {
                cout << abs(x->factor);
            }

            if (x->power != 0)
            {
                cout << "x^" << x->power;
            }
            else
            {
                if (abs(x->factor) == 1)
                {
                    cout << 1;
                }
            }

            if (x->previous != head)
            {
                if (x->previous->factor > 0)
                    cout << "+";
                else
                    cout << "-";
            }
        }
        cout << endl;
    }

    bool empty()
    {
        return (head->next == tail);
    }

    long long int min()
    {
        return head->next->factor;
    }

    long long int max()
    {
        return tail->previous->factor;
    }

    void derative()
    {
        for (mono *x = head->next; x != tail; x = x->next)
        {
            if (x->power == 0)
            {
                remove(x);
            }
            else
            {
                x->factor *= x->power;
                x->power--;
            }
        }
    }

    mono *addMonomial(int power, long long int factor, mono *begin = nullptr)
    {
        if (begin == nullptr)
            begin = head;

        if (factor == 0)
            return nullptr;

        mono *newMono = new mono;
        newMono->power = power;
        newMono->factor = factor;

        mono *x;
        if (begin != tail)
        {
            x = begin->next;
        }
        else
        {
            x = begin;
        }

        while (x->power < power && x != tail)
        {
            x = x->next;
        }

        if (x->power == power)
        {
            delete newMono;
            x->factor += factor;
            if (x->factor == 0)
            {
                remove(x);
            }
            return x;
        }
        else
        {
            mono *before = x->previous;
            newMono->next = before->next;
            before->next = newMono;
            newMono->previous = before;
            newMono->next->previous = newMono;
        }

        return newMono;
    }
};

polynomial *ids[100];

void printAsc(char id)
{
    if (ids[id]->empty())
    {
        cout << "EMPTY" << endl;
    }
    else
    {
        ids[id]->print();
    }
}

void printDesc(char id)
{
    if (ids[id]->empty())
    {
        cout << "EMPTY" << endl;
    }
    else
    {
        ids[id]->reversePrint();
    }
}

void derivative(char id)
{
    ids[id]->derative();
}

void addMono(char id, long long int power, long long int factor)
{
    ids[id]->addMonomial(power, factor);
    cout << "ADD OK" << endl;
}

void add(char addTo, char id)
{
    ids[addTo]->add(*ids[id]);
    cout << "ADD OK" << endl;
}

void min(char id)
{
    if (ids[id]->empty())
    {
        cout << "ERROR" << endl;
    }
    else
    {
        cout << ids[id]->min() << endl;
    }
}

void max(char id)
{
    if (ids[id]->empty())
    {
        cout << "ERROR" << endl;
    }
    else
    {
        cout << ids[id]->max() << endl;
    }
}

void clean(char id)
{
    if (ids[id]->empty())
    {
        cout << "EMPTY" << endl;
    }
    else
    {
        ids[id]->clean();
        cout << "CLEAN OK" << endl;
    }
}

void multi(char id1, char id2)
{
    ids[id1]->multiple(*ids[id2]);
    cout << "MULTI OK" << endl;
}


void multipleConst(char id, long long int p)
{
    ids[id]->multipleConst(p);
    cout << "MULTI OK" << endl;
}


void doIt()
{
    long long int n;
    cin >> n;
    string op;
    char id;
    char id2;
    long long int factor;
    long long int power;
    long long int points;
    int c;

    for (long long int x = 'A'; x <= 'Z'; x++)
    {
        ids[x]->clean();
    }
    while (n--)
    {
        cin >> op;
        if (op == "PRINT_ASC")
        {
            cin >> id;
            printAsc(id);
        }
        else if (op == "PRINT_DESC")
        {
            cin >> id;
            printDesc(id);
        }
        else if (op == "DERIVATIVE")
        {
            cin >> id;
            derivative(id);
        }
        else if (op == "ADD_MONO")
        {
            cin >> id >> power >> factor;
            addMono(id, power, factor);
        }
        else if (op == "ADD")
        {
            cin >> id >> id2;
            add(id, id2);
        }
        else if (op == "MIN")
        {
            cin >> id;
            min(id);
        }
        else if (op == "MAX")
        {
            cin >> id;
            max(id);
        }
        else if (op == "CLEAN")
        {
            cin >> id;
            clean(id);
        }
        else if (op == "MULTI")
        {
            cin >> id >> id2;
            multi(id, id2);
        }
        else if (op == "MULTI_CONST")
        {
            cin >> id >> c;
            multipleConst(id, c);
        }
    }
}

int main()
{
    for (int x = 'A'; x <= 'Z'; x++)
    {
        ids[x] = new polynomial;
    }
    long long int z;
    cin >> z;
    while (z--)
    {
        doIt();
    }
}