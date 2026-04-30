#include<bits/stdc++.h>
using namespace std;
/*
USED BINARY SEARCH + DFS LOGIC AS THE CONSTRAINTS WERE FRIENDLY 
*/
class Solution {
public:
 bool dfs(vector<vector<int>> & grid , int x, int y ,map<pair<int,int>,int>&visited,int time){
        visited[{x,y}]=1; 
        int n =grid.size(); 
        if(x==n-1 && y==n-1)return true; 
        if(grid[x][y]>time)return false;
        bool left=false;
        bool right  =false;
        bool up=false;
        bool down= false;
        if(x>0 && grid[x-1][y]<=time && !visited[{x-1,y}]){
         up = dfs(grid,x-1,y,visited,time); 
        }
        if(x<n-1 && grid[x+1][y]<=time && !visited[{x+1,y}]){
           down= dfs(grid,x+1,y,visited,time); 

        }
        if(y>0 && grid[x][y-1]<=time && !visited[{x,y-1}]){
           left= dfs(grid,x,y-1,visited,time); 
        }
         if(y<n-1 && grid[x][y+1]<=time && !visited[{x,y+1}]){
            right= dfs(grid,x,y+1,visited,time); 
        }
    if(up || down || left || right)return true; 
    return false ; 
  }
    int swimInWater(vector<vector<int>>& grid) {
            int s=0;
            int e= 1e5+1; 
            int ans =1000000; 
            
            while(s<=e){
                int m = s+(e-s)/2 ;
                map<pair<int,int>,int>visited;
                // can we reach the end with this value of k 
                if(dfs(grid,0,0,visited,m)){
                    ans = m; 
                    e=m-1; 
                }
                else{
                    s=m+1; 
                }
            }
            return ans; 
        
    }
};