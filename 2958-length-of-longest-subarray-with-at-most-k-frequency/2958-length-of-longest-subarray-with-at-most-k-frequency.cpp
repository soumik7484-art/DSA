class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        unordered_map<int, int> freq;

        int left = 0;
        int ans = 0;

        for (int right = 0; right < nums.size(); right++) {
            freq[nums[right]]++;

            // Make the window valid
            while (freq[nums[right]] > k) {
                freq[nums[left]]--;
                left++;
            }

            // Current window is good
            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};