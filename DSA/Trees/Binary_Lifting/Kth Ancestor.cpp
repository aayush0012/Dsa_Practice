/*
================================================================================
                    BINARY LIFTING - KTH ANCESTOR
================================================================================

Question
--------
Given a node and an integer k,
find the kth ancestor of that node.

Example
-------
5 -> 4 -> 2 -> 1

k = 3

Answer = 1

================================================================================
BRUTE FORCE
================================================================================

Har baar ek step upar chale jao.

Example:
k = 13

=> 13 baar parent pe chale jao.

Time Complexity:
O(k)

Worst Case:
Tree skewed ho sakta hai.

Height = n

Toh per query complexity:

O(n)

Ye approach slow hai.

================================================================================
OBSERVATION
================================================================================

Hume har ancestor store karne ki zarurat nahi hai.

Sirf ye ancestors store karenge:

1st
2nd
4th
8th
16th
32nd
...

Question:
Sirf powers of 2 hi kyun?

Because har number ko powers of 2 ke sum me likh sakte hain.

Example:

13

= 8 + 4 + 1

Matlab agar 13th ancestor chahiye toh

Jump 8

↓

Jump 4

↓

Jump 1

Done.

================================================================================
LOG KA LOGIC
================================================================================

Question:
Kitne columns banane padenge?

Suppose

n = 100000

Worst Case:
Tree skewed hai.

1
|
2
|
3
|
4
|
.
.
100000

Height = 100000

Ab hume maximum jump kitna chahiye?

Powers of 2

1
2
4
8
16
32
64
...

Jab tak jump <= height.

2^16 = 65536

2^17 = 131072

131072 tree ki height se bada ho gaya.

Matlab bas 17 columns enough hain.

General Formula:

LOG = floor(log2(n)) + 1

Ya phir integer method:

int LOG = 0;

while ((1 << LOG) <= n)
    LOG++;

Ye method Competitive Programming me zyada use hota hai.

================================================================================
WHAT DOES up[][] STORE?
================================================================================

up[node][i]

means

2^i-th ancestor of node.

Example

1
|
2
|
3
|
4
|
5

For node = 5

up[5][0] = 4   -> 1st ancestor

up[5][1] = 3   -> 2nd ancestor

up[5][2] = 1   -> 4th ancestor

up[5][3] = -1  -> 8th ancestor doesn't exist

================================================================================
HOW DO WE BUILD THE TABLE?
================================================================================

STEP 1

Sabse pehle parent already pata hota hai.

Toh

up[node][0] = parent[node]

Ye first column ban gaya.

------------------------------------------------------------

STEP 2

Ab maan lo hume

4th ancestor

nikalna hai.

Observe:

4th ancestor

=

2nd ancestor of 2nd ancestor.

Isliye

up[node][2]

=

up[ up[node][1] ][1]

Similarly,

8th ancestor

=

4th ancestor of 4th ancestor.

General Formula:

up[node][j]

=

up[ up[node][j-1] ][j-1]

Isi formula se pura Binary Lifting table fill hota hai.

Time Complexity:

O(N log N)

================================================================================
QUERY
================================================================================

Need kth ancestor.

Sabse pehle

k

ko binary me convert karo.

Example

k = 13

Binary = 1101

Matlab

13

= 8 + 4 + 1

Ab highest power se start karo.

Jump 8

↓

Jump 4

↓

Jump 1

Answer mil gaya.

Time Complexity:

O(log N)

================================================================================
COMPLEXITIES
================================================================================

Preprocessing

O(N log N)

Each Query

O(log N)

Space

O(N log N)

================================================================================
*/

class TreeAncestor {
public:

    int LOG;
    vector<vector<int>> up;

    TreeAncestor(int n, vector<int>& parent) {

        // Find number of columns required
        LOG = 0;
        while ((1 << LOG) <= n)
            LOG++;

        // Binary Lifting Table
        up.assign(n, vector<int>(LOG, -1));

        // First Column
        // up[node][0] = parent of node

        for (int node = 0; node < n; node++)
            up[node][0] = parent[node];

        // Fill Remaining Columns

        for (int j = 1; j < LOG; j++) {

            for (int node = 0; node < n; node++) {

                if (up[node][j - 1] != -1)
                    up[node][j] = up[up[node][j - 1]][j - 1];
            }
        }
    }

    int getKthAncestor(int node, int k) {

        // Traverse bits of k from highest to lowest

        for (int i = LOG - 1; i >= 0; i--) {

            if (k & (1 << i)) {

                node = up[node][i];

                if (node == -1)
                    return -1;
            }
        }

        return node;
    }
};

/*
Time Complexity

Preprocessing : O(N log N)

Each Query : O(log N)

Space : O(N log N)
*/
