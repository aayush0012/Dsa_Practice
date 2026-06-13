/*
    Sum of Subarray Minimums
    ------------------------

    Idea:
    Instead of finding the minimum for every subarray separately,
    we calculate the contribution of every element.

    For every arr[i], we ask:

        "In how many subarrays is arr[i] the minimum?"

    If an element is minimum in X subarrays, then:

        contribution = arr[i] * X

    ------------------------------------------------------------

    Previous Smaller and Next Smaller
    ---------------------------------

    For every index i:

    prevSmaller = index of previous smaller element
    nextSmaller = index of next smaller element

    These indices help determine how far arr[i] can expand
    while still remaining the minimum.

    Left choices:
        i - prevSmaller

    Right choices:
        nextSmaller - i

    Therefore:

        contribution =
            arr[i] *
            (i - prevSmaller) *
            (nextSmaller - i)

    ------------------------------------------------------------

    Duplicate Handling
    ------------------

    Duplicates can cause double counting.

    To avoid this:
        - Previous Smaller uses <=
        - Next Smaller uses <

    This ensures every subarray is counted exactly once.

    Example:
        [2,2]

    Only one index should count the subarray [2,2].

    ------------------------------------------------------------

    Time Complexity:
        O(n)

    Space Complexity:
        O(n)

    Monotonic stack is used because every element is pushed
    and popped at most once.
    PATTERN -> WE CAN FIND CONTRIBUTION OF EACH ELEMENT EITHER MIN OR MAX OR BOTH
    IF WE ARE ASKED TO FIND MAX WE CAN USE NEXT GREATER AND PREVIOUS GREATER ELEMENT CONCEPT 
*/

class Solution {
public:
const long long mod = 1e9+7; 

 vector<int> nexti(vector<int> &nums2, int n)
{
        vector<int>next(n,-1); 
        stack<int>st; 
        st.push(n-1); 

        for(int i = n-2; i>=0; i--){
            bool a = false;
            while(!st.empty()){
                int first = st.top(); 

                if(nums2[first] < nums2[i]){
                    next[i]=first;
                    st.push(i); 
                    a=true;
                    break; 
                }

                else st.pop(); 
            }

            if(!a){
             st.push(i); 
            }
        }

        return next; 
}

vector<int> pnexti(vector<int> &nums2, int n)
{
        vector<int>next(n,-1); 
        stack<int>st; 
        st.push(0); 

        for(int i = 1; i<n; i++){

            bool a = false;

            while(!st.empty()){

                int first = st.top(); 

                if(nums2[first] <= nums2[i]){
                    next[i]=first;
                    st.push(i); 
                    a=true;
                    break; 
                }

                else st.pop(); 
            }

            if(!a){
             st.push(i); 
            }
        }

        return next; 
}

    int sumSubarrayMins(vector<int>& arr) {

        int n =arr.size(); 

        vector<int>rs = pnexti(arr,n);
        vector<int>s = nexti(arr,n); 

        long long ans = 0; 

        for(int i= 0; i<arr.size(); i++){

            int left_idx= rs[i]; 
            int right_idx = s[i]; 

            int left = 0; 
            int right =0; 

            if(left_idx==-1){
                left= (i+1)%mod; 
            }

            if(right_idx==-1){
                right = (n-i)%mod; 
            }

            if(left_idx!=-1){
                left =(i-left_idx)%mod;
            }

            if(right_idx!=-1){
                right = (right_idx-i)%mod;
            }

            ans =(ans%mod + ((left*right)%mod*arr[i]%mod)%mod)%mod; 
        }   

        return ans ;
    }
};
