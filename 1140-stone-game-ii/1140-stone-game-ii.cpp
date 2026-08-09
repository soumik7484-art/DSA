class Solution {
public:
    int n;
    vector<int> piles;
    vector<int> suffix;
    vector<vector<int>> dp;

    int solve(int i, int M) {
        if (i >= n)
            return 0;

        if (dp[i][M] != -1)
            return dp[i][M];

        // Can take all remaining piles
        if (i + 2 * M >= n)
            return dp[i][M] = suffix[i];

        int best = 0;

        // Try taking X piles, where 1 <= X <= 2*M
        for (int X = 1; X <= 2 * M && i + X <= n; X++) {

            // Stones Bob can force us to lose afterwards
            int bob = solve(i + X, max(M, X));

            // Current player gets total remaining stones - Bob's best
            int current = suffix[i] - bob;

            best = max(best, current);
        }

        return dp[i][M] = best;
    }

    int stoneGameII(vector<int>& piles) {
        this->piles = piles;
        n = piles.size();

        // suffix[i] = sum of piles[i...n-1]
        suffix.resize(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        // M can go up to n
        dp.assign(n, vector<int>(n + 1, -1));

        return solve(0, 1);
    }
};