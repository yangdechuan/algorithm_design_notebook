/*
快速排序
时间复杂度: O(N*logN)
稳定性：不稳定
*/
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void my_quick_sort(typename vector<T>::iterator first,
                   typename vector<T>::iterator last) {
    // Return if one or zero element.
    if (last - first <= 1) {
        return;
    }
    // 1. Divide
    T pivot = *first;
    auto pred = [=](T x) { return x < pivot; };
    auto mid = partition(first + 1, last, pred);
    swap(*first, *(mid - 1));
    // 2. Conquer
    my_quick_sort<T>(first, mid - 1);
    my_quick_sort<T>(mid, last);
}

int main() {
    vector<int> vec = {9, 0, 8, 1, 7, 2, 6, 3, 5, 4};
    my_quick_sort<int>(vec.begin(), vec.end());
    for (int x : vec) {
        cout << x << " " << endl;
    }
}