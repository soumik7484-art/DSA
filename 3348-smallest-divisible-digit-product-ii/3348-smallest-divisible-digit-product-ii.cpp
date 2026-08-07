#include <bits/stdc++.h>
using namespace std;

class Solution {
    int E2, E3;
    vector<vector<int>> dp;

    void factorDigit(int d, int &a, int &b, int &c5, int &c7) {
        while (d % 2 == 0) {
            a = max(0, a - 1);
            d /= 2;
        }

        while (d % 3 == 0) {
            b = max(0, b - 1);
            d /= 3;
        }

        while (d % 5 == 0) {
            c5 = max(0, c5 - 1);
            d /= 5;
        }

        while (d % 7 == 0) {
            c7 = max(0, c7 - 1);
            d /= 7;
        }
    }

    bool canMake(int a, int b, int c5, int c7, int len) {
        if (a < 0 || b < 0 || c5 < 0 || c7 < 0)
            return false;

        return dp[a][b] + c5 + c7 <= len;
    }

    string buildSuffix(
        int len,
        int a,
        int b,
        int c5,
        int c7
    ) {
        string res;
        res.reserve(len);

        for (int i = 0; i < len; i++) {

            for (int d = 1; d <= 9; d++) {

                int na = a;
                int nb = b;
                int n5 = c5;
                int n7 = c7;

                factorDigit(d, na, nb, n5, n7);

                int remaining = len - i - 1;

                if (!canMake(
                        na, nb, n5, n7, remaining))
                    continue;

                res.push_back(char('0' + d));

                a = na;
                b = nb;
                c5 = n5;
                c7 = n7;

                break;
            }
        }

        return res;
    }

public:
    string smallestNumber(string num, long long t) {

        // --------------------------------------------------
        // Factorize t
        // --------------------------------------------------

        E2 = E3 = 0;
        int E5 = 0, E7 = 0;

        while (t % 2 == 0) {
            E2++;
            t /= 2;
        }

        while (t % 3 == 0) {
            E3++;
            t /= 3;
        }

        while (t % 5 == 0) {
            E5++;
            t /= 5;
        }

        while (t % 7 == 0) {
            E7++;
            t /= 7;
        }

        // Prime factor > 7 cannot be produced by any digit 1..9.
        if (t != 1)
            return "-1";

        // --------------------------------------------------
        // DP
        //
        // dp[a][b] = minimum number of digits needed
        // to provide at least 2^a * 3^b.
        // --------------------------------------------------

        dp.assign(
            E2 + 1,
            vector<int>(E3 + 1, 1e9)
        );

        dp[0][0] = 0;

        vector<pair<int, int>> choices = {
            {1, 0}, // 2
            {0, 1}, // 3
            {2, 0}, // 4
            {1, 1}, // 6
            {3, 0}, // 8
            {0, 2}  // 9
        };

        for (int a = 0; a <= E2; a++) {
            for (int b = 0; b <= E3; b++) {

                if (dp[a][b] == 1e9)
                    continue;

                for (auto [x, y] : choices) {

                    int na = min(E2, a + x);
                    int nb = min(E3, b + y);

                    dp[na][nb] =
                        min(dp[na][nb],
                            dp[a][b] + 1);
                }
            }
        }

        int n = num.size();

        // --------------------------------------------------
        // Prefix information
        //
        // pref2[i] = remaining exponent of 2 after
        // processing num[0 ... i-1].
        // --------------------------------------------------

        vector<int> pref2(n + 1, E2);
        vector<int> pref3(n + 1, E3);
        vector<int> pref5(n + 1, E5);
        vector<int> pref7(n + 1, E7);

        // prefixOK[i] = whether num[0 ... i-1] is zero-free
        vector<char> prefixOK(n + 1, true);

        for (int i = 0; i < n; i++) {

            pref2[i + 1] = pref2[i];
            pref3[i + 1] = pref3[i];
            pref5[i + 1] = pref5[i];
            pref7[i + 1] = pref7[i];

            int d = num[i] - '0';

            if (d == 0) {
                prefixOK[i + 1] = false;
            } else {
                prefixOK[i + 1] = prefixOK[i];

                factorDigit(
                    d,
                    pref2[i + 1],
                    pref3[i + 1],
                    pref5[i + 1],
                    pref7[i + 1]
                );
            }
        }

        // --------------------------------------------------
        // Is num itself valid?
        // --------------------------------------------------

        if (prefixOK[n] &&
            pref2[n] == 0 &&
            pref3[n] == 0 &&
            pref5[n] == 0 &&
            pref7[n] == 0) {

            return num;
        }

        // --------------------------------------------------
        // Try SAME LENGTH.
        //
        // Change the rightmost possible position.
        // --------------------------------------------------

        int minimumLength =
            dp[E2][E3] + E5 + E7;

        if (n >= minimumLength) {

            for (int i = n - 1; i >= 0; i--) {

                // Prefix before i must be zero-free.
                if (!prefixOK[i])
                    continue;

                int original = num[i] - '0';

                // Try smallest digit > original.
                for (int d = original + 1; d <= 9; d++) {

                    int a = pref2[i];
                    int b = pref3[i];
                    int c5 = pref5[i];
                    int c7 = pref7[i];

                    factorDigit(
                        d,
                        a, b, c5, c7
                    );

                    int remaining = n - i - 1;

                    if (!canMake(
                            a, b, c5, c7,
                            remaining))
                        continue;

                    string suffix = buildSuffix(
                        remaining,
                        a, b, c5, c7
                    );

                    if ((int)suffix.size() != remaining)
                        continue;

                    string ans;
                    ans.reserve(n);

                    ans += num.substr(0, i);
                    ans.push_back(char('0' + d));
                    ans += suffix;

                    return ans;
                }
            }
        }

        // --------------------------------------------------
        // Same length impossible.
        //
        // Need the smallest possible longer length.
        // --------------------------------------------------

        int len = max(n + 1, minimumLength);

        string ans = buildSuffix(
            len,
            E2,
            E3,
            E5,
            E7
        );

        if ((int)ans.size() != len)
            return "-1";

        return ans;
    }
};