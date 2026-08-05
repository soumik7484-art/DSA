class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> adj(n);
        
        for (auto &e : invocations) {
            adj[e[0]].push_back(e[1]);
        }

        // Find all suspicious methods using DFS
        vector<int> suspicious(n, 0);
        stack<int> st;
        st.push(k);
        suspicious[k] = 1;

        while (!st.empty()) {
            int u = st.top();
            st.pop();

            for (int v : adj[u]) {
                if (!suspicious[v]) {
                    suspicious[v] = 1;
                    st.push(v);
                }
            }
        }

        // Check if any non-suspicious method invokes a suspicious method
        for (auto &e : invocations) {
            int u = e[0], v = e[1];
            if (!suspicious[u] && suspicious[v]) {
                vector<int> ans;
                for (int i = 0; i < n; i++)
                    ans.push_back(i);
                return ans;
            }
        }

        // Remove suspicious methods
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (!suspicious[i])
                ans.push_back(i);
        }

        return ans;
    }
};