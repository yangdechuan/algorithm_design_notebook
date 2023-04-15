/*
堆排序
时间复杂度：O(NlogN)
稳定性：不稳定
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 实现一个大根二叉堆
class MyHeap {
  public:
    // 初始化堆
    void heapify(vector<int> &vec) {
        int n = vec.size();
        for (int i = n / 2; i >= 0; i--) {
            down(vec, i, n);
            n--;
        }
    }

    // 下沉
    void down(vector<int> &vec, int x, int n) {
        int i = x;
        while ((2 * i + 1 < n && vec[i] < vec[2 * i + 1]) ||
               (2 * i + 2 < n && vec[i] < vec[2 * i + 2])) {
            int l = 2 * i + 1, r = 2 * i + 2;
            int largest = l;
            if (r < n && vec[l] < vec[r]) {
                largest = r;
            }
            swap(vec[i], vec[largest]);
            i = largest;
        }
    }
};

// 用自己实现的大根堆做堆排序
void solve_heap_sort(vector<int> &vec) {
    MyHeap myheap;

    // 初始建堆 O(N)
    myheap.heapify(vec);

    // 堆排序 O(NlogN)
    int hlen = vec.size();
    int n = hlen;
    for (int i = 0; i < n - 1; i++) {
        swap(vec[0], vec[hlen - 1]);
        hlen--;
        myheap.down(vec, 0, hlen);
    }
}

// 用 STL 中的堆函数堆排序
void solve_heap_sort_with_stl_func(vector<int> &vec) {
    auto first = vec.begin();
    auto last = vec.end();
    make_heap(first, last, less<int>());
    while (last != first) {
        pop_heap(first, last);
        last--;
    }
}

// 用 STL 中的 priority_queue 做堆排序
void solve_heap_sort_with_stl_pq(vector<int> &vec) {
    // priority_queue 会拷贝vec，所以不改变vec
    priority_queue<int, vector<int>, less<int>> pq(vec.begin(), vec.end());
    int n = vec.size();
    for (int i = n - 1; i >= 0; i--) {
        vec[i] = pq.top();
        pq.pop();
    }
}

int main() {
    vector<int> vec = {9, 0, 8, 1, 7, 2, 6, 3, 5, 4};
    solve_heap_sort(vec);
    // solve_heap_sort_with_stl_func(vec);
    // solve_heap_sort_with_stl_pq(vec);
    for (int x : vec) {
        cout << x << " " << endl;
    }
}