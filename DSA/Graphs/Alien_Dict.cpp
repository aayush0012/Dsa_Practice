#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    string findOrder(vector<string> &words) {
        /*
        ------------------------------------------------------------
        ALIEN DICTIONARY USING TOPOLOGICAL SORT (KAHN'S ALGORITHM)
        ------------------------------------------------------------

        Idea:
        1. Each character = node
        2. Compare adjacent words to find ordering (edge)
        3. Build graph (adj list)
        4. Compute indegree of each node
        5. Apply Kahn’s Algorithm (BFS Topo Sort)
        6. If all nodes processed → valid order
           else → cycle → return ""

        ------------------------------------------------------------
        */

        // Total number of unique characters
        int total = 0;

        // Adjacency list (graph)
        map<char, vector<char>> mp;

        // Visited array to track which characters are present
        map<int, int> visited;

        // Step 1: Mark all unique characters
        for (int i = 0; i < words.size(); i++) {
            for (int j = 0; j < words[i].size(); j++) {
                int idx = words[i][j] - 'a';
                if (visited[idx] == 0) {
                    total++;               // count unique characters
                }
                visited[idx] = 1;
            }
        }

        // Step 2: Build graph using adjacent word comparison
        for (int i = 0; i < words.size() - 1; i++) {
            string word1 = words[i];
            string word2 = words[i + 1];

            int n1 = word1.size();
            int n2 = word2.size();

            int index1 = 0, index2 = 0;

            // Find first mismatching character
            while (index1 < n1 && index2 < n2) {
                if (word1[index1] == word2[index2]) {
                    index1++;
                    index2++;
                } else {
                    // Create directed edge: word1[index1] -> word2[index2]
                    mp[word1[index1]].push_back(word2[index2]);
                    break;
                }
            }

            // Edge case: prefix issue (invalid dictionary)
            // Example: ["abc", "ab"]
            if (index1 != n1 && index2 == n2) {
                return "";
            }
        }

        // Step 3: Compute indegree of each node
        vector<int> indeg(26, 0);

        for (auto it : mp) {
            for (auto ch : it.second) {
                indeg[ch - 'a']++;
            }
        }

        // Step 4: Push all nodes with indegree = 0
        queue<char> q;
        for (int i = 0; i < 26; i++) {
            if (visited[i] && indeg[i] == 0) {
                q.push('a' + i);
            }
        }

        // Step 5: Kahn's Algorithm (BFS)
        string ans = "";
        int cnt = 0;

        while (!q.empty()) {
            char node = q.front();
            q.pop();

            ans += node;
            cnt++;

            // Reduce indegree of neighbors
            for (auto neigh : mp[node]) {
                indeg[neigh - 'a']--;

                if (indeg[neigh - 'a'] == 0) {
                    q.push(neigh);
                }
            }
        }

        // Step 6: Check for cycle
        // If all nodes processed → valid ordering
        if (cnt == total) {
            return ans;
        }

        // Otherwise cycle exists
        return "";
    }
};