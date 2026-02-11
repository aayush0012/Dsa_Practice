#include<map> 
#include <iostream>
#include <vector>
#include <map>
using namespace std;
void solve(vector<vector<int>>& ans, vector<vector<int>> &edges,int n){
     map<int,vector<int>> mp; 
    for(int i =0; i<n; i++){
        mp[i]=vector<int>(); 
   }
    for(int i =0; i<edges.size(); i++){
        mp[edges[i][0]].push_back(edges[i][1]); 
        mp[edges[i][1]].push_back(edges[i][0]); 
    } 
    for(auto it: mp){
        vector<int>res;
        res.push_back(it.first); 
        for(auto j:it.second ){
            res.push_back(j); 
        }
        ans.push_back(res); 
    }
    
}
void dfs(vector<vector<int>> &adj ,map<int,bool> &visited, int node,vector<int> &arr){
    // now we have to apply dfs 
    arr.push_back(node); 
    visited[node]=1; 
    for(auto it:adj[node]){
        if(!visited[it]){
           dfs(adj,visited,it,arr); 
        }
    }
}
vector<vector<int>> depthFirstSearch(int V, int E, vector<vector<int>> &edges)
{
    vector<vector<int>>ans; 
    solve(ans,edges,V);
    vector<vector<int>>final; 
    // ans is the adjacency list 
    map<int,bool>visited;
    vector<int>arr; 
    for(int i=0; i<V; i++){
        vector<int>arr; 
        if(!visited[i]){
        dfs(ans,visited,i,arr);
         final.push_back(arr);
        }
        
    }
    return final ;
}
