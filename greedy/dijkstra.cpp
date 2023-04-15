/*
问题：单源最短路径，求图中节点s到其他所有节点的最短路径。
时间复杂度：O(E*logV)

把图中所有顶点分成两组，第一组：已求完最短路径的顶点，第二组：未求完最短路径的顶点，按最短路径长度递增的顺序逐个把第二组的顶点加到第一组。

实现：
未完成最短路径计算的顶点存在优先级队列中，每次可以快速从队列中选取最短路径的节点，重复执行以下操作指导队列为空：
1）从优先级队列中选取最近的节点
2）更新优先级队列中的节点的距离
*/

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int solve_dijkstra(vector<vector<pair<int, int>>> &graph, int s, int t) {
    // graph是图的邻接表，s是源点，求s到t的最短路径
    const int inf = numeric_limits<int>::max();

    // 数据结构：一个数组和一个优先级队列
    int n = graph.size();
    vector<int> dist(n, inf);
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;

    // 初始化每个节点到源点的距离，s为0，其他为无穷
    dist[s] = 0;
    // 每个节点以d[v]为权重放入优先级队列中（权重为无穷的节点可以先不插入）
    pq.push(make_pair(0, s));

    while (!pq.empty()) {
        // delete-min from priority queue
        auto [d, u] = pq.top();
        pq.pop();
        // 不支持decrease-key操作，这里需要特殊判断一下
        if (dist[u] < d) {
            continue;
        }
        for (int i = 0; i < graph[u].size(); i++) {
            auto [v, l] = graph[u][i];
            // decrease-key of v in priority queue
            if (dist[v] > dist[u] + l) {
                // 不支持decrease-key操作，没关系，直接插入，弹出的时候需要特殊判断一下
                pq.push(make_pair(dist[u] + l, v));
                dist[v] = dist[u] + l;
            }
        }
    }
    return dist[t];
}
