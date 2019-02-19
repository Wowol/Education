#include <iostream>
#include <queue>
#include <algorithm>
#define MAX 5005

using namespace std;

struct Shop
{
    int timeOpen;
    int timeClose;
    int money;
};

struct
{
  public:
    bool operator()(const Shop &a, const Shop &b)
    {
        return a.timeOpen < b.timeOpen;
    }
} CompareOpen;

struct
{
  public:
    bool operator()(const Shop &a, const Shop &b)
    {
        return a.money > b.money;
    }
} CompareMoney;

vector<Shop> takenShops;
Shop tab[MAX];
int n;

bool canTake(Shop &newShop)
{
    vector<Shop> shops(takenShops);
    shops.push_back(newShop);
    sort(shops.begin(), shops.end(), CompareOpen);

    priority_queue<int, vector<int>, std::greater<int>> q;

    int currentIndex = 0;
    int currentTime = shops[0].timeOpen;
    int qa = shops.size();

    while (currentIndex < shops.size())
    {
        currentTime = max(shops[currentIndex].timeOpen, currentTime);
        for (; currentIndex < shops.size() && shops[currentIndex].timeOpen <= currentTime; currentIndex++)
        {
            q.push(shops[currentIndex].timeClose);
        }

        while (!q.empty())
        {
            int top = q.top();
            q.pop();
            if (top <= currentTime)
            {
                return false;
            }
            currentTime++;
            for (; currentIndex < shops.size() && shops[currentIndex].timeOpen <= currentTime; currentIndex++)
            {
                q.push(shops[currentIndex].timeClose);
            }
        }
    }

    return true;
}

void doIt()
{
    takenShops.clear();
    cin >> n;
    for (int x = 0; x < n; x++)
    {
        cin >> tab[x].timeOpen >> tab[x].timeClose >> tab[x].money;
    }
    sort(tab, tab + n, CompareMoney); // descending

    unsigned long long takenMoney = 0;
    for (int x = 0; x < n; x++)
    {
        if (canTake(tab[x]))
        {
            takenMoney += tab[x].money;
            takenShops.push_back(tab[x]);
        }
    }
    cout << takenMoney << endl;
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