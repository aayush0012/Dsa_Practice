#include <bits/stdc++.h>
using namespace std;

/*
STEPS (Kahn's Algorithm - BFS Topological Sort):
1. Find indegree of all vertices
2. Push all nodes with indegree 0 into queue
3. Do BFS and reduce indegree of adjacent nodes
*/

vector<int> topologicalSort(vector<vector<int>> &edges, int v, int e) {
    
    // Step 1: Create adjacency list
    vector<vector<int>> adj(v);
    for (int i = 0; i < e; i++) {
        int u = edges[i][0];
        int w = edges[i][1];
        adj[u].push_back(w);
    }

    // Step 2: Compute indegree
    vector<int> indeg(v, 0);
    for (int i = 0; i < v; i++) {
        for (auto it : adj[i]) {
            indeg[it]++;
        }
    }

    // Step 3: Push nodes with indegree 0
    queue<int> q;
    for (int i = 0; i < v; i++) {
        if (indeg[i] == 0) {
            q.push(i);
        }
    }

    // Step 4: BFS (Kahn's Algorithm)
    vector<int> ans;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        ans.push_back(node);

        for (auto it : adj[node]) {
            indeg[it]--;
            if (indeg[it] == 0) {
                q.push(it);
            }
        }
    }

    return ans;
}