#include<map>
#include<queue>
// HERE WE ARE USING DFS CONCEPT TO DETECT THE LOOP FOR DIRECTED GRAPHS 

bool check(map<int,vector<int>> &adj, map<int,int> &visited, int node, map<int,int>dfs){
  visited[node]=1;
  dfs[node]=1;
  for(auto it:adj[node]){
    if(!visited[it]){
      bool ans= check(adj,visited,it,dfs); 
      if(ans){
        return true; 
      }
    }
    else if(dfs[it]){
        return true ; 
    }
  }
dfs[node]=0; 

return false; 

}
int detectCycleInDirectedGraph(int n, vector < pair < int, int >> & edges) {
  // Write your code here.
  map<int,vector<int>>adj; 
  map<int,int>visited;
  map<int,int>dfs; 
  for(int i=0;i<edges.size(); i++){
    pair<int,int>p=edges[i]; 
    adj[p.first].push_back(p.second); 
  }
  for(int i=1;i<=n;i++){
      if(!visited[i]){
        bool ans=check(adj,visited,i,dfs); 
        if(ans==1){
          return 1 ;
        }
      }
  }
  return 0; 
}
