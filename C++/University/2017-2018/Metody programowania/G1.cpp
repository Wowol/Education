using namespace std;
#include <iostream>
#include <iomanip>

template <class T1, class T2>
class node
{
  public:
    T1 key;
    T2 value;

    node<T1, T2>(T1 k, T2 n)
    {
        key = k;
        value = n;
    }

    T2 getName()
    {
        return value;
    }

    friend ostream &operator<<(ostream &st, node<T1, T2> &a)
    {
        st << setfill('0') << setw(9) << a.key << " " << a.value << endl;
    }

    node<T1, T2> *left = nullptr;
    node<T1, T2> *right = nullptr;
    node<T1, T2> *parent = nullptr;
};

template <class T1, class T2>
class map
{
  public:
    node<T1, T2> *head;

    map()
    {
        head = nullptr;
    }

    T2 &operator[](T1 key)
    {
        node<T1, T2> *current = head;
        if (head == nullptr)
        {
            head = new node<T1, T2>(key, "");
            return head->value;
        }
        while (current != nullptr)
        {
            if (key == current->key)
            {
                return current->value;
            }
            else if (key > current->key)
            {
                if (current->right == nullptr)
                {
                    current->right = new node<T1, T2>(key, "");
                    current->right->parent = current;
                    return current->right->value;
                }
                current = current->right;
            }
            else
            {
                if (current->left == nullptr)
                {
                    current->left = new node<T1, T2>(key, "");
                    current->left->parent = current;
                    return current->left->value;
                }
                current = current->left;
            }
        }
    }

    node<T1, T2> *find(T1 key)
    {
        node<T1, T2> *current = head;
        while (current != nullptr)
        {
            if (key == current->key)
            {
                return current;
            }
            else if (key > current->key)
            {
                current = current->right;
            }
            else
            {
                current = current->left;
            }
        }
        return nullptr;
    }

    bool delet(T1 key)
    {
        node<T1, T2> *current = head;
        while (current != nullptr)
        {
            if (key == current->key)
            {
                break;
            }
            else if (key > current->key)
            {
                current = current->right;
            }
            else
            {
                current = current->left;
            }
        }
        if (current == nullptr)
            return false;

        if (current->left == nullptr || current->right == nullptr)
        {
            if (current->parent == nullptr) // usuwamy korzen
            {
                if (current->left != nullptr)
                {
                    node<T1, T2> *temp = head->left;
                    delete head;
                    head = temp;
                }
                else if (current->right != nullptr)
                {
                    node<T1, T2> *temp = head->right;
                    delete head;
                    head = temp;
                }
                else
                {
                    delete head;
                    head = nullptr;
                    return true;
                }
                head->parent = nullptr;
                return true;
            }
            else if (current == current->parent->left)
            {
                if (current->left != nullptr)
                {
                    current->parent->left = current->left;
                    current->left->parent = current->parent;
                }
                else
                {
                    current->parent->left = current->right;
                    if (current->right != nullptr)
                    {
                        current->right->parent = current->parent;
                    }
                }
            }
            else if (current == current->parent->right)
            {
                if (current->left != nullptr)
                {
                    current->parent->right = current->left;
                    current->left->parent = current->parent;
                }
                else
                {
                    current->parent->right = current->right;
                    if (current->right != nullptr)
                    {
                        current->right->parent = current->parent;
                    }
                }
            }

            delete current;
            return true;
        }
        else
        {
            node<T1, T2> *child = current->right;
            while (child->left != nullptr)
            {
                child = child->left;
            }

            T1 tempKey = child->key;
            T2 tempValue = child->value;

            // if (child == current->right)
            // {
            //     current->right = nullptr;
            // }

            delet(child->key);
            current->key = tempKey;
            current->value = tempValue;
            return true;
        }
    }

    void print()
    {
        if (head == nullptr)
        {
            cout << "EMPTY" << endl;
        }
        else
        {
            print(head);
        }
    }

    void print(node<T1, T2> *n)
    {
        if (n == nullptr)
            return;
        print(n->left);

        cout << *n;
        print(n->right);
    }

    void clean()
    {
        clean(head);
        head = nullptr;
    }

    void clean(node<T1, T2> *n)
    {
        if (n == nullptr)
            return;
        clean(n->left);
        clean(n->right);
        delete n;
    }
};