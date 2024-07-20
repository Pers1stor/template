#include <bits/stdc++.h>

using namespace std;
#define Max 1002
#define INF 999999

struct edge  // 边集结构体
{
    int to;   // 弧尾下标
    int cap;  // 边的权值
    int rev;  // 对应反向边的下标
};

vector<edge> G[Max];  // 图的邻接表
bool used[Max];
// 向图中填加一条边及其反向边
void add_adge(int from, int to, int cap) {
    G[from].push_back((edge){to, cap, G[to].size()});
    G[to].push_back((edge){from, 0, G[from].size() - 1});
}

// DFS搜索可以增流的路径
int DFS(int v, int t, int f) {  // v:当前点;t:汇点;f:路径能增加的最大流量
    if (v == t)
        return f;
    used[v] = true;
    for (int i = 0; i < G[v].size(); i++) {
        edge& e = G[v][i];
        if (!used[e.to] && e.cap > 0) {
            int d = DFS(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;  // 每次DFS只更新一条路径
            }
        }
    }
    return 0;
}

int main() {
    int N, M;  // 节点数和边数
    cin >> N >> M;
    int from, to, cap;
    for (int i = 0; i < M; i++) {
        cin >> from >> to >> cap;
        add_adge(from, to, cap);
    }
    int s, t;
    cin >> s >> t;
    int flow = 0;
    while (true) {
        memset(used, 0, sizeof(used));
        int f = DFS(s, t, INF);
        if (f == 0)
            break;
        flow += f;
    }
    cout << "最大流量为：" << flow << endl;
    return 0;
}
/*
测试样例：
5 7
0 1 10
0 2 2
1 2 6
1 3 6
2 4 5
3 2 3
3 4 8
0 4
输出结果：
最大流量为：11
*/