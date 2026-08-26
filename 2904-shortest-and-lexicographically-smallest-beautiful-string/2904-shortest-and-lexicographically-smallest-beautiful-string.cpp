class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();

        int left = 0;
        int ones = 0;
        int bestLen = INT_MAX;
        string ans = "";

        for (int right = 0; right < n; right++) {
            if (s[right] == '1')
                ones++;

            // Shrink while we have at least k ones.
            while (left <= right && ones >= k) {

                if (ones == k) {
                    int len = right - left + 1;
                    string cur = s.substr(left, len);

                    if (len < bestLen) {
                        bestLen = len;
                        ans = cur;
                    }
                    else if (len == bestLen && cur < ans) {
                        ans = cur;
                    }
                }

                if (s[left] == '1')
                    ones--;

                left++;
            }
        }

        return ans;
    }
};
