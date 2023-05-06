/*
线段树是用来维护区间的数据结构
线段树可以在O(logN)时间复杂度内实现单点修改、区间查询（区间求最值、区间求和）等操作

线段树是一个二叉树，树上每个结点维护一个区间（最值或区间和），根节点维护整个区间，每个节点维护的是父亲的区间二等分后的一个子区间；
建树时间复杂度：O(N)
查询和修改时间复杂度：O(logN)
*/
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> class SegTreeRangeMin {
  public:
    SegTreeRangeMin(vector<T> &vec) {
        INF = numeric_limits<T>::max();
        n = 1;
        // 为简单起见，把元素个数扩大到2的幂
        while (n < vec.size()) {
            n *= 2;
        }
        dat = vector<T>(2 * n - 1, INF);
        build(vec, 0, 0, n);
    }
    // 建树：对区间 [l, r) 创建线段树
    // 沿着根结点往下创建，k 是树结点的下标，[l, r) 为该结点对应的区间
    // k 的左儿子下标 2 * k + 1，对应区间 [l, (l + r) / 2)
    // k 的右儿子下标 2 * k + 2，对应区间 [(l + r) / 2, r)
    void build(vector<T> &vec, int k, int l, int r) {
        if (l + 1 == r) {
            dat[k] = vec[l];
        } else {
            build(vec, 2 * k + 1, l, (l + r) / 2);
            build(vec, 2 * k + 2, (l + r) / 2, r);
            dat[k] = min(dat[2 * k + 1], dat[2 * k + 2]);
        }
    }

    // 单点修改：把第 k 个元素更新为 x
    void update(int k, T x) {
        k += (n - 1);
        dat[k] = x;
        while (k > 0) {
            k = (k - 1) / 2;
            dat[k] = min(dat[2 * k + 1], dat[2 * k + 2]);
        }
    }

    // 区间查询：查询区间 [s, t) 的最小值
    // 沿着根结点往下查询，k 是树结点的下标，[l, r) 为该结点对应的区间
    int range_min(int s, int t) {
        assert(s >= 0 && t <= n && s < t);
        return dfs(s, t, 0, 0, n);
    }
    int dfs(int s, int t, int k, int l, int r) {
        if (s >= r || t <= l) {
            return INF;
        } else if (s <= l && t >= r) {
            return dat[k];
        } else {
            int v1 = dfs(s, t, 2 * k + 1, l, (l + r) / 2);
            int v2 = dfs(s, t, 2 * k + 2, (l + r) / 2, r);
            return min(v1, v2);
        }
    }

  private:
    T INF;
    vector<T> dat;
    int n;
};

void test() {
    vector<int> vec;
    srand(time(0));
    for (int i = 0; i < 100; i++) {
        int tmp = rand() % 100;
        vec.push_back(tmp);
    }

    SegTreeRangeMin<int> tree(vec);
    for (int l = 0; l < vec.size(); l++) {
        for (int r = l + 1; r < vec.size(); r++) {
            assert(*min_element(vec.begin() + l, vec.begin() + r) ==
                   tree.range_min(l, r));
        }
    }
}

int main() { test(); }