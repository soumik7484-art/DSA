class Solution {
public:
    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    int findGCD(vector<int>& nums) {
        int mn = nums[0], mx = nums[0];

        for (int num : nums) {
            mn = min(mn, num);
            mx = max(mx, num);
        }

        return gcd(mn, mx);
    }
};