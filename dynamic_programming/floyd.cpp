/*
问题：图中任意两点的最短路径。
时间复杂度 O(V^3)

dp[k][i][j]表示节点i到节点j最多经过0-k之间的节点的最短路径
dp[k][i][j] = min(dp[k-1][i][j], dp[k-1][i][k] + dp[k-1][k][j])
*/

#include <vector>

using namespace std;

const int inf = numeric_limits<int>::max();

int solve_floyd(vector<vector<int>> &graph) {
    // graph 是图的邻接矩阵
    int n = graph.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<vector<int>> path(n, vector<int>(n, -1));
    // 初始化
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = graph[i][j];
            if (graph[i][j] < inf) {
                path[i][j] = i;
            } else {
                path[i][j] = -1;
            }
        }
    }
    // 图中任意两点ij的最短路径
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dp[i][k] + dp[k][j] < dp[i][j]) {
                    dp[i][j] = dp[i][k] + dp[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
}