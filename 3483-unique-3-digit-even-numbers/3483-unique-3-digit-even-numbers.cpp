class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        int freq[10] = {0};

        for (int d : digits) {
            freq[d]++;
        }

        int ans = 0;

        // Check every 3-digit number
        for (int num = 100; num <= 999; num++) {

            // Must be even
            if (num % 2 != 0)
                continue;

            int x = num;

            int a = x / 100;
            int b = (x / 10) % 10;
            int c = x % 10;

            // Temporarily use the digits
            freq[a]--;
            freq[b]--;
            freq[c]--;

            // If all required digits were available
            if (freq[a] >= 0 &&
                freq[b] >= 0 &&
                freq[c] >= 0) {
                ans++;
            }

            // Restore
            freq[a]++;
            freq[b]++;
            freq[c]++;
        }

        return ans;
    }
};