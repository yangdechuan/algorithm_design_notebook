/*
问题：n个物品一个背包，物品i的重量是wi>0，价值vi>0，背包容量是W，求把物品放入背包，能容纳的最大价值。
时间复杂度：O(n*W)

dp(i, j) = max profit subset of items 1, …, i with weight limit j.
dp(i, j) = max{ dp(i - 1, j), dp(i - 1, j - wi) + vi }
*/
#include <iostream>
#include <vector>

using namespace std;

int solve_01_knapsack(vector<int> &w, vector<int> &v, int W) {
    int n = w.size();
    vector<int> dp(W + 1, 0);
    for (int i = 1; i <= n; i++) {        // item
        for (int j = W; j >= w[i]; j--) { // capacity
            // dp[j]: DP doesn't select item i
            // dp[j - w[i]] + v[i]: DP selects item i
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    return dp[W];
}