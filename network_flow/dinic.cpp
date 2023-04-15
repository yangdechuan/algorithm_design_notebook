/*
网络流dinic模板，拷贝自：http://algorithm.openjudge.cn/2021prefinaltest/G/
未修改代码，只是增加了一些注释；

Dinic算法是一种解决最大流问题的算法，其核心思想是通过不断地增广路径来寻找最大流。以下是Dinic算法的流程：
1.构建初始残量网络：将原始图中每条边的初始流量设置为该边的容量，构建残量网络。
2.构建分层图：在残量网络上运行BFS算法，将所有可达源点的节点按照距离源点的距离分层，得到分层图。
3.寻找增广路径：从源点开始在分层图上进行DFS或BFS搜索，只搜索同一层或下一层的节点，并且只在残量网络中容量大于0的边上进行搜索。如果找到一条增广路径，就记录该路径上的最小容量。
4.更新残量网络：根据增广路径上的最小容量，更新残量网络中的边权值。对于增广路径上的每条正向边，其流量加上最小容量；对于增广路径上的每条反向边，其流量减去最小容量。
5.重复步骤2-4，直到不能再找到增广路径为止。此时，残量网络中的所有增广路径都已经被找到，最大流也被求出。
（以上来自ChatGPT回答）
*/

/*
 * Dinic algo for max flow
 *
 * This implementation assumes that #nodes, #edges, and capacity on each edge <=
 * INT_MAX, which means INT_MAX is the best approximation of INF on edge
 * capacity. The total amount of max flow computed can be up to LLONG_MAX (not
 * defined in this file), but each 'dfs' call in 'dinic' can return <= INT_MAX
 * flow value.
 */
#include <algorithm>
#include <assert.h>
#include <limits.h>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#define N (100 + 2)
#define M (N * N + 4 * N)

typedef long long LL;

using namespace std;

// 边 u->v 的容量是 cap，u的下一条边在数组 e 的 index 是 next
struct edge {
    int v, cap, next;
};
edge e[M];

// head[u] 表示结点 u 的第一条出边的 index
int head[N];
// cur 是 head 的拷贝
int cur[N];
// 层次图，level[i] 表示 结点 i 的层次，level[s] = 0
int level[N];
// 边的个数
int num_of_edges;

// 初始化
void dinic_init(void) {
    num_of_edges = 0;
    memset(head, -1, sizeof(head));
    return;
}

// 用于构造残差图 u->v c1, v->u c2
int add_edge(int u, int v, int c1, int c2) {
    int &i = num_of_edges;

    assert(c1 >= 0 && c2 >= 0 &&
           c1 + c2 >= 0); // check for possibility of overflow
    e[i].v = v;
    e[i].cap = c1;
    e[i].next = head[u];
    head[u] = i++;

    e[i].v = u;
    e[i].cap = c2;
    e[i].next = head[v];
    head[v] = i++;
    return i;
}

// 打印残差图结构，用于debug
void print_graph(int n) {
    for (int u = 0; u < n; u++) {
        printf("%d: ", u);
        for (int i = head[u]; i >= 0; i = e[i].next) {
            printf("%d(%d)", e[i].v, e[i].cap);
        }
        printf("\n");
    }
    return;
}

// 找到所有的增广路径，并更新残差网络，时间复杂度 O(VE)
int dfs(int u, int t, int bn) {
    if (u == t)
        return bn;
    int left = bn;
    for (int &i = cur[u]; i >= 0; i = e[i].next) {
        int v = e[i].v;
        int c = e[i].cap;
        if (c > 0 && level[u] + 1 == level[v]) {
            int flow = dfs(v, t, min(left, c));
            if (flow > 0) {
                e[i].cap -= flow;
                e[i ^ 1].cap += flow;
                cur[u] = i;
                left -= flow;
                if (!left)
                    break;
            }
        }
    }
    if (left > 0)
        level[u] = 0;
    return bn - left;
}

// 构建层次图，时间复杂度 O(E)
bool bfs(int s, int t) {
    memset(level, 0, sizeof(level));
    level[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == t)
            return true;
        for (int i = head[u]; i >= 0; i = e[i].next) {
            int v = e[i].v;
            if (!level[v] && e[i].cap > 0) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return false;
}

// 最大流算法：dinic算法，s是源点，t是汇点，max_flow 是从 s 到 t 的最大流
LL dinic(int s, int t) {
    LL max_flow = 0;

    // 重复执行下列操作，直到不能找到增广路径为止（最多O(V)次，因为每次增广后，都会增加增广路径的长度）
    // bfs：构建层次图，时间复杂度 O(E)
    // dfs：找到所有的增广路径，并更新残差网络，时间复杂度 O(VE)
    // 因此 dinic 算法时间复杂度是 O(E*V^2)
    while (bfs(s, t)) {
        memcpy(cur, head, sizeof(head));
        max_flow += dfs(s, t, INT_MAX);
    }
    return max_flow;
}
