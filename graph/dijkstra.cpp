#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;
const int INF = 1E9;

struct Dijkstra {
    int n;                  // 点的数量
    vector<vector<pii>> g;  // 邻接表存储所有边 [下条边，权重]
    vector<int> dist;       // 存储所有点到x号点的距离
    Dijkstra(int n_) : n(n_), g(n_), dist(n_, INF) {}
    Dijkstra(int n_, vector<vector<int>> edges) : n(n_), g(n_), dist(n_, INF) {
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }
    }
    void addEdge(vector<int> e) {
        addEdge(e[0], e[1], e[2]);
    }
    void addEdge(int u, int v, int w) {
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    // 求x号点到n号点的最短距离，如果不存在，则返回-1
    int shortestPath(int x) {
        dist[x] = 0;
        priority_queue<pii, vector<pii>, greater<pii>> heap; // first存储距离，second存储节点编号
        heap.push({0, x});  

        while (!heap.empty()) {
            auto [d, u] = heap.top();
            heap.pop();
            if (d > dist[u]) continue;
            for (auto [v, w] : g[u]) {
                int new_dis = d + w;
                if (dist[v] > new_dis) {
                    dist[v] = new_dis;
                    heap.emplace(new_dis, v);
                }
            }
        }

        if (dist[n] == INF)
            return -1;
        return dist[n];
    }
};
