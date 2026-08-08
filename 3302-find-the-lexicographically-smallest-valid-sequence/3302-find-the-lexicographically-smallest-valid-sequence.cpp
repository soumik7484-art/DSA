class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // right[j] = rightmost position where word2[j]
        // can be placed while matching word2[j...m-1].
        vector<int> right(m, n);

        int j = m - 1;

        for (int i = n - 1; i >= 0 && j >= 0; --i) {
            if (word1[i] == word2[j]) {
                right[j] = i;
                --j;
            }
        }

        vector<int> ans;

        int pos = 0;
        bool changed = false;

        for (int j = 0; j < m; ++j) {
            bool found = false;

            while (pos < n) {

                // Character matches exactly.
                if (word1[pos] == word2[j]) {
                    ans.push_back(pos);
                    ++pos;
                    found = true;
                    break;
                }

                // We can change this character, but only once.
                //
                // After using pos for word2[j], the remaining
                // word2[j+1...] must be matched exactly.
                if (!changed) {
                    bool suffixPossible;

                    if (j == m - 1) {
                        suffixPossible = true;
                    } else {
                        // right[j+1] must exist and be after pos.
                        suffixPossible =
                            (right[j + 1] < n &&
                             right[j + 1] > pos);
                    }

                    if (suffixPossible) {
                        ans.push_back(pos);
                        ++pos;
                        changed = true;
                        found = true;
                        break;
                    }
                }

                ++pos;
            }

            if (!found)
                return {};
        }

        return ans;
    }
};