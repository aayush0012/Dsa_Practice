#include <bits/stdc++.h>
using namespace std;

/*
====================== DIJKSTRA (EASY HUMAN EXPLANATION) ======================

Goal:
Given a source node, find the shortest distance to all other nodes.

Simple Thinking:
- Start from source (distance = 0)
- Go to its neighbors and update their distances
- Always pick the node which currently has the smallest distance

Why Priority Queue (pq)?
- We need the minimum distance node every time
- pq (min heap) gives smallest element quickly (O(log n))
- So we always process the closest node first

Important Trick:
- We store {distance, node} in pq
- Because pq sorts based on FIRST element → so distance must come first

Flow:
1. Put source in pq with distance 0
2. Take the smallest distance node
3. Check all its neighbors
4. If shorter path found → update distance and push again in pq
5. Repeat until pq is empty

Note:
- Works only when all weights are NON-NEGATIVE

===============================================================================
*/

vector<int> dijkstra(vector<vector<int>> &vec, int vertices, int edges, int source) {

    // Min heap -> {distance, node}
    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;

    // Adjacency list -> node : {adjNode, weight}
    map<int, list<pair<int,int>>> adj;

    // Build graph (undirected)
    for(int i = 0; i < vec.size(); i++){
        int u = vec[i][0];
        int v = vec[i][1];
        int wt = vec[i][2];

        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }

    // Distance array
    vector<int> ans(vertices, INT_MAX);

    // Initialize
    pq.push({0, source});
    ans[source] = 0;

    while(!pq.empty()){
        int weight = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        for(auto it : adj[u]){
            int val = it.second;

            if(weight + val < ans[it.first]){
                ans[it.first] = weight + val;
                pq.push({ans[it.first], it.first});
            }
        }
    }

    return ans;
}