/*
问题：最小生成树
适用于边稠密图，事件复杂度O(V^2)

初始化只有一个顶点的树X，然后贪心地选取X和其他顶点之间相连的最小权值的边，并把它加到X中；不断这个操作，直到把所有顶点纳入X中，就得到最小生成树。

Prim算法主要有两种实现方式：基于堆的实现和基于数组的实现。
1. 基于堆的实现：Prim算法的基于堆的实现使用优先队列（Priority
Queue）来存储顶点和边的信息，并选择最小的边。优先队列可以使用二叉堆（Binary
Heap）或斐波那契堆（Fibonacci
Heap）等数据结构实现。在基于堆的实现中，算法的时间复杂度为O(E log V)。
2.
基于数组的实现：Prim算法的基于数组的实现使用两个数组来存储顶点和边的信息，并选择最小的边。其中，一个数组用于标记顶点是否已经加入最小生成树的顶点集合中，另一个数组用于存储每个顶点到最小生成树的最短距离。在基于数组的实现中，算法的时间复杂度为O(V^2)。
需要注意的是，基于堆的实现对于稠密图（即边数接近于V^2）的情况下，时间复杂度的常数较大；而基于数组的实现对于稀疏图（即边数接近于V）的情况下，时间复杂度可能会较高。因此，在实际应用中需要根据具体场景选择合适的实现方式。
*/
#include <climits>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// 基于数组的实现，图用邻接矩阵表示，O(V^2)
int solve_prim_with_matrix(vector<vector<int>> &graph, int n) {
    const int inf = numeric_limits<int>::max();
    int ans = 0;
    vector<int> mincost(n, inf);
    vector<int> vis(n, 0);
    vis[0] = 1;
    for (int i = 0; i < n; i++) {
        mincost[i] = graph[0][i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (vis[j] == 0 && (u == -1 || mincost[j] < mincost[u])) {
                u = j;
            }
        }
        ans += mincost[u];
        vis[u] = 1;
        for (int v = 0; v < n; v++) {
            if (vis[v] == 0) {
                mincost[v] = min(mincost[v], graph[u][v]);
            }
        }
    }
    return ans;
}

// 基于堆的实现，图用邻接表表示，O(E*logV)
int solve_prim_with_adjlist(vector<vector<pair<int, int>>> &graph, int n) {
    const int inf = numeric_limits<int>::max();
    vector<int> mincost(n, inf);
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;

    mincost[0] = 0;
    pq.push(make_pair(0, 0));

    int ans = 0;
    while (!pq.empty()) {
        int cur_cost = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (mincost[u] < cur_cost) {
            continue;
        }
        ans += cur_cost;
        for (int i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i].first;
            int new_cost = graph[u][i].second;
            if (new_cost < mincost[v]) {
                mincost[v] = new_cost;
                pq.push(make_pair(mincost[v], v));
            }
        }
    }
    return ans;
}
