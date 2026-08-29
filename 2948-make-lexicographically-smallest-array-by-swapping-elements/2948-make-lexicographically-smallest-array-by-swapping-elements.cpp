class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();

        // Store {value, original index}
        vector<pair<int, int>> v;

        for (int i = 0; i < n; i++) {
            v.push_back({nums[i], i});
        }

        // Sort by value
        sort(v.begin(), v.end());

        vector<int> ans(n);

        int start = 0;

        while (start < n) {
            int end = start;

            // Find one connected group
            while (end + 1 < n &&
                   v[end + 1].first - v[end].first <= limit) {
                end++;
            }

            // Values in this group are already sorted.
            // Sort their original indices so the smallest values
            // go to the smallest indices.
            vector<int> indices;

            for (int i = start; i <= end; i++) {
                indices.push_back(v[i].second);
            }

            sort(indices.begin(), indices.end());

            // Assign sorted values to sorted indices
            for (int i = 0; i < (int)indices.size(); i++) {
                ans[indices[i]] = v[start + i].first;
            }

            start = end + 1;
        }

        return ans;
    }
};