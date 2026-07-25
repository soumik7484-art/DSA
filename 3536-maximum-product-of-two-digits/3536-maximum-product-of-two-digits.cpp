class Solution {
public:
    int maxProduct(int n) {
        vector<int> digits;
        
        while (n > 0) {
            digits.push_back(n % 10);
            n /= 10;
        }

        int ans = 0;
        int m = digits.size();

        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                ans = max(ans, digits[i] * digits[j]);
            }
        }

        return ans;
    }
};