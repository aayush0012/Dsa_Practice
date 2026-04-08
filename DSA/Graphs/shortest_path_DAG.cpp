#include<map>
#include<queue>
#include <bits/stdc++.h>
using namespace std;

/*
================ SHORTEST PATH IN DAG =================

Approach:
1) Build adjacency list: adj[u] -> {v, wt}
2) Generate topological order using DFS
3) Initialize distance array (source = 0, rest = INF)
4) Process nodes in topological order and relax edges
5) Mark unreachable nodes as -1

Time Complexity: O(V + E)
Works only for DAG
======================================================
*/

class Solution {
  public:
  
  void dfs(int node, map<int,vector<pair<int,int>>> &adj,
           stack<int> &st, map<int,int> &visited){
        visited[node] = 1;
        for(auto it : adj[node]){
            if(!visited[it.first]){
                dfs(it.first, adj, st, visited);
            }
        }
        st.push(node);
  }

    vector<int> shortestPath(int V, int E, vector<vector<int>>& edges) {
        
       map<int,vector<pair<int,int>>> adj;
       for(int i = 0; i < edges.size(); i++){
            int u = edges[i][0]; 
            int v = edges[i][1]; 
            int wt = edges[i][2]; 
            adj[u].push_back({v, wt}); 
       }
       map<int,int> visited;
       stack<int> st;
       for(int i = 0; i < V; i++){
            if(!visited[i]){
                dfs(i, adj, st, visited);
            }
       }

       vector<int> ans(V);
       for(int i = 0; i < V; i++){
            ans[i] = INT_MAX;
       }

       ans[0] = 0;

       while(!st.empty()){
            int node = st.top(); 
            st.pop(); 
            if(ans[node] == INT_MAX) continue;
            for(auto it : adj[node]){
                int v = it.first;
                int wt = it.second;

                if(ans[node] + wt < ans[v]){
                    ans[v] = ans[node] + wt;
                }
            }
       }

       for(int i = 0; i < ans.size(); i++){
            if(ans[i] == INT_MAX) ans[i] = -1; 
       }

       return ans; 
    }
};