/*
================================================================================
            Longest Increasing Subsequence (Binary Search | O(n log n))
================================================================================

Problem:
Given an integer array nums, return the length of the Longest Increasing
Subsequence (LIS).

Example:
Input  : [10,9,2,5,3,7,101,18]
Output : 4


Approach
========

Sabse pehle jo approach dimag me aati hai wo DP ki hoti hai.

dp[i] = Length of LIS ending at index i.

Har index ke liye uske pehle ke saare elements check karte hain.

Time Complexity = O(n²)

Agar interviewer bole ki isse O(n log n) me solve karo, tab hume observe
karna padega ki hume actual LIS store karne ki zarurat hi nahi hai.


Let's Understand with an Example
================================

Maan lo,

nums = [3,5,6,2,7]

Ek vector maintain karte hain.

Initially

[]

3 aaya

[3]

5 aaya

5 > 3

To append kar denge.

[3,5]

6 aaya

6 > 5

Again append.

[3,5,6]

Ab 2 aaya.

2 answer increase nahi karega.

Lekin agar hum 3 ki jagah 2 rakh dein to future me aur elements ko attach
karne ke chances badh jaate hain.

Isliye

[2,5,6]

Ab 7 aaya.

7 > 6

Append kar denge.

[2,5,6,7]


Ab dhyaan dene wali baat 👇

Ye vector

[2,5,6,7]

Actual LIS nahi hai.

Original array me 2, 5 aur 6 ke baad aata hai.

Isliye ye valid subsequence bhi nahi hai.

Actual LIS hai

[3,5,6,7]

To phir ye vector maintain kyu kar rahe hain?

Kyuki hume actual sequence nahi chahiye.

Hume sirf har length ke liye best possible ending element chahiye.

Agar ending element chhota hoga to future me usse extend karne ke chances
zyada honge.


Algorithm
=========

Har element x ke liye sirf 2 cases hain.

Case 1

Agar

x > ans.back()

To iska matlab hum longest increasing subsequence ko aur bada kar sakte hain.

Simply push_back() kar do.


Case 2

Agar x bada nahi hai.

To answer increase nahi hoga.

Lekin ho sakta hai x kisi existing subsequence ki ending ko improve kar de.

Isliye hum first element jo >= x ho usko replace kar dete hain.

Example

ans = [2,5,6]

x = 4

Replace 5

ans = [2,4,6]

Length same hai.

Lekin future me isse extend karna aur easy ho gaya.


Why lower_bound()?
==================

Ye vector hamesha sorted rehta hai.

Hume first element chahiye jo current element se
greater than ya equal ho.

Exactly ye kaam lower_bound() karta hai.

Example

ans = [2,5,6,10]

x = 4

lower_bound() hume 5 ka index de dega.

Hum usse replace kar denge.

ans = [2,4,6,10]


Complexity
==========

Time  : O(n log n)

Har element ke liye

Binary Search -> O(log n)

Replacement -> O(1)

Space : O(n)

================================================================================
*/

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> ans;

        for (int i = 0; i < nums.size(); i++) {
            if (ans.empty()) {
                ans.push_back(nums[i]);
            } else {
                if (nums[i] > ans.back()) {
                    ans.push_back(nums[i]);
                } else {
                    int idx = lower_bound(ans.begin(), ans.end(), nums[i]) - ans.begin();
                    ans[idx] = nums[i];
                }
            }
        }

        return ans.size();
    }
};
