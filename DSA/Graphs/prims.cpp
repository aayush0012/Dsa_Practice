#include <bits/stdc++.h> 
using namespace std;

/*
================ PRIM'S ALGORITHM (MST) =================

Prim’s Algorithm is used to find the Minimum Spanning Tree (MST)
of a connected, weighted, undirected graph.

------------------------------------------------------------
CORE IDEA:
- Start from any node (here node 1)
- Grow the MST by always picking the minimum weight edge
  that connects a visited node to an unvisited node

------------------------------------------------------------
DATA STRUCTURES USED:

1) key[]
- Stores minimum weight required to include a node in MST
- Initialize all with INT_MAX, except starting node (0)

2) parent[]
- Stores parent of each node in MST

3) mst[]
- Boolean array to track if node is included in MST

------------------------------------------------------------
ALGORITHM STEPS:

1) Convert edge list into adjacency list
2) Initialize:
   key[1] = 0
   parent[1] = -1
3) Repeat n times:
   - Pick node with minimum key (not in MST)
   - Mark it as included in MST
   - Update adjacent nodes:
       if not in MST and weight < key:
           update key and parent

------------------------------------------------------------
RESULT:
- parent[] gives MST structure
- key[] gives weights
- MST edges: (parent[i], i)

------------------------------------------------------------
TIME COMPLEXITY:
- O(N^2) (due to linear search)
- Can be optimized using priority queue → O(E log V)

============================================================
*/

vector<pair<pair<int, int>, int>> calculatePrimsMST(int n, int m, vector<pair<pair<int, int>, int>> &g)
{
    map<int,vector<pair<int,int>>> mp; 

    // Build adjacency list
    for(int i= 0; i<g.size(); i++){
        int u = g[i].first.first;
        int v= g[i].first.second;
        int w=g[i].second; 

        mp[u].push_back({v,w}); 
        mp[v].push_back({u,w}); 
    }

    vector<int> parent(n+1,-1);
    vector<int> key(n+1,INT_MAX);
    vector<bool> mst(n+1,false); 

    // Start from node 1
    key[1]=0; 

    for(int i =1; i<=n ;i++){
        int mini=INT_MAX; 
        int node=1; 

        // Find minimum key node not in MST
        for(int v=1; v<=n; v++){
            if(!mst[v] && key[v]<mini){
                mini=key[v]; 
                node=v; 
            }
        }

        mst[node]=true;

        // Update adjacent nodes
        for(auto it:mp[node]){
            int v = it.first;
            int wt = it.second;

            if(!mst[v] && wt < key[v]){ 
                parent[v]=node; 
                key[v]=wt; 
            }
        }
    }

    vector<pair<pair<int, int>, int>> ans; 

    // Build MST result
    for(int i =2; i<=n; i++){
        ans.push_back({{parent[i],i},key[i]}); 
    }

    return ans; 
}