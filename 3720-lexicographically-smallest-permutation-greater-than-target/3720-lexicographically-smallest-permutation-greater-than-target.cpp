class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        vector<int> total(26, 0);
        for (char c : s)
            total[c - 'a']++;

        // Try changing the rightmost possible position.
        for (int i = n - 1; i >= 0; i--) {

            // Count characters left after using target[0...i-1].
            vector<int> cnt = total;
            bool possible = true;

            for (int j = 0; j < i; j++) {
                int x = target[j] - 'a';

                if (cnt[x] == 0) {
                    possible = false;
                    break;
                }

                cnt[x]--;
            }

            if (!possible)
                continue;

            // Find the smallest available character
            // strictly greater than target[i].
            for (int c = target[i] - 'a' + 1; c < 26; c++) {

                if (cnt[c] == 0)
                    continue;

                string ans = target.substr(0, i);

                // Make the first difference here.
                ans += char('a' + c);
                cnt[c]--;

                // Remaining characters in sorted order
                // give the smallest possible suffix.
                for (int x = 0; x < 26; x++) {
                    ans += string(cnt[x], char('a' + x));
                }

                return ans;
            }
        }

        return "";
    }
};