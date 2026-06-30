/*
================================================================================
                    BINARY LIFTING - LOWEST COMMON ANCESTOR
================================================================================

Question
--------

Given two nodes u and v,

find their Lowest Common Ancestor (LCA).

Example

            1
         /     \
        2       3
      /   \
     4     5
    /
   8

LCA(8,5)

=

2

================================================================================
OBSERVATION
================================================================================

Binary Lifting already tells us

"How to jump upwards."

Ab hum usi table

up[][]

ka use karke LCA nikalenge.

================================================================================
STEP 1 - STORE DEPTH OF EVERY NODE
================================================================================

Sabse pehle DFS chala ke har node ki depth store kar lo.

Example

            1
         /     \
        2       3
      /   \
     4     5
    /
   8

Depth

1 -> 0
2 -> 1
3 -> 1
4 -> 2
5 -> 2
8 -> 3

Why?

Agar dono nodes different depth pe honge

to compare hi nahi kar sakte.

================================================================================
STEP 2 - MAKE BOTH NODES AT SAME DEPTH
================================================================================

Example

u = 8

v = 3

Depth Difference

= 2

Matlab

8 ko 2 levels upar le jao.

Binary Lifting se ye O(logN) me ho jayega.

================================================================================
STEP 3
================================================================================

Agar lift karne ke baad

u == v

Toh wahi LCA hai.

Return u.

================================================================================
STEP 4 - LIFT BOTH TOGETHER
================================================================================

Ab dono same depth pe hain.

LOG-1 se 0 tak iterate karenge.

Rule

Agar

up[u][i] != up[v][i]

Toh dono ko jump kara do.

Kyun?

Kyuki iska matlab hai

LCA abhi bhi upar hai.

---------------------------------------------------

Agar

up[u][i] == up[v][i]

Toh jump mat karo.

Kyuki

Ya toh wahi LCA hai

Ya LCA ke upar hai.

================================================================================
FINAL STEP
================================================================================

Loop ke end me

u

and

v

LCA ke just niche honge.

Answer

=

up[u][0]

================================================================================
Time Complexity
================================================================================

DFS

O(N)

Building Table

O(N logN)

Each Query

O(logN)

Space

O(N logN)

================================================================================
*/

#include<bits/stdc++.h>
using namespace std;

int LOG;
vector<vector<int>> up;
vector<int> depth;
vector<vector<int>> adj;

void dfs(int node, int parent)
{
    up[node][0] = parent;

    for(auto child : adj[node])
    {
        if(child == parent)
            continue;

        depth[child] = depth[node] + 1;

        dfs(child, node);
    }
}

void build(int n)
{
    LOG = 0;

    while((1<<LOG) <= n)
        LOG++;

    up.assign(n + 1, vector<int>(LOG, -1));
    depth.assign(n + 1, 0);

    dfs(1,-1);

    for(int j=1;j<LOG;j++)
    {
        for(int node=1;node<=n;node++)
        {
            if(up[node][j-1] != -1)
            {
                up[node][j] = up[ up[node][j-1] ][j-1];
            }
        }
    }
}

int lca(int u,int v)
{
    // Make both nodes at same depth

    if(depth[u] < depth[v])
        swap(u,v);

    int diff = depth[u] - depth[v];

    for(int i=LOG-1;i>=0;i--)
    {
        if(diff & (1<<i))
            u = up[u][i];
    }

    // One node was ancestor of another

    if(u == v)
        return u;

    // Lift both together

    for(int i=LOG-1;i>=0;i--)
    {
        if(up[u][i] != up[v][i])
        {
            u = up[u][i];
            v = up[v][i];
        }
    }

    // Parent of both is the answer

    return up[u][0];
}

/*
Distance Between Two Nodes

distance(u,v)

=

depth[u]
+
depth[v]
-
2*depth[lca(u,v)]

*/
