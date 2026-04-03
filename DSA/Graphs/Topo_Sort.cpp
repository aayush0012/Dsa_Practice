#include <bits/stdc++.h> 
using namespace std;

/*
======================== TOPOLOGICAL SORT (DFS) ========================

Definition:
Topological sorting is a linear ordering of vertices in a Directed Acyclic Graph (DAG)
such that for every directed edge u -> v, u comes before v in the ordering.

Key Points:
- Works only for Directed Graphs
- Graph must be acyclic (DAG)
- If cycle exists, topo sort is not valid

Approach (DFS + Stack):
1. Perform DFS traversal
2. After visiting all neighbors of a node, push it into stack
3. Stack gives reverse of topological order

Why it works?
- A node is pushed only after all its dependencies are processed
- Ensures correct ordering

Time Complexity: O(V + E)
Space Complexity: O(V + E)

Note:
- This method does NOT detect cycles
- For cycle detection, use Kahn’s Algorithm (BFS + indegree)
=======================================================================
*/

// DFS helper function
void solve(int node, vector<vector<int>>& adj, vector<int>& visited, stack<int>& st){
    
    visited[node] = 1; // mark node as visited

    // visit all adjacent nodes
    for(auto it : adj[node]){
        if(!visited[it]){
            solve(it, adj, visited, st); 
        }
    }

    // push node AFTER visiting all neighbors (important step)
    st.push(node); 
}

vector<int> topologicalSort(vector<vector<int>> &edges, int v, int e) {

    stack<int> st;

    // visited array to track visited nodes
    vector<int> visited(v, 0);  

    // adjacency list representation
    vector<vector<int>> adj(v); 

    // build graph
    for(int i = 0; i < edges.size(); i++){
        int u = edges[i][0]; 
        int vtx = edges[i][1]; 
        adj[u].push_back(vtx); 
    }

    // handle disconnected components
    for(int i = 0; i < v; i++){
        if(!visited[i]){
            solve(i, adj, visited, st); 
        }
    }

    // extract topological order from stack
    vector<int> ans; 
    while(!st.empty()){
        ans.push_back(st.top()); 
        st.pop(); 
    }

    return ans; 
}
