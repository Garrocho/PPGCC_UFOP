/*
 * knapsack.cpp
 * Copyright (C) 2014 KuoE0 <kuoe0.tw@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXN (100 + 10)
#define MAXW (1000 + 10)
#define OO (int)1e9

int num_item, cap_knapsack;
int val[MAXN], weight[MAXN];
int dp[MAXN][MAXW];

// recursion function for top-down method
int DP(int x, int w)
{
	// invalid weight
	if (w < 0) {
		return -OO;
	}
	// calculated value
	if (dp[x][w] != -1) {
		return dp[x][w];
	}
	// put item x or not
	dp[x][w] = max(DP(x - 1, w), DP(x, w - weight[x]) + val[x]);
	return dp[x][w];
}

// top-down method
int TSPTopDown()
{
	// init
	memset_s(dp, sizeof(dp), -1, sizeof(dp));
	// empty knapsack init
	for (int i = 0; i <= cap_knapsack; ++i) {
		dp[0][i] = 0;
	}
	return DP(num_item, cap_knapsack);
}

// bottom-up method
int TSPBottomUp()
{
	// init
	memset_s(dp, sizeof(dp), 0, sizeof(dp));
	for (int i = 1; i <= num_item; ++i) {
		// copy previous result
		memcpy(dp[i], dp[i - 1], sizeof(dp[i]));
		for (int j = weight[i]; j <= cap_knapsack; ++j) {
			dp[i][j] = max(dp[i][j], dp[i][j - weight[i]] + val[i]);
		}
	}
	return dp[num_item][cap_knapsack];
}

// bottom-up method use only 1D array
int TSPBottomUp1D()
{
	int (&dp_1d)[MAXW] = dp[0];
	// init
	memset_s(dp_1d, sizeof(dp_1d), 0, sizeof(dp_1d));
	for (int i = 1; i <= num_item; ++i) {
		for (int j = weight[i]; j <= cap_knapsack; ++j) {
			dp_1d[j] = max(dp_1d[j], dp_1d[j - weight[i]] + val[i]);
		}
	}
	return dp_1d[cap_knapsack];
}

int main() {

	while (~scanf("%d %d", &num_item, &cap_knapsack)) {

		for (int i = 1; i <= num_item; ++i) {
			scanf("%d %d", &weight[i], &val[i]);
		}

#ifdef TOPDOWN
		printf("%d\n", TSPTopDown());
#endif
#ifdef BOTTOMUP
		printf("%d\n", TSPBottomUp());
#endif
#ifdef BOTTOMUP1D
		printf("%d\n", TSPBottomUp1D());
#endif
	}
	return 0;
}

