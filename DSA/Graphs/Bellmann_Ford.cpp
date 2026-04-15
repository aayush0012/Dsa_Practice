#include<map>
#include<queue>
#include<map>
#include<queue>
#include <bits/stdc++.h>
using namespace std;
/*
Bellman-Ford Algorithm (Hinglish Revision)

Use case:
Find shortest path from a single source node to all other nodes.
Works with negative edge weights.
Can also detect negative cycles.

Core Idea:
Hum har edge ko repeatedly relax karte hain.
Maximum shortest path me n-1 edges ho sakte hain.
Isliye hum n-1 baar relaxation karte hain.

Relaxation:
Agar dist[u] + weight < dist[v] ho, to dist[v] ko update kar dete hain.

Steps:

1. Sabhi nodes ke distance ko infinity (1e8) se initialize karo.
2. Source node ka distance 0 set karo.
3. n-1 times:

   * Har edge (u, v, wt) ke liye check karo:
     agar dist[u] reachable hai aur dist[u] + wt < dist[v], to update karo.
4. Optional:
   Ek extra iteration me agar distance aur improve hota hai,
   to graph me negative cycle hai.

Important Condition:
Update tabhi karna hai jab dist[u] infinity na ho,
warna galat updates ho sakte hain.

Dijkstra vs Bellman-Ford:
Dijkstra negative edges handle nahi karta.
Bellman-Ford negative edges handle karta hai.

Time Complexity:
O(N * M)

One line yaad rakhne ke liye:
Bellman-Ford sab edges ko n-1 baar relax karke shortest path nikalta hai,
even with negative weights.
*/

vector<int> bellmonFord(int n, int m, int src, vector<vector<int>> &edges) {
    // Write your code here.
    vector<int>ans(n+1,1e8); 
    ans[src]=0; 
    for(int i = 1;i<=n-1; i++){
        for(int j =0; j<edges.size(); j++){
            int u = edges[j][0]; 
            int v= edges[j][1]; 
            int wt= edges[j][2]; 
            if(ans[i]!=1e8 && ans[u]+wt<ans[v]){
                ans[v]=ans[u]+wt; 
            }
        }
    }

        return ans ; 

}