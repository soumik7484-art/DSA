class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int n = s.size();

        int ones = 0;
        for (char c : s)
            if (c == '1') ones++;

        string t = "1" + s + "1";
        int m = t.size();

        vector<pair<char,int>> runs;

        for (int i = 0; i < m;) {
            int j = i;
            while (j < m && t[j] == t[i]) j++;
            runs.push_back({t[i], j - i});
            i = j;
        }

        int bestGain = 0;

        for (int i = 1; i + 1 < runs.size(); i++) {

            // removable block of 1's : 0 111 0
            if (runs[i].first == '1' &&
                runs[i - 1].first == '0' &&
                runs[i + 1].first == '0') {

                int removeLen = runs[i].second;

                int mergedZero =
                    runs[i - 1].second +
                    removeLen +
                    runs[i + 1].second;

                int gain = mergedZero - removeLen;   // = leftZero + rightZero
                bestGain = max(bestGain, gain);
            }
        }

        return ones + bestGain;
    }
};