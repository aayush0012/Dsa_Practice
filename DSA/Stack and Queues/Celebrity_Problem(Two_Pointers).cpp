/*
===============================================================================
                                CELEBRITY PROBLEM
===============================================================================

A celebrity is a person who:
1. Knows nobody.
2. Is known by everybody.

Matrix Representation:
mat[i][j] = 1  -> Person i knows Person j
mat[i][j] = 0  -> Person i does not know Person j

Celebrity Conditions for index 'c':

1. Entire row 'c' should contain 0s
   (except mat[c][c], which is irrelevant)

        0 0 0 0
        ^
      Celebrity knows nobody

2. Entire column 'c' should contain 1s
   (except mat[c][c])

        1
        1
        0
        1
        ^
      Everyone knows celebrity

-------------------------------------------------------------------------------
BRUTE FORCE APPROACH
-------------------------------------------------------------------------------

For every person:
    - Check their entire row.
    - Check their entire column.

Time Complexity  : O(N²)
Space Complexity : O(1)

-------------------------------------------------------------------------------
OPTIMIZED TWO POINTER APPROACH
-------------------------------------------------------------------------------

Key Observation:

Consider two people:
    top and bottom

Case 1:
    top knows bottom

    mat[top][bottom] = 1

    => top cannot be celebrity
    => eliminate top

Case 2:
    bottom knows top

    mat[bottom][top] = 1

    => bottom cannot be celebrity
    => eliminate bottom

Case 3:
    Neither knows the other

    => both cannot be celebrity
    => eliminate both

Case 4:
    Both know each other

    => both cannot be celebrity
    => eliminate both

Using two pointers, we continuously eliminate impossible candidates
until at most one person remains.

The remaining person is only a POTENTIAL celebrity.

We must verify:
    1. Their row contains only 0s.
    2. Their column contains only 1s.

-------------------------------------------------------------------------------
TIME COMPLEXITY
-------------------------------------------------------------------------------

Candidate Elimination : O(N)
Verification          : O(N)

Total                 : O(N)

Space Complexity      : O(1)

===============================================================================
*/

class Solution {
public:
    int celebrity(vector<vector<int>>& mat) {

        int top = 0;
        int bottom = mat.size() - 1;

        // Candidate elimination
        while (top < bottom) {

            if (mat[top][bottom] == 1 && mat[bottom][top] == 0) {
                // top knows bottom
                // top cannot be celebrity
                top++;
            }
            else if (mat[top][bottom] == 0 && mat[bottom][top] == 1) {
                // bottom knows top
                // bottom cannot be celebrity
                bottom--;
            }
            else {
                // Both know each other
                // OR neither knows the other
                // In both situations, neither can be celebrity
                top++;
                bottom--;
            }
        }

        // No candidate survived
        if (top > bottom)
            return -1;

        int candidate = top;

        // Verification step
        for (int i = 0; i < mat.size(); i++) {

            if (i == candidate)
                continue;

            // Everyone must know candidate
            if (mat[i][candidate] == 0)
                return -1;

            // Candidate should know nobody
            if (mat[candidate][i] == 1)
                return -1;
        }

        return candidate;
    }
};
