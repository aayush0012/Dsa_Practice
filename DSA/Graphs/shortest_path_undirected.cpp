#include<map>
#include<queue>
#include <bits/stdc++.h>
using namespace std;
vector<int> shortestPath(
    vector<pair<int,int>> edges,
    int n , int m,
    int s , int t){

    // Step 1: Create adjacency list for undirected graph
    vector<vector<int>> adj(n+1);
    for(int i =0; i<edges.size(); i++){
        int u = edges[i].first;
        int v = edges[i].second;

        adj[u].push_back(v);
        adj[v].push_back(u); // because graph is undirected
    }

    // parent[i] will store from which node we reached 'i'
    vector<int> parent(n+1);

    // queue for BFS traversal
    queue<int> q;

    // visited map to keep track of visited nodes
    map<int,bool> visited;

    // not used in logic (can be removed, but keeping as per original code)
    vector<int> path;

    // Step 2: Start BFS from source node 's'
    q.push(s);
    parent[s] = -1; // source has no parent

    while(!q.empty()){
        int frnt = q.front();
        q.pop();

        // mark current node as visited
        visited[frnt] = 1;

        // explore all neighbours
        for(auto it : adj[frnt]){
            if(!visited[it]){
                visited[it] = 1;   // mark visited
                parent[it] = frnt; // store parent
                q.push(it);        // push for further traversal
            }
        }
    }

    // Step 3: Reconstruct path from target 't' to source 's'
    vector<int> ans;

    int index = t;
    ans.push_back(index);

    // move backwards using parent array until we reach source
    while(index != s){
        index = parent[index];
        ans.push_back(index);
    }

    // reverse to get path from s -> t
    reverse(ans.begin(), ans.end());

    return ans;
}