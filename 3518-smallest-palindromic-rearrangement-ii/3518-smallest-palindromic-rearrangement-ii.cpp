#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    // Computes nCr (n choose r) capped at 'limit' to prevent integer overflow
    long long nCr(int n, int r, long long limit) {
        if (r < 0 || r > n) return 0;
        if (r == 0 || r == n) return 1;
        if (r > n - r) r = n - r;
        long long res = 1;
        for (int i = 1; i <= r; ++i) {
            res = res * (n - r + i) / i;
            if (res >= limit) return limit;
        }
        return res;
    }

    // Computes the number of distinct permutations of remaining character counts, capped at 'limit'
    long long countPermutations(const vector<int>& counts, long long limit) {
        long long total_perms = 1;
        int rem_len = 0;
        for (int c : counts) {
            if (c <= 0) continue;
            rem_len += c;
            long long combinations = nCr(rem_len, c, limit);
            if (combinations == 0) return 0;
            if (limit / combinations < total_perms) {
                return limit;
            }
            total_perms *= combinations;
            if (total_perms >= limit) return limit;
        }
        return total_perms;
    }

public:
    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }

        vector<int> half_freq(26, 0);
        char mid_char = '\0';
        for (int i = 0; i < 26; ++i) {
            half_freq[i] = freq[i] / 2;
            if (freq[i] % 2 != 0) {
                mid_char = (char)('a' + i);
            }
        }

        // Check if total distinct palindromic permutations is less than k
        long long total_perms = countPermutations(half_freq, (long long)k + 1);
        if (total_perms < k) {
            return "";
        }

        int half_len = s.length() / 2;
        string first_half = "";
        long long cur_k = k;

        // Build the first half position by position
        for (int i = 0; i < half_len; ++i) {
            for (int ch = 0; ch < 26; ++ch) {
                if (half_freq[ch] > 0) {
                    half_freq[ch]--;
                    long long count = countPermutations(half_freq, cur_k + 1);
                    if (cur_k <= count) {
                        first_half += (char)('a' + ch);
                        break;
                    } else {
                        cur_k -= count;
                        half_freq[ch]++; // Backtrack and try next character
                    }
                }
            }
        }

        // Reconstruct the full palindrome
        string second_half = first_half;
        reverse(second_half.begin(), second_half.end());

        string result = first_half;
        if (mid_char != '\0') {
            result += mid_char;
        }
        result += second_half;

        return result;
    }
};