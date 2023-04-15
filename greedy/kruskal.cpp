/*
问题：最小生成树
适用于边稀疏图，M表示边数，N表示节点数，时间复杂度：O(E*logV)

按照边权值从小到大顺序查看一遍，如果不产生环（重边也算环），就把当前这条边加入到生成树中。
*/

#include <iostream>
#include <vector>

using namespace std;

// 并查集用于快速判断两个节点是否连通
class UnionFind {
  public:
    UnionFind(int n) {
        this->n = n;
        father.resize(n);
        for (int i = 0; i < n; i++) {
            father[i] = i; // 初始化每个元素的父节点为它自己
        }
    }
    int find(int x) {
        if (x == father[x]) {
            return x;
        } else {
            father[x] = find(father[x]);
            return father[x];
        }
    }
    bool connected(int x, int y) { return find(x) == find(y); }
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        father[rootX] = rootY;
    }

  private:
    int n;              // 元素个数
    vector<int> father; // 父节点数组
};

// 定义边数据结构
struct edge {
    int from, to;
    int cost;
};

// 边可以比较
bool cmp(edge x, edge y) { return x.cost < y.cost; }

// 也可以重载运算符<
// bool operator<(edge x, edge y) {
//     return x.cost < y.cost;
// }

int solve_kruskal(vector<edge> &edges, int n) {
    UnionFind uf(n);
    sort(edges.begin(), edges.end(), cmp);
    int ans = 0;
    for (int i = 0; i < edges.size(); i++) {
        int from = edges[i].from;
        int to = edges[i].to;
        int cost = edges[i].cost;
        if (!uf.connected(from, to)) {
            ans += cost;
            uf.unite(from, to);
        }
    }
    return ans;
}
