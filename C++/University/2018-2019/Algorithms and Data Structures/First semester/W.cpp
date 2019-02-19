#include <iostream>
#include <queue>
#include <set>
#include <unordered_set>

using namespace std;

int maxes[4];

int n;

struct Scheme {
    int minutes;
    int water[4];

    friend bool operator<(const Scheme& first, const Scheme& other) {
        return first.minutes > other.minutes;
    }

    bool operator()(const Scheme& me, const Scheme& other) const {
        return me.water[1] == other.water[1] && me.water[2] == other.water[2] && me.water[3] == other.water[3];
    }

    size_t operator()(const Scheme& me) const {
        return std::hash<int>()((me.water[1]) ^ std::hash<int>()((me.water[2]) ^ std::hash<int>()(me.water[3])));
    }
};

unordered_set<Scheme, Scheme, Scheme> used;

bool create_scheme(Scheme& new_scheme, Scheme& last, int from, int to) {
    int unused = 6 - (from + to);
    if (last.water[to] < maxes[to] && last.water[from] > 0) {
        if (maxes[to] - last.water[to] < last.water[from]) {  // full second
            new_scheme.minutes = last.minutes + maxes[to] - last.water[to];
            new_scheme.water[from] = last.water[from] - (maxes[to] - last.water[to]);
            new_scheme.water[to] = maxes[to];
        } else {  // empty first
            new_scheme.water[from] = 0;
            new_scheme.water[to] = last.water[to] + last.water[from];
            new_scheme.minutes = last.minutes + last.water[from];
        }
        new_scheme.water[unused] = last.water[unused];
        return true;
    }
    return false;
}

void doIt() {
    cin >> maxes[1] >> maxes[2] >> maxes[3] >> n;
    int sum = maxes[1];

    Scheme first;
    first.minutes = 0;
    first.water[1] = sum;
    first.water[2] = 0;
    first.water[3] = 0;

    priority_queue<Scheme> q;
    q.push(first);

    while (!q.empty()) {
        Scheme last = q.top();
        q.pop();
        if (used.find(last) != used.end()) {
            continue;
        }
        used.insert(last);

        if (last.water[1] == n || last.water[2] == n || last.water[3] == n) {
            cout << last.minutes << endl;
            return;
        }

        Scheme new_scheme;
        if (create_scheme(new_scheme, last, 1, 2)) {
            q.push(new_scheme);
        }

        if (create_scheme(new_scheme, last, 1, 3)) {
            q.push(new_scheme);
        }

        if (create_scheme(new_scheme, last, 2, 1)) {
            q.push(new_scheme);
        }

        if (create_scheme(new_scheme, last, 2, 3)) {
            q.push(new_scheme);
        }

        if (create_scheme(new_scheme, last, 3, 1)) {
            q.push(new_scheme);
        }

        if (create_scheme(new_scheme, last, 3, 2)) {
            q.push(new_scheme);
        }
    }
    cout << "NIE" << endl;
}

int main() {
    int z;
    cin >> z;
    while (z--) {
        doIt();
        used.clear();
    }
}

// if (last.water[to] < maxes[to] && last.water[from] > 0) {  // first to second
//         if (maxes[to] - last.water[to] < last.water[from]) {   // full second
//             new_scheme.minutes = last.minutes + maxes[to] - last.water[to];
//             new_scheme.water[from] = last.water[from] - (maxes[to] - last.water[to]);
//             new_scheme.water[to] = maxes[to];
//         } else {  // empty first
//             new_scheme.water[from] = 0;
//             new_scheme.water[to] = last.water[to] + last.water[from];
//             new_scheme.minutes = last.minutes + last.water[from];
//         }
//         new_scheme.water[3] = last.water[3];
//         q.push(new_scheme);
//     }