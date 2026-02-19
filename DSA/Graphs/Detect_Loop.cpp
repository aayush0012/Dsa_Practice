#include<map>
#include<queue>
bool check(map<int,vector<int>>&adj , int node , map<int,bool> &visited){
    map<int,int>parent; 
    queue<int>q;
    parent[node]=-1;
    visited[node]=1; 
    q.push(node); 
    while(!q.empty()){
        int front=q.front(); 
        q.pop(); 
        for(auto it:adj[front]){
            if(visited[it] && it!=parent[front]){
                return true ; 
            }
            if(!visited[it]){
                visited[it]=1; 
                parent[it]=front; 
                q.push(it) ; 
            }
        }
    }
    return false; 
}


string cycleDetection (vector<vector<int>>& edges, int n, int m)
{
    // Write your code here.
    map<int,vector<int>>adj; 
      for(int i=0; i<edges.size(); i++){
       adj[edges[i][0]].push_back(edges[i][1]); 
       adj[edges[i][1]].push_back(edges[i][0]); 
      }
      // now we have a adjacnency list 
      map<int,bool>visited;
      for(int i =1; i<=n; i++){
          if(!visited[i]){
              bool ans= check(adj,i,visited); 
              if(ans){
                  return "Yes"; 
              }
          }
      }
      return "No" ; 
}
