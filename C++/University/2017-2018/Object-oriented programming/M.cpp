#ifndef EHHHHH
#define EHHHHH


#include <queue>
#include <set>
#include <functional>

using namespace std;

function<int(vector<int>::iterator, vector<int>::iterator)> make_bfs(function<pair<vector<int>::iterator, vector<int>::iterator>(int)> neigh, function<void(int)> f)
{
    auto bfs = [neigh, f](vector<int>::iterator first, vector<int>::iterator last) {
        queue<int> q;
        set<int> visited;
        for (; first != last; first++)
        {
            q.push(*first);
            visited.insert(*first);
        }
        int result = 0;
        while (!q.empty())
        {
            int w = q.front();
            q.pop();

            f(w);
            result++;

            pair<vector<int>::iterator, vector<int>::iterator> neighbours = neigh(w);
            for (; neighbours.first != neighbours.second; neighbours.first++)
            {
                int somsiad = *neighbours.first;
                if (visited.find(somsiad) == visited.end())
                {
                    visited.insert(somsiad);
                    q.push(somsiad);
                }
            }
        }
        return result;
    };
    return bfs;
}

#endif