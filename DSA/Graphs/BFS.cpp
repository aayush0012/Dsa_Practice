
void bfs(vector<vector<int>>&adj, int node,vector<int> &ans,map<int,bool> &visited){
    queue<int>q; 
    q.push(node); 
    visited[node]=1; 
    while(!q.empty()){
        int frnt=q.front(); 
        q.pop(); 
        ans.push_back(frnt); 
        // we have to check the neighbours of the node 
        for(auto it : adj[frnt]){
            if(!visited[it]){
                q.push(it); 
                visited[it]=1; 
            }
        }

    }
}
vector<int> bfsTraversal(int n, vector<vector<int>> &adj){
    //  We are given an adjacency list and now we have to perform bfs 
    map<int,bool>visited; 
      vector<int>ans; 
   bfs(adj,0,ans,visited); 
    return ans ; 
  

}
