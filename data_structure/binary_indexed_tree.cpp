/*
树状数组，也称为二叉索引树（Binary Indexed Tree，BIT）
树状数组可以在O(logN)时间复杂度内实现序列的前缀和以及单点更新；

主要思想：
是将序列中的每个元素都映射到一个二进制表示下的位置上，假设一个序列为a[1...n]，那么树状数组的第i个位置（i>0）维护的是从a[i-lowbit(i)+1]到a[i]的区间和；
树状数组的下标一般从1开始，因为树状数组的实现是基于二进制的位运算，从而需要使用下标0的位置来表示一个空节点或者是根节点的父节点；

树状数组能解决的问题是线段树能解决的问题的子集，但树状数组的代码要远比线段树短，时间效率常数也更小；
*/
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

template <typename T> class BinaryIndexedTree {
  public:
    // 建树：根据区间 [1, n] 创建树状树组
    // 时间复杂度：O(N)
    // 每一个节点的值是由所有与自己直接相连的儿子的值求和得到的，因此可以倒着考虑贡献，即每次确定完儿子的值后，用自己的值更新自己的直接父亲。
    BinaryIndexedTree(vector<T> &vec, int n) {
        bit.resize(n + 1);
        this->n = n;
        for (int i = 1; i <= n; i++) {
            bit[i] += vec[i];
            // 父结点
            int j = i + lowbit(i);
            if (j <= n) {
                bit[j] += bit[i];
            }
        }
    }

    // 区间查询：查询区间 [1, k] 的和
    // 时间复杂度：O(logN)
    T get_sum(int k) {
        T s = 0;
        while (k) {
            s += bit[k];
            // 上一个区间右结点
            k -= lowbit(k);
        }
        return s;
    }

    // 单点修改：第k个元素加x
    // 时间复杂度：O(logN)
    void add(int k, T x) {
        while (k <= n) {
            bit[k] += x;
            // 父结点
            k += lowbit(k);
        }
    }

  private:
    // k 的二进制中，最低位的 1 以及后面所有 0 组成的数。
    int lowbit(int k) { return k & -k; }
    vector<T> bit;
    int n;
};

void test() {
    int n = 10;
    vector<int> vec(n + 1);
    srand(time(0));
    for (int i = 1; i <= n; i++) {
        int tmp = rand() % 100;
        vec[i] = tmp;
    }
    BinaryIndexedTree<int> tree(vec, n);
    for (int i = 1; i <= n; i++) {
        assert(accumulate(vec.begin() + 1, vec.begin() + i + 1, 0) ==
               tree.get_sum(i));
    }
}

int main() { test(); }