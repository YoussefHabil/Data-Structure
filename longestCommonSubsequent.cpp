#include <iostream>
#include <algorithm>

using namespace std;

// Dynamic Programming Approach
string longestCommonSubsequenceDP(const string& X, const string& Y) {
    int m = X.length();
    int n = Y.length();

    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; ++i)
        for (int j = 0; j <= n; ++j)
            dp[i][j] = 0;

    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            dp[i][j] = (X[i - 1] == Y[j - 1]) ? dp[i - 1][j - 1] + 1 : max(dp[i - 1][j], dp[i][j - 1]);

    int len = dp[m][n];
    string lcs(len, ' ');

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[--len] = X[i - 1];
            --i;
            --j;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }

    return lcs;
}
