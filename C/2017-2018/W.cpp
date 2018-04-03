#include <iostream>
#include <map>
#include <cstring>
#include <algorithm>
#include <math.h>

using namespace std;

template <typename T>
class stack
{
  private:
    long long size;
    T *tab;
    long long index;

  public:
    stack(long long size = 15)
    {
        this->size = size;
        tab = new T[size];
        index = -1;
    }

    void push(T &x)
    {
        if (full())
        {
            return;
        }
        tab[++index] = x;
    }

    T top()
    {
        if (empty())
        {
            return 0;
        }
        return tab[index];
    }

    T pop()
    {
        if (empty())
        {
            return 0;
        }
        return tab[index--];
    }

    bool empty()
    {
        return (index == -1);
    }

    bool full()
    {
        return (index == size - 1);
    }

    void clear()
    {
        index = -1;
    }

    void resize(long long n)
    {
        if (n < size)
        {
            return;
        }

        T *newTab = new T[n];
        std::memcpy(newTab, tab, size * sizeof(T));

        size = n;
        delete[] tab;
        tab = newTab;
    }

    ~stack()
    {
        delete[] tab;
    }
};


map<char, long long> priority;
long long value[200]; // = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 3, 4};

string convertToONP(string p)
{
    string out;
    out.clear();

    stack<char> s(p.size() + 10);
    s.clear();

    for (char &c : p)
    {
        if (isalpha(c))
        {
            out += c;
            continue;
        }

        if (c == '(')
        {
            s.push(c);
            continue;
        }

        if (c == ')')
        {
            while (s.top() != '(')
            {
                out += s.pop();
            }
            s.pop();
            continue;
        }

        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        {
            if (s.empty() || priority[c] > priority[s.top()])
            {
                s.push(c);
            }
            else
            {
                while (priority[c] <= priority[s.top()])
                {
                    out += s.pop();
                }

                s.push(c);
            }
        }
    }

    while (!s.empty())
    {
        out += s.pop();
    }

    return out;
}

long long f(long long a, long long b, char op)
{
    switch (op)
    {
    case '*':
        return a * b;
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '/':
        return b != 0 ? a / b : 0;
    case '^':
        return b > 0 ? pow(a, b) : 1;
    case '%':
        return a % b;
    default:
        return a + b;
    }
}

long long calculateONP(string p)
{
    stack<long long> s(p.size() + 10);
    s.clear();
    for (char &c : p)
    {
        if (isalpha(c))
        {
            s.push(value[c]);
            continue;
        }
        else
        {
            long long first = s.pop();
            long long second = s.pop();
            long long result = f(second, first, c);
            s.push(result);
        }
    }

    return s.pop();
}

void doIt()
{
    for (long long x = 'a'; x <= 'z'; x++)
    {
        cin >> value[x];
    }
    long long n;
    cin >> n;
    while (n--)
    {
        string p;
        cin >> p;
        string onp = convertToONP(p);
        cout << onp << endl;
        long long result = calculateONP(onp);
        cout << result << endl;
    }
}

int main()
{
    priority.clear();
    priority['('] = 0;
    priority['+'] = priority['-'] = priority[')'] = 1;
    priority['*'] = priority['/'] = priority['%'] = 2;
    priority['^'] = 3;

    long long z;
    cin >> z;
    while (z--)
    {
        doIt();
    }
}
