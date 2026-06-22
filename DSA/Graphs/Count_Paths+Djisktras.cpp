/*
LeetCode 1976 - Number of Ways to Arrive at Destination

===========================================================
INTUITION (Hinglish)
===========================================================

Normal Dijkstra mein hum sirf shortest distance nikalte hain.

Yaha question pooch raha hai:

    "Shortest distance kitni hai?"
    +
    "Us shortest distance ko achieve karne ke kitne ways hain?"

Isliye hum 2 arrays maintain karenge:

    dist[i]
        = source (0) se node i tak shortest distance

    ways[i]
        = source (0) se node i tak shortest paths ki count

-----------------------------------------------------------
OBSERVATION 1
-----------------------------------------------------------

Agar kisi node v ke liye hume ek better distance milta hai:

    dist[u] + wt < dist[v]

toh purane saare paths useless ho jaate hain.

Example:

    dist[v] = 20

ab naya mila

    dist[u] + wt = 15

toh shortest distance ab 15 hai.

Ab v tak jitne shortest paths hain wo saare u ke shortest
paths se aayenge.

Isliye:

    ways[v] = ways[u]

-----------------------------------------------------------
OBSERVATION 2
-----------------------------------------------------------

Agar:

    dist[u] + wt == dist[v]

toh hume ek aur shortest path mil gaya.

Example:

    ways[v] = 3

aur ek aur route mila jisse shortest distance same hai.

Agar:

    ways[u] = 2

toh ye 2 naye shortest paths contribute karega.

Isliye:

    ways[v] += ways[u]

-----------------------------------------------------------
STALE ENTRY CONCEPT
-----------------------------------------------------------

Priority Queue mein same node multiple baar aa sakta hai.

Example:

    (10, 1)

insert hua.

Baad mein better path mila:

    (5, 1)

ab

    dist[1] = 5

ho gaya.

PQ mein dono entries padhi hain.

Jab (10,1) bahar niklega toh wo outdated hai.

Check:

    if (w > dist[u]) continue;

Meaning:

    "Ye entry insert hui thi jab mujhe lagta tha
     shortest distance w hai.

     Ab mujhe better distance mil chuka hai.

     Ignore this entry."

Ye optimization normal Dijkstra mein bhi use hota hai.

-----------------------------------------------------------
TIME COMPLEXITY
-----------------------------------------------------------

    O(E log V)

-----------------------------------------------------------
SPACE COMPLEXITY
-----------------------------------------------------------

    O(E + V)

*/

class Solution {
public:

    const long long mod = 1e9 + 7;

    int countPaths(int n, vector<vector<int>>& roads) {

        priority_queue<
            pair<long long, int>,
            vector<pair<long long, int>>,
            greater<pair<long long, int>>
        > pq;

        map<int, vector<pair<int, int>>> adj;

        for (int i = 0; i < roads.size(); i++) {

            int u = roads[i][0];
            int v = roads[i][1];
            int time = roads[i][2];

            adj[u].push_back({time, v});
            adj[v].push_back({time, u});
        }

        vector<long long> dist(n, LLONG_MAX);
        vector<long long> ways(n, 0);

        dist[0] = 0;
        ways[0] = 1;

        pq.push({0, 0});

        while (!pq.empty()) {

            auto temp = pq.top();
            pq.pop();

            long long w = temp.first;
            int u = temp.second;

            // stale entry
            if (w > dist[u])
                continue;

            for (auto it : adj[u]) {

                int wt = it.first;
                int v = it.second;

                // Better shortest distance found
                if (dist[u] + wt < dist[v]) {

                    dist[v] = dist[u] + wt;
                    ways[v] = ways[u];

                    pq.push({dist[v], v});
                }

                // Another shortest path found
                else if (dist[u] + wt == dist[v]) {

                    ways[v] =
                        (ways[v] + ways[u]) % mod;
                }
            }
        }

        return ways[n - 1] % mod;
    }
};
