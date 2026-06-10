class Solution {
public:
    int solve(vector<int>&nums,int index,int prev_index,vector<vector<int>>&dp){
        if(index==nums.size())return 0; 
        int take = 0; 
        int leave = 0 ;
        if(dp[index][prev_index+1]!=0)return dp[index][prev_index+1]; 
        if(prev_index==-1 || nums[index]>nums[prev_index]){
            take = 1+solve(nums,index+1,index,dp) ;
        }
        leave = solve(nums,index+1,prev_index,dp); 
         return dp[index][prev_index+1]=max(take,leave); 
    }
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size(); 
        vector<vector<int>>dp(n+1,vector<int>(n+1,0)); 
       for(int index = n-1; index>=0; index--){
            for(int last=n-1;last>=-1; last--){
                int take =0;
                int leave =0 ;
                if(last==-1 || nums[index]>nums[last]){
                    take = 1+dp[index+1][index+1]; 
                }
                leave = dp[index+1][last+1];
                dp[index][last+1]=max(take,leave); 
            }
            
        }
        return dp[0][0]; 
    }
};
