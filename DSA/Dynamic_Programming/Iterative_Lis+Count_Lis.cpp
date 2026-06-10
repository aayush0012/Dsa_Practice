class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size(); 
    vector<int>dp(n,1); 
    vector<int>cnt(n,1) ;
    for (int index = 0; index<n; index++){
        for(int prev= 0; prev<index; prev++) {
            if(nums[prev]<nums[index]){
               if(dp[prev]+1==dp[index]){
                    cnt[index]+=cnt[prev];
               }
               else if(dp[prev]+1>dp[index]){
                dp[index]=dp[prev]+1;
                cnt[index]=cnt[prev]; 
               }
            }
        }
    }
    int maxi =*max_element(dp.begin(),dp.end()); 
    int ans = 0; 
    for(int i =0; i<n; i++){
        if(dp[i]==maxi)ans+=cnt[i]; 
    }
    return ans; 
    }

};
