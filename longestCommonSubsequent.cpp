#include <iostream>
#include <string>

using namespace std;

// Dynamic Programming Approach
string longestCommonSubsequenceDP(const string& X, const string& Y) {
    int m = X.length();
    int n = Y.length();

    int dp[m + 1][n + 1];

    // Initialize the DP table
    for (int i = 0; i <= m; ++i)
        for (int j = 0; j <= n; ++j)
            dp[i][j] = 0;

    // Fill in the DP table
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            dp[i][j] = (X[i - 1] == Y[j - 1]) ? dp[i - 1][j - 1] + 1 : max(dp[i - 1][j], dp[i][j - 1]);

    // Reconstruct the LCS
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

// Recursive Approach
string longestCommonSubsequenceRecursive(const string& X, const string& Y, int m, int n) {
    if (m == 0 || n == 0)
        return "";

    if (X[m - 1] == Y[n - 1]) {
        string result = longestCommonSubsequenceRecursive(X, Y, m - 1, n - 1);
        result += X[m - 1];
        return result;
    }

    string left = longestCommonSubsequenceRecursive(X, Y, m - 1, n);
    string right = longestCommonSubsequenceRecursive(X, Y, m, n - 1);

    return (left.length() > right.length()) ? left : right;
}

// Brute Force Approach
string longestCommonSubsequenceBruteForce(const string& X, const string& Y) {
    int m = X.length();

    // Initialize the longestSubsequence variable
    string longestSubsequence;

    // Iterate over all possible subsequences of X
    for (int i = 0; i < (1 << m); ++i) {
        string currentSubsequence;

        // Construct the current subsequence based on the bitmask
        for (int j = 0; j < m; ++j) {
            if (i & (1 << j)) {
                currentSubsequence += X[j];
            }
        }

        // Check if the current subsequence is a subsequence of Y
        size_t pos = 0;
        for (int k = 0; k < currentSubsequence.length(); ++k) {
            char c = currentSubsequence[k];
            pos = Y.find(c, pos);
            if (pos == string::npos) {
                break;
            }
            ++pos;
        }

        // Update the longestSubsequence if the current one is longer
        if (pos != string::npos && currentSubsequence.length() > longestSubsequence.length()) {
            longestSubsequence = currentSubsequence;
        }
    }

    return longestSubsequence;
}

int main() {
    string X, Y;

    // Prompt user to enter the first string
    cout << "Enter the first string: ";
    cin >> X;

    // Prompt user to enter the second string
    cout << "Enter the second string: ";
    cin >> Y;

    // Dynamic Programming
    string lcsDP = longestCommonSubsequenceDP(X, Y);
    int lenDP = lcsDP.length();

    cout << "\nDynamic Programming Approach:" << endl;
    cout << "Length of Longest Common Subsequence: " << lenDP << endl;
    cout << "Longest Common Subsequence: " << lcsDP << "\n\n";

    // Recursive Approach
    string lcsRecursive = longestCommonSubsequenceRecursive(X, Y, X.length(), Y.length());
    int lenRecursive = lcsRecursive.length();

    cout << "Recursive Approach:" << endl;
    cout << "Length of Longest Common Subsequence: " << lenRecursive << endl;
    cout << "Longest Common Subsequence: " << lcsRecursive << "\n\n";

    // Brute Force Approach
    string lcsBruteForce = longestCommonSubsequenceBruteForce(X, Y);
    int lenBruteForce = lcsBruteForce.length();

    cout << "Brute Force Approach:" << endl;
    cout << "Length of Longest Common Subsequence: " << lenBruteForce << endl;
    cout << "Longest Common Subsequence: " << lcsBruteForce << endl;

    return 0;
}
