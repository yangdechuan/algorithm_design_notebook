/*
无序数组中找第k大元素
时间复杂度O(N)
*/
#include <iostream>
#include <vector>

using namespace std;

// 实现STL中的 partition 函数
// 满足pred的元素放在前半部分，不满足的放在后半部分，并返回后半部分的首位
vector<int>::iterator my_partition(vector<int>::iterator first,
                                   vector<int>::iterator last,
                                   function<bool(int)> pred) {
    auto slow = first, fast = first;
    while (fast != last) {
        if (pred(*fast)) {
            swap(*fast, *slow);
            slow++;
        }
        fast++;
    }
    return slow;
}

int my_quick_select(vector<int>::iterator first, vector<int>::iterator last,
                    int k) {
    // 1. Divide
    int pivot = *first;
    auto pred = [=](int x) { return x > pivot; };
    auto mid = my_partition(first + 1, last, pred);
    swap(*first, *(mid - 1));
    // 2. Conquer
    if (mid - first == k) {
        return *(mid - 1);
    } else if (mid - first > k) {
        return my_quick_select(first, mid - 1, k);
    } else {
        return my_quick_select(mid, last, k - (mid - first));
    }
}

int main() {
    vector<int> vec;
    vec = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    int ans = my_quick_select(vec.begin(), vec.end(), 4);
    cout << "ans: " << ans << endl;
}