/*
问题：单源最短路径，求图中节点s到其他所有节点的最短路径。
时间复杂度 O(V*E)

朴素方法：
dp(i, v) 表示从s到v最多经过 i 条边的最短路径长度
dp(i, v) = min(dp(i - 1, v), min(dp(i, u) + luv))

优化方法：
dp[v] 表示目前为止，s到v的最短路径长度
dp[v] = min(dp[v], dp[u] + luv)
*/

#include <vector>

using namespace std;

const int inf = numeric_limits<int>::max();

struct edge {
    int from, to, cost;
};

// 空间复杂度：O(n^2)
int solve_bellman_ford_naive(vector<edge> &edges, int n, int s, int t) {
    vector<vector<int>> dp(n, vector(n, inf));
    dp[0][s] = 0;

    // 从s到v最多经过 i 条边
    for (int i = 1; i <= n - 1; i++) {
        for (int v = 0; v < n; v++) {
            dp[i][v] = dp[i - 1][v];
        }
        // 遍历每条边
        for (int j = 0; j < edges.size(); j++) {
            int u = edges[j].from;
            int v = edges[j].to;
            int cost = edges[j].cost;
            if (dp[i - 1][u] != inf && dp[i][v] > dp[i - 1][u] + cost) {
                dp[i][v] = dp[i - 1][u] + cost;
            }
        }
    }
    return dp[n - 1][t];
}

// 空间复杂度：O(n)
int solve_bellman_ford(vector<edge> &edges, int n, int s, int t) {
    vector<int> dp(n, inf);
    dp[s] = 0;

    // 最多 n-1 轮松弛
    for (int i = 1; i <= n - 1; i++) {
        bool updated = false;
        // 遍历每条边 uv（可以按任何顺序遍历边）
        for (int j = 0; j < edges.size(); j++) {
            int u = edges[j].from;
            int v = edges[j].to;
            int cost = edges[j].cost;
            if (dp[u] != inf && dp[v] > dp[u] + cost) {
                dp[v] = dp[u] + cost;
                updated = true;
            }
        }
        if (!updated) {
            break;
        }
    }
    // 判断负环
    // 需要注意，只有源点可达的负环才会被检测到。
    for (int j = 0; j < edges.size(); j++) {
        int u = edges[j].from;
        int v = edges[j].to;
        int cost = edges[j].cost;
        if (dp[u] != inf && dp[v] > dp[u] + cost) {
            // 存在负环
            return -1;
        }
    }
    return dp[t];
}