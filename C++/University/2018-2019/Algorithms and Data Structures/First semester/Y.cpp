#include <algorithm>
#include <iostream>

#define MAX_EDGES 200005
#define MAX 100005

using namespace std;

struct edge {
    int from;
    int to;
    int weight;

    bool operator<(const edge& other) {
        return weight < other.weight;
    }

    int id;
};

edge edges[MAX_EDGES];
int parent[MAX];
bool can_be[MAX_EDGES];

int find(int w) {
    if (w == parent[w]) {
        return w;
    } else {
        parent[w] = find(parent[w]);
        return parent[w];
    }
}

void unionn(int w, int q) {
    int w_boss = find(w);
    int q_boss = find(q);
    if (w_boss != q_boss) {
        parent[w_boss] = q_boss;
    }
}

void doIt() {
    int n, m;
    cin >> n >> m;

    for (int x = 0; x < m; x++) {
        cin >> edges[x].from >> edges[x].to >> edges[x].weight;
        edges[x].id = x;
        can_be[x] = false;
    }

    for (int x = 1; x <= n; x++) {
        parent[x] = x;
    }

    sort(edges, edges + m);
    for (int x = 0; x < m; x++) {
        for (int y = x; y < m && (y == x || edges[y].weight == edges[y - 1].weight); y++) {
            if (find(edges[y].from) != find(edges[y].to)) {
                can_be[edges[y].id] = true;
            }
        }

        int y;
        for (y = x; y < m && (y == x || edges[y].weight == edges[y - 1].weight); y++) {
            if (find(edges[y].from) != find(edges[y].to)) {
                unionn(edges[y].from, edges[y].to);
            }
        }
        x = y;
        x--;
    }

    for (int x = 0; x < m; x++) {
        cout << (can_be[x] ? "TAK" : "NIE") << endl;
    }
}

int main() {
    int z;
    cin >> z;
    while (z--) {
        doIt();
    }
}