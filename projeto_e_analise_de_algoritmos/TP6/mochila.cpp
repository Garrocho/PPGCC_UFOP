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
#include <vector>
using namespace std;

#define OO (int)1e9

int num_item, cap_knapsack;
vector<int> val, weight;
vector< vector<int> > dp;

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
dp[x][w] = max(DP(x - 1, w), DP(x - 1, w - weight[x]) + val[x]);
return dp[x][w];
}

// top-down method
int TSPTopDown()
{
// init
fill(dp.begin(), dp.end(), vector<int>(cap_knapsack + 1, -1));
// empty knapsack init
fill(dp[0].begin(), dp[0].end(), 0);
return DP(num_item, cap_knapsack);
}

// bottom-up method
int TSPBottomUp()
{
// init
fill(begin(dp), end(dp), vector<int>(cap_knapsack + 1, 0));
for (int i = 1; i <= num_item; ++i) {
// copy previous result
dp[i] = dp[i - 1];
for (int j = weight[i]; j <= cap_knapsack; ++j) {
dp[i][j] = max(dp[i][j], dp[i - 1][j - weight[i]] + val[i]);
}
}
return dp[num_item][cap_knapsack];
}

// bottom-up method use only 1D array
int TSPBottomUp1D()
{
auto dp_1d = dp[0];
// init
fill(begin(dp_1d), end(dp_1d), 0);
for (int i = 1; i <= num_item; ++i) {
for (int j = cap_knapsack; j >= weight[i]; --j) {
dp_1d[j] = max(dp_1d[j], dp_1d[j - weight[i]] + val[i]);
}
}
return dp_1d[cap_knapsack];
}

int main() {

while (~scanf("%d %d", &num_item, &cap_knapsack)) {
val = weight = vector<int>(num_item + 1);
dp = vector< vector<int> >(num_item + 1, vector<int>(cap_knapsack + 1));

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

