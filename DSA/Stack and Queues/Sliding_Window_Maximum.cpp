```cpp
/*
    SLIDING WINDOW MAXIMUM
    ----------------------

    Concept:

    Hume har window of size k ka maximum nikalna hai.

    Brute force:
    Har window ke liye maximum find kro.
    Complexity = O(n*k)

    Optimized Approach:
    -------------------

    Hum deque maintain krenge.

    Deque me hum indices store krenge
    and deque decreasing order me maintain hoga
    according to values.

    Example:

    nums = [1,3,-1]

    Jab 3 aaya:
    1 useless ho gaya because:
        3 > 1
    and 3 zyada der tak survive bhi krega.

    Isliye:
    smaller elements ko pop_back kar dete h.

    Important:
    ----------
    Front of deque always stores
    maximum element of current window.

    Why indices?
    ------------
    Because hume check karna hota h
    ki koi element window se bahar gaya ya nahi.

    Current valid window:
        [i-k+1 , i]

    Agar:
        dq.front() <= i-k

    then wo index expired h
    so pop_front()

    Complexity:
    -----------
    Every element:
        pushed once
        popped once

    Total:
        O(n)

*/


class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {

        deque<int> dq;
        vector<int> ans;

        int n = nums.size();

        for(int i = 0; i < n; i++) {

            // remove expired elements
            while(!dq.empty() && dq.front() <= i-k) {
                dq.pop_front();
            }

            // remove smaller useless elements
            while(!dq.empty() && nums[dq.back()] < nums[i]) {
                dq.pop_back();
            }

            // push current index
            dq.push_back(i);

            // window formed
            if(i >= k-1) {
                ans.push_back(nums[dq.front()]);
            }
        }

        return ans;
    }
};
```
