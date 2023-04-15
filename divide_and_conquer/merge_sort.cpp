/*
归并排序
时间复杂度: O(N*logN)
稳定性：稳定
*/
#include <iostream>
#include <vector>

using namespace std;

void my_merge_sort(vector<int>::iterator first, vector<int>::iterator last) {
    // Return if one or zero element.
    if (last - first <= 1) {
        return;
    }
    // 1. Divide
    int n = last - first;
    auto mid = first + n / 2;
    // 2. Conquer
    my_merge_sort(first, mid);
    my_merge_sort(mid, last);
    // 3. Combine
    vector<int> tmp_vec(n);
    auto i = first, j = mid;
    int k = 0;
    while (i != mid || j != last) {
        if (i != mid && j != last) {
            if (*i < *j) {
                tmp_vec[k++] = *i;
                i++;
            } else {
                tmp_vec[k++] = *j;
                j++;
            }
        } else if (i != mid) {
            tmp_vec[k++] = *i;
            i++;
        } else {
            tmp_vec[k++] = *j;
            j++;
        }
    }
    k = 0;
    for (auto it = first; it != last; it++) {
        *it = tmp_vec[k++];
    }
}

int main() {
    vector<int> vec = {9, 0, 8, 1, 7, 2, 6, 3, 5, 4};
    my_merge_sort(vec.begin(), vec.end());
    for (int x : vec) {
        cout << x << " " << endl;
    }
}