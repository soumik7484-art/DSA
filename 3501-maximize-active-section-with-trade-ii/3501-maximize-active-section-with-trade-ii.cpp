#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
private:
    // Helper function for Range Maximum Query on Sparse Table
    int query_rmq(const vector<vector<int>>& st, int L_idx, int R_idx) {
        if (L_idx > R_idx || st.empty()) return 0;
        int len = R_idx - L_idx + 1;
        int k = 31 - __builtin_clz(len);
        return max(st[k][L_idx], st[k][R_idx - (1 << k) + 1]);
    }

public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        int total_ones = 0;
        for (char c : s) {
            if (c == '1') total_ones++;
        }

        // Extract all contiguous 0-blocks in string s
        vector<int> Z_start, Z_end, Z_len;
        for (int i = 0; i < n; ) {
            if (s[i] == '0') {
                int j = i;
                while (j < n && s[j] == '0') j++;
                Z_start.push_back(i);
                Z_end.push_back(j - 1);
                Z_len.push_back(j - i);
                i = j;
            } else {
                i++;
            }
        }

        int p = Z_len.size();
        vector<int> adj_sum(max(0, p - 1));
        for (int i = 0; i < p - 1; i++) {
            adj_sum[i] = Z_len[i] + Z_len[i + 1];
        }

        // Build Sparse Table for Range Maximum Query (RMQ) on adj_sum
        int sz = adj_sum.size();
        int K = 0;
        while ((1 << K) <= sz) K++;
        vector<vector<int>> st(K, vector<int>(sz, 0));

        if (sz > 0) {
            for (int i = 0; i < sz; i++) st[0][i] = adj_sum[i];
            for (int j = 1; j < K; j++) {
                for (int i = 0; i + (1 << j) <= sz; i++) {
                    st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
                }
            }
        }

        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int L = q[0], R = q[1];

            // Binary search to find range of 0-blocks overlapping [L, R]
            auto it = lower_bound(Z_end.begin(), Z_end.end(), L);
            if (it == Z_end.end() || Z_start[it - Z_end.begin()] > R) {
                ans.push_back(total_ones);
                continue;
            }

            int first = it - Z_end.begin();
            auto it2 = upper_bound(Z_start.begin(), Z_start.end(), R);
            int last = (it2 - Z_start.begin()) - 1;

            if (first > last) {
                ans.push_back(total_ones);
                continue;
            }

            int m = last - first + 1;
            if (m < 2) {
                ans.push_back(total_ones);
                continue;
            }

            // Truncate boundary 0-blocks to query range [L, R]
            int b1 = min(Z_end[first], R) - max(Z_start[first], L) + 1;
            int bm = min(Z_end[last], R) - max(Z_start[last], L) + 1;

            int max_gain = 0;
            if (m == 2) {
                max_gain = b1 + bm;
            } else {
                int b2_full = Z_len[first + 1];
                int bm_minus_1_full = Z_len[last - 1];

                max_gain = max(b1 + b2_full, bm_minus_1_full + bm);

                // Range RMQ for fully contained internal 0-block adjacent pairs
                if (first + 1 <= last - 2) {
                    int mid_max = query_rmq(st, first + 1, last - 2);
                    max_gain = max(max_gain, mid_max);
                }
            }

            ans.push_back(total_ones + max_gain);
        }

        return ans;
    }
};