#include<bits/stdc++.h>
using namespace std; 
/*
================ DISJOINT SET + KRUSKAL =================

Disjoint Set (Union-Find) is used to manage a collection of
non-overlapping sets and efficiently check connectivity.

Example:
Elements: {1,2,3,4,5}
Sets: {1,2}, {4}, {3,5}

------------------------------------------------------------
WHY WE USE IT:
- To check if two nodes belong to the same component
- To merge components efficiently
- Used in graph algorithms like MST and cycle detection

------------------------------------------------------------
CORE IDEA:
- Each node has a parent
- Initially, parent[i] = i (each node is its own set)

------------------------------------------------------------
OPERATIONS:

1) FIND (find_parent)
- Finds the ultimate parent (root)
- Uses path compression for optimization

2) UNION (un)
- Merges two sets
- Uses rank to keep tree shallow

------------------------------------------------------------
KRUSKAL'S ALGORITHM:
- Used to find Minimum Spanning Tree (MST)

Steps:
1) Sort all edges by weight
2) For each edge (u, v, wt):
   - If find(u) != find(v):
       → include edge in MST
       → union(u, v)
   - Else skip (cycle)

------------------------------------------------------------
TIME COMPLEXITY:
- Almost O(1) per DSU operation

============================================================
*/

bool cmp(vector<int> &a ,vector<int> &b){
  return a[2]<b[2]; 
}

void sett(vector<int> &parent , vector<int> &rank,int n ){
  for(int i =0; i<n; i++){
    parent[i]=i; 
    rank[i]=0; 
  }
}

int find_parent(vector<int> &parent,int node){
  if(parent[node]==node){
    return node; 
  }
  parent[node] = find_parent(parent,parent[node]);
  return parent[node]; 
}

void un(vector<int>&parent,vector<int> &rank,int u,int v){
  u=find_parent(parent,u); 
  v=find_parent(parent,v); 

  if(rank[u]<rank[v]){
    parent[u]=v;
  }
  else if (rank[u]>rank[v]){
    parent[v]=u; 
  }
  else{
    parent[u]=v;
    rank[v]++; 
  }
}

int minimumSpanningTree(vector<vector<int>>& edges, int n)
{
  vector<int>parent(n); 
  vector<int>rank(n); 

  sett(parent,rank,n); 

  int mst_wt = 0 ;

  sort(edges.begin(),edges.end(), cmp ); 

  for(int i =0; i<edges.size(); i++){
    int u = find_parent(parent,edges[i][0]); 
    int v = find_parent(parent,edges[i][1]); 
    int wt= edges[i][2]; 

    if(u!=v){
        mst_wt+=wt; 
        un(parent,rank,edges[i][0],edges[i][1]); 
    }
  }

  return mst_wt; 
}