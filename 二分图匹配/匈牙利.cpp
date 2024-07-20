#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
#define Max 1002
#define INF 999999

vector<int> G[Max];  // 图的邻接表
bool used[Max];      // DFS标记数组
int match[Max];      // 匹配记录数组
int V;               // 节点数

void add_adge(int from, int to) {  // 向图中填加一条边
    G[from].push_back(to);
    G[to].push_back(from);
}

// DFS搜索增广路
bool DFS(int v) {  // v:当前点
    used[v] = true;
    for (int i = 0; i < G[v].size(); i++) {
        int u = G[v][i];   // v的邻接点u
        int w = match[u];  // u已经的匹配点
        // w<0:说明u,没有被匹配，那么直接将v->u进行匹配
        // w>0:说明u,已经有了被匹配，那么我们尝试拆去u->w的匹配，
        // 并为w重新找一个匹配(DFS(w)),若能找到,就就将v->u进行匹配
        if (w < 0 || (used[w] && DFS(w))) {
            match[v] = u;
            match[u] = v;
            return true;
        }
    }
    return false;
}

int Mactching() {
    int res = 0;
    memset(match, -1, sizeof(match));
    for (int i = 0; i < V; i++) {  // 每个节点遍历一遍
        if (match[i] < 0) {
            memset(used, 0, sizeof(used));
            if (DFS(i))
                res++;
        }
    }
    return res;
}
