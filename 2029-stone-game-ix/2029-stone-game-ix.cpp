#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int cnt[3] = {0, 0, 0};

        for (int x : stones) {
            cnt[x % 3]++;
        }

        // Stones divisible by 3 can be ignored initially.
        // If there are an odd number of them, they effectively
        // switch whose turn it is.

        if (cnt[0] % 2 == 0) {
            // Alice wins if both remainder groups exist
            // and their counts are sufficiently unbalanced.
            return cnt[1] > 0 && cnt[2] > 0;
        }

        // Odd number of 0-mod-3 stones
        return abs(cnt[1] - cnt[2]) > 2;
    }
};