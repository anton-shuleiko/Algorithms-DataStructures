#include <iostream>
#include <vector>

using namespace std;

vector<int> parent;
vector<int> power;

int find(int u) {
    if (u == parent[u]) return u;
    return parent[u] = find(parent[u]);
}

void unite(int u, int v) {
    u = find(u);
    v = find(v);
    if (u != v) {
        if (power[u] < power[v]) swap(u, v);
        parent[v] = u;
        power[u] += power[v];
    }
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    // initialization
    parent.resize(n + 1);
    power.resize(n + 1, 1);
    for (int i = 1; i <= n; ++i) parent[i] = i;

    // process edges
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        unite(u, v);
    }

    // process operations
    for (int i = 0; i < k; ++i) {
        string op;
        int u, v;
        cin >> op >> u >> v;
        if (op == "cut") {
            unite(u, v);
        } else {
            if (find(u) == find(v)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }

    return 0;
}